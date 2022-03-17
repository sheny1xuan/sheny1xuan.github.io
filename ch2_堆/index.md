# acwing基础课ch2-堆


## 堆/优先队列

### 堆是什么

+ 堆是一颗完全二叉树。
+ 大顶堆：父亲结点的值大于左右子树的结点。
+ 小顶堆：父亲结点的值小于左右子树的结点。

### 堆的操作与优点

##### 优点

+ O(1)时间内找出最大或最小的数
+ 添加或者删除一个数需要O(logn)的时间复杂度

##### 支持操作-最小堆

+ **向上调整**：把欲调整节点与其父亲节点比较，直到其小于父亲节点。
+ **向下调整**：将当前结点与左右孩子比较，直到其比左右儿子都小。

##### 存储方式

+ 使用一维数组进行存储，1号点为根节点，同时使用一个变量记录节点的总数。
+ 使用数组静态表示堆$heap[i]$从1开始，该节点左孩子为$heap[2i]$,该节点右孩子为$heap[2i+1]$。
+ 因为堆为完全二叉树，所以数组肯定可以放满。

![image-20210518151420081](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210518151420081.png)

### 建立堆

+ 先将堆初始化（数组初始化）。
+ 从n/2到1**向下调整**每一个数。
+ 时间复杂度$O(n)$，而通过插入每一个元素建立堆的时间复杂度是$O(nlogn)$

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210518203551431.png" alt="image-20210518203551431" style="zoom:80%;" />

### 向堆中插入一个数

+ 将欲添加元素添加至堆的最后。
+ 将该元素**向上调整**至合适的位置。

### 求堆顶元素

+ 返回第一个元素即可

### 删除堆顶元素

+ 把最后一个元素覆盖堆顶元素
+ 删除最后一个元素，缩小数据规模
+ 之后将第一个元素**向下调整**

### 删除任意一个元素

+ 将第k个元素与最后一个元素交换
+ 之后删除最后一个元素

+ 然后再将第k个元素分别向上/向下调整（因为不知道交换之后的元素具体位置）。

### 修改任意一个元素

+ 修改第k个元素
+ 然后将第k个元素分别向上/向下调整。



## 堆排序

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int h[N], cnt, n, m;

void down(int idx){
    int t = idx;
    if(idx * 2 <= cnt && h[idx * 2] < h[t]) t = idx * 2;
    if(idx * 2 + 1 <= cnt && h[idx * 2 + 1] < h[t]) t = idx * 2 + 1;
    swap(h[t], h[idx]);
    if(t != idx){
        down(t);
    }
}

void up(int idx){
    int t = idx;
    if(idx / 2 > 0 && h[idx / 2] > h[t])	t = idx / 2;
    swap(h[t], h[idx]);
    if(t != idx){
        up(t)
    }
}

int popTop(){
    int ret = h[1];
    swap(h[cnt], h[1]);
    cnt--;
    down(1);
    
    return ret;
}
// 建堆过程，向下调整
// 时间复杂度O(n)
void creatHeap(){
    cnt = n;
    for(int i = n / 2; i >= 1; i--){
        down(i);
    }
}

int main(){
    
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++) cin >> h[i];
    
    creatHeap();
    
    for(int i = 1; i <= m; i++){
        cout << popTop() << ' ';
    }
    
    return 0;
    
}
```


