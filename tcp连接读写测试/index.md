# 读写已经关闭的TCP连接会发生什么




## 读写已经关闭的TCP连接

#### TCP连接状态图

![TCP四次挥手](https://picture-table.oss-cn-beijing.aliyuncs.com/img/TCP%E5%9B%9B%E6%AC%A1%E6%8C%A5%E6%89%8B.png)

#### 连接关闭的两种方式

关闭一个连接，有两种方式：1.使用四次挥手，正常关闭一个TCP连接。2.在紧急情况下，TCP连接会发送RST报文关闭一个连接。

#### shutdown与close

##### shutdown

+ int shutdown(int sockfd, int how)

> The  shutdown() call causes all or part of a full-duplex connection on the socket associated with sockfd to be shut down.  If how is SHUT_RD, further receptions will be disallowed.  If how is  SHUT_WR,  further  transmissions will be disallowed.  If how is SHUT_RDWR, further receptions and transmissions will be disallowed.

>If the TCP stack receives a shutdown with SHUT_RD only, it shall mark this connection as no more data expected. Any pending and subsequent `read` requests (regardless whichever thread they are in) will then returned with zero sized result. However, the connection is still active and usable -- you can still receive OOB data, for example. Also, the OS will drop any data it receives for this connection. But that is all, no packages will be sent to the other side.
>
>If the TCP stack receives a shutdown with SHUT_WR only, it shall mark this connection as no more data can be sent. All pending write requests will be finished, but subsequent write requests will fail. Furthermore, a FIN packet will be sent to another side to inform them we don't have more data to send.

+ SHUT_RD：主动关闭接收端，所有的read都会返回0。由于在TCP连接中不能主动关闭接收端，必须等待对端发送FIN报文，才能关闭当前连接。所以操作系统仍然会收到对端发送的报文，但是这些报文会被丢弃。
+ SHUT_WR：主动关闭发送端，操作系统标记当前的连接不可以继续写入。如果写入该连接，会产生SIGPIPE信号。之后操作系统会向对端发送FIN关闭发送端，收到ACK后进入FIN_WAIT2状态，仍然可以接受对端发送的数据。

##### close

+ close()：close与SHUT_RDWR相同，同时关闭socket的读端与写端。

#### 写异常

##### 主动关闭写端

+ 主动关闭写端，之后再向改socket写入数据，会产生SIGPIPE信号。

##### 对端关闭读端

+ 对端仅关闭读端而未关闭写端，此时双方仍都处于ESTABLISHED。对端操作系统仍然会收到发送的报文，但是这些报文会被丢弃。

##### 对端同时关闭读写

+ 第一次写入后可以返回，但是发送到对端后，对端发送RST报文，关闭该连接。之后再次写入会产生SIGPIPE信号。

#### 读异常

##### 主动关闭读端

+ read返回0。

##### 对端关闭写端

+ read返回0。

##### 对端同时关闭读写

+ 返回-1，并且产生错误read error Connection reset by peer, errorno: 104。

#### 测试读写异常

+ 测试过程查看某个端口的连接情况`lsof -i:1234`
+ 向某个进程发送信号`kill -signal pid`

##### 服务端

+ 信号SIGINT同时关闭当前连接读写。
+ 信号SIGUSR1关闭当前读端。
+ 信号SIGUSR2关闭当前写端。

``` cpp
#include <sys/socket.h>
#include <arpa/inet.h>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
int connfd = -1;

void SigHandler(int sig) {
    if (sig == SIGINT) {
        printf("Ctrl C\n");
        printf("Close client all %d\n", connfd);
        shutdown(connfd, SHUT_RDWR);
    } else if (sig == SIGUSR1) {
        printf("SIGUSR1\n");
        printf("Close client read fd %d\n", connfd);
        shutdown(connfd, SHUT_RD);
    } else if (sig == SIGUSR2) {
        printf("SIGUSR2\n");
        printf("Close client write fd %d\n", connfd);
        shutdown(connfd, SHUT_WR);        
    }
}

int main () {
    const char* ip = "127.0.0.1";
    int port =  1234;

    signal(SIGINT, SigHandler);
    signal(SIGUSR1, SigHandler);
    signal(SIGUSR2, SigHandler);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&opt), sizeof(opt));
    assert(sock >= 0);
    
    auto ret = bind(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr));
    assert(ret != -1);

    ret = listen(sock, 5);

    struct sockaddr_in client;
    socklen_t client_lenght = sizeof(client);

    connfd = accept(sock, reinterpret_cast<sockaddr*>(&client), &client_lenght);

    char client_name[16];
    inet_ntop(AF_INET, &(client.sin_addr), client_name, client_lenght);
    uint16_t client_port = ntohs(client.sin_port);
    char read_buf[BUFSIZ];
    printf("[%s:%d] on \n", client_name, client_port);
    
    while (true) {
        memset (read_buf, 0, sizeof(read_buf));

        ret = read(connfd, read_buf, BUFSIZ - 1);

        if (ret == -1) {
            printf("error: read error %s, errorno: %d\n", strerror(errno), errno);
            close(connfd);
            break;
        } else if (ret == 0) {
            printf("Read return 0, other end close write or close local read\n");
            sleep(10);
            break;
        } else {
            printf("[%s:%d]: read %d bytes, (data) : %s\n", client_name, client_port, ret, read_buf);

            ret = write(connfd, read_buf, ret);

            if (ret == -1) {
                printf("error: write error %s, errorno: %d\n", strerror(errno), errno);
                close(connfd);
                break;  
            }

            printf("[%s:%d]: write %d bytes, (data) : %s\n", client_name, client_port, ret, read_buf);
        }
    }

    close(sock);

    return 0;
} 
```

##### 客户端

+ 信号SIGINT同时关闭当前连接写端。

``` cpp
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int sock = -1;

void signal_handler(int signum) {
    if (signum == SIGINT) {
        if (sock != -1) {
            shutdown(sock, SHUT_WR);
        }
        printf("receive sigint don't write sock %d\n", sock);
        // exit(0);
    } else if (signum == SIGPIPE) {
        printf("other end is close\n");
        exit(0);
    }
}

int main () {
    const char* ip = "127.0.0.1";
    int port =  1234;

    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // connet 是非阻塞的
    auto ret = connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (ret == -1) {
        printf("connnet error %s, errorno: %d \n", strerror(errno), errno);
        close(sock);
        exit(0);
    }

    printf("Connet to [%s:%d] on \n", ip, port);
    
    while (true) {
        char write_buf[BUFSIZ];
        memset (write_buf, 0, BUFSIZ);

        int ret = read(STDIN_FILENO, write_buf, BUFSIZ - 1);

        if (ret == -1) {
            printf("error: read error from bash %s, errorno: %d\n", strerror(errno), errno);
            close(sock);
            break;
        } else if (ret == 0) {
            printf("READ EOF\n");
            close(sock);
            break;
        }

        printf("Start write \n");

        ret = write(sock, write_buf, ret);

        if (ret == -1) {
            printf("error: write error %s, errorno: %d\n", strerror(errno), errno);
            close(sock);
            // break;
        }

        ret = read(sock, write_buf, BUFSIZ - 1);

        if (ret == -1) {
            printf("error: read error from bash %s, errorno: %d\n", strerror(errno), errno);
            close(sock);
            break;
        }

        printf("[%s:%d]: read %d bytes, (data) : %s\n", ip, port, ret, write_buf);
    }

    close(sock);

    return 0;
}
```

#### 参考链接

+ https://stackoverflow.com/questions/4160347/close-vs-shutdown-socket
+ https://blog.csdn.net/BryantLmm/article/details/81671457

