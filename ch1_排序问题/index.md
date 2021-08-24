# acwing基础课ch1-排序问题


# 排序

## 分类

![img](https://picture-table.oss-cn-beijing.aliyuncs.com/img/849589-20190306165258970-1789860540.png)

## 复杂度分析

![img](https://picture-table.oss-cn-beijing.aliyuncs.com/img/849589-20180402133438219-1946132192.png)

![image-20210428205202716](../pic/image-20210428205202716.png)

## 快速排序

+ 基于分治思想

### 主要步骤

1. 确定分界点x，随机(一般为左端点)
2. 调整范围，左半边小于等于x，右半边大于等于x（双指针）。
   1. 如果忘记了双指针方法，可以暴力开数组求解。
3. 递归处理左右区间。

### 复杂度分析

+ 最坏时间复杂度发生在数组有序的时候，数组有序时，每次划分的区间都是左边界，时间复杂度时$O(n^2)$
+ 最好时间复杂度：切分点在数组中间，$C_n = 2C_{n/2} + n$,$T:O(nlogn)$
+ 平均时间复杂度：切分点的期望是在数组中间，因此平均复杂度就是最好的时间复杂度。
+ 空间复杂度：$O(logn)$递归栈调用，最差为$O(n)$

### [Acwing785. 快速排序](https://www.acwing.com/problem/content/787/)

+ 一直选取做边界会超时
+ 选择中值或者随机取值则不会超时。
+ while循环结束后$q[l...j]<=x, q[j+1...r]>=x$
+ j的取值范围为$l, r-1$，所以不会一直不划分边界
+ 只能取大于或者小于号是因为交换原来的数字进行了限位，不会产生数组溢出的问题。

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int a[N];

void Quick_Sort(int a[], int l, int r){
    if(l >= r)  return;
    // 注意这里i,j都与开始值差一位
    int x = a[l], i = l - 1, j = r + 1;
    // 循环结束后,a[l...j] <= x, a[j+1...r] >= x
    while(i < j){
        // 这里不能用等号，是因为交换让目标值做限位的作用
        while(a[++i] < x);
        while(a[--j] > x);
        if(i < j)   swap(a[i], a[j]);
    }
    cout <<l << ' '<< r << ' ' << j << ' ' << endl;
    // j取值范围时[l, r-1]不存在0和n区间无限循环
    // j最小值大于等于l
    Quick_Sort(a, l, j);
    Quick_Sort(a, j+1, r);
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n; i++){
        scanf("%d", &a[i]);
    }
    Quick_Sort(a, 0, n-1);
    for(int i = 0;i < n; i++){
        printf("%d ", a[i]);
    }
    return 0;
}
```

+ 快慢指针版本，数据量较大时候，由于多次交换，会超时。

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int a[N];

void Quick_Sort(int a[], int l, int r){
    // 快慢指针版本
    if(l >= r)  return;
    swap(a[l], a[l + r >> 1]);
    int x = a[l], i = l;
    for(int j = l+1; j <= r; j++){
        if(a[j] <= x){
            swap(a[j], a[++i]);
        }
    }
    swap(a[i], a[l]);
    Quick_Sort(a, l, i-1);
    Quick_Sort(a, i+1, r);
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n; i++){
        scanf("%d", &a[i]);
    }
    Quick_Sort(a, 0, n-1);
    for(int i = 0;i < n; i++){
        printf("%d ", a[i]);
    }
    return 0;
}
```

+ 快速选择切分，递归进行左右半边的区间排序

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int a[N];

int Quick_Select(int a[], int l, int r){
    swap(a[l], a[l+r>>1]);
    int x = a[l] ,i = l, j = r+1;
    // 如果超出了数据范围break即可
    while(i < j){
        while(a[++i] < x){
            if(i >= r)  break;
        }
        while(a[--j] > x){
            if(j <= l)  break;
        }
        if(i < j)   swap(a[i], a[j]);
    }
    swap(a[l], a[j]);
    return j;
}


void Quick_Sort(int a[], int l, int r){
    if(l >= r)  return;
    int j = Quick_Select(a, l, r);
    // cout << l << ' ' << r << ' ' << j << endl;
    Quick_Sort(a, l, j-1);
    Quick_Sort(a, j+1, r);
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n; i++){
        scanf("%d", &a[i]);
    }
    Quick_Sort(a, 0, n-1);
    for(int i = 0;i < n; i++){
        printf("%d ", a[i]);
    }
    return 0;
}
```



### [786. 第k个小的数](https://www.acwing.com/problem/content/description/788/)

+ 二分的快速选择切分

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5+10;
int a[N];

int Quick_Select(int a[], int l, int r){
    int x = a[l], i = l, j = r + 1;
    while(i < j){
        while(a[++i] < x){
            if(i >= r)   break;
        }
        while(a[--j] > x){
            if(j <= l)   break;
        }
        if(i < j) swap(a[i], a[j]);
    }
    swap(a[l], a[j]);
    return j;
}
int main(){
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    int l = 0, r = n-1;
    while(l <= r){
        int t = Quick_Select(a, l, r);
        if(t == k - 1){
            cout << a[t] << endl;
            return 0;
        }
        else if(t > k - 1){
            r = t - 1;
        }
        else{
            l = t + 1;
        }
    }

    return 0;
    
}
```

