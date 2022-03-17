# 

# c++同步

## 锁

#### 头文件

+ `#include <mutex>`

#### 同步操作

``` cpp
mutex mu;
mu.lock();

thread safe;

mu.unlock();
```

#### RAII机制

#### lock_guard

+ `lock_guard`只能在一个scope中使用，不能够移动，也不能够解锁。

#### unique_lock

+ 存在移动构造函数，可以转移锁使用的scope
+ 允许当前对象中不存在锁，可以在之后进行加锁或者解锁，管理更加复杂与灵活。

### 条件变量

#### 头文件

+ `#include <condition_variable>`

#### 同步操作

+ 条件变量必须通过互斥锁实现原子性的条件的通知与唤醒。
+ [条件变量](https://en.cppreference.com/w/cpp/thread/condition_variable)

``` cpp
std::mutex m;
std::condition_variable cv;
// 标准使用方法
void th1() {
    m.lock();
    change condition;
    m.unlock();
    cv.notify_all();
}

bool WakeCondition() {
}

void th2() {
    m.lock();
    cv.wait(m, WakeCondition);
    m.unlock();
}

// 生产者消费者
const int MAX_COUNT = 10;
int count = 0;

bool ProducerCondition() {
    return count < MAX_COUNT;
}

bool ConsumerCondition() {
    return count > 0;
}

void producer() {
    m.lock();
    cv.wait(m, ProducerCondition);
    count += 1;
    m.unlock();
    cv.notify_all();
}

void consumer() {
    m.lock();
    cv.wait(lk, ConsumerCondition);
    count -= 1;
    m.unlock();
    cv.notify_all();
}
```

### 信号量

+ 互斥锁+条件变量。
+ 互斥锁：P（加锁），V（解锁）
+ 条件变量：P（wait）， V（signal）
+ P消耗资源，V生产资源

#### 头文件

+ `#include <semaphore.h>`(c语言库)

#### 同步操作

+ `int sem_init(sem_t *sem, int pshared, unsigned int value);`(pshared 控制信号量的类型，值为 0 代表该信号量用于多线程间的同步，值如果大于 0 表示可以共享，用于多个相关进程间的同步)
+ `int sem_wait(sem_t *sem); `，将信号量减一，如果信号量<=0则阻塞。
+ `int sem_post(sem_t *sem);`，将信号量加一，并且唤醒正在等待改信号量的线程。
+ `int sem_destroy(sem_t *sem);`，清理该信号量使用的内存。

``` cpp
sem_t empty, full;

sem_init(&empty, 0, 0);
sem_init(&full, 0, 0);

void producer() {
    sem_wait(&empty);
    produce();
    sem_post(&full);
}

void consumer() {
    sem_wait(&full);
    consume();
    sem_post(&empty);
}
```


