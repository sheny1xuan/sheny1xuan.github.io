# acwing基础课ch1-位运算


## 位运算

### 位的统计问题

#### 计算n的二进制表示中第k位

+ 先把第k位移动到最后一位，
+ 然后进行判断。

#### lowbit(x)运算：返回x的最后一位1的位置

+ `-x = ~x + 1` 

+ x & -x
+ 1010 ->10
+ 101000 -> 1000

![image-20210514170434893](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210514170434893.png)

#### 二进制中1的个数

+ 暴力统计每个数中的每一位

``` cpp
#include <iostream>

using namespace std;

const int N = 1e5+10;
int a[N], n;

void cal_bits(int& x){
    int res = 0;
    while(x){
        if(x & 1)   res += 1;
        x = x >> 1;
    }
    x = res;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)  scanf("%d", &a[i]);
    
    for(int i = 0; i < n; i++){
        cal_bits(a[i]);
        printf("%d ", a[i]);
    }
    
    return 0;
    
}
```

+ `x & (-x)->low_bit(x)`得到二进制中最右边的1的位置。

``` cpp
#include <iostream>

using namespace std;

const int N = 1e5+10;
int x, n;

int low_bits(int x){
    return x & (-x);
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        int res = 0;
        while(x) {
            x = x - low_bits(x);
            res += 1;
        }
        cout << res << ' ';
    }
    return 0;
    
}
```