+ 高级基于快速排序的快速选择。

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int a[N];

int Quick_Sort(int a[], int l, int r, int k){
    if(l >= r)  return a[l];
    int x = a[l], i = l - 1, j = r + 1;
    while(i < j){
        while(a[++i] < x);
        while(a[--j] > x);
        if(i < j) swap(a[i], a[j]);
    }
    if(j - l + 1 >= k)  Quick_Sort(a, l, j, k);
    else    Quick_Sort(a, j+1, r, k - (j - l + 1));
}

int main(){
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    cout << Quick_Sort(a, 0, n-1, k);
    return 0;
    
}
```

## 归并排序

+ 本质：将两个排序好的队列进行合并的过程。

  ![image-20210429222656482](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210429222656482.png)

### 步骤

+ 确定分界点。
+ 递归划分区间。
+ 双执政归并合并两个有序序列。

### 复杂度分析

+ $T:O(nlogn)$
+ $S:O(n)$，辅助数组进行赋值操作



### [787. 归并排序](https://www.acwing.com/problem/content/789/)

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int a[N];
int temp[N];

void merge(int a[], int l, int mid, int r){
    int i = l, j = mid+1, cur = 0;
    while(i <= mid && j <= r){
        if(a[i] <= a[j]){
            temp[cur++] = a[i++];
        }else{
            temp[cur++] = a[j++];
        }
    }
    while(i <= mid)    temp[cur++] = a[i++];
    while(j <= r)   temp[cur++] = a[j++];
    for(int i = l, j = 0; j < cur; i++, j++){
        a[i] = temp[j];
    }
}

void merge_sort(int a[], int l, int r){
    if(l >= r)  return;
    int mid = l + r >> 1;
    
    merge_sort(a, l, mid);
    merge_sort(a, mid+1, r);
    
    merge(a, l, mid, r);
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    
    merge_sort(a, 0, n-1);
    
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
}
```

### [788. 逆序对的数量](https://www.acwing.com/problem/content/790/)

### 归并思想

![image-20210429225324879](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210429225324879.png)

+ i 前面的数均小于j
+ $T:O(nlogn)$
+ $S:O(n)$

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5+10;
int a[N];
int temp[N];

LL merge_reverse_num(int a[], int l, int r){
    if(l >= r)  return 0;
    int mid = l + r >> 1;
    LL res = merge_reverse_num(a, l, mid) + merge_reverse_num(a, mid+1, r);
    int i = l, j = mid + 1, cur = 0;
    while(i <= mid && j <= r){
        if(a[i] <= a[j]){
            temp[cur++] = a[i++];
        }else{
            // a[i] > a[j] -> + mid - i + 1
            res += mid - i + 1;
            temp[cur++] = a[j++];
        }
    }
    while(i <= mid) temp[cur++] = a[i++];
    while(j <= r)   temp[cur++] = a[j++];
    for(int i = l, j = 0; j < cur; i++, j++){
        a[i] = temp[j];
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("%ld", merge_reverse_num(a, 0, n-1));
    return 0;
}
```

### 暴力(LTE)

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5+10;
int a[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    LL res = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(a[i] > a[j]) res += 1;
        }
    }
    printf("%ld", res);
    return 0;
    
}
```


