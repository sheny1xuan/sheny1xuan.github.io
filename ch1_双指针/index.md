# acwing基础课ch1-双指针


## 双指针

### 两个序列双指针

归并排序

### 一个序列同向双指针

双指针利用某种性质将暴力(n^2)的算法优化到O(n).

![image-20210510220243933](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210510220243933.png)

#### 实现split()



#### 最长连续不重复子序列

+ 暴力做法：枚举以i为结尾的所有数组，j表示离当前i最远的不重复数组。

![image-20210510222517511](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210510222517511.png)

+ 暴力做法：TLE

``` cpp
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;
const int N = 1e5+10;
int a[N];

int main(){
    int res = 0, n = 0;
    
    cin >> n;
    for(int i = 0; i < n; i++)  scanf("%d", &a[i]);
    
    for(int i = 0; i < n; i++){
        unordered_set<int> uset;

        for(int j = i; j >= 0; j--){
            // check
            if(uset.find(a[j]) != uset.end()){
                break;
            }else{
                res = max(i - j + 1, res);
            }
            uset.insert(a[j]);
        }
        
    }
    cout << res;
    
    return 0;
}
```

+ 双指针
+ 利用反证法，如果以i结尾的子数组最长不重复对应左节点为j，那么i+1结尾最长不重复数组对应左节点大于 等于j。且如果左节点大于j的话，一定是由于新加入的i+1导致的。

``` cpp
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;
const int N = 1e5+10;
int a[N];

int main(){
    int res = 0, n = 0;
    
    cin >> n;
    for(int i = 0; i < n; i++)  scanf("%d", &a[i]);
    
    unordered_set<int> uset;
    for(int i = 0, j = 0; i < n; i++){
        // 删除j, 直到当前j -> i 中没有重复数字。
        while(j < i && uset.find(a[i]) != uset.end()){
            uset.erase(a[j]);
            j++;
        }   
        // 产生的重复是由a[i]导致的
        uset.insert(a[i]);
        res = max(i - j + 1, res);
    }
    cout << res;
    
    return 0;
}
```

#### 数组元素的目标和

> 给定两个升序排序的有序数组 A 和 B，以及一个目标值 x。
>
> 求A[i] + B[j] = x

+ i正序枚举，j倒序枚举，如果$A[i] + B[j] > t$则$A[i+1]+B[j]>t$,所以j可以从$j+1$开始枚举。

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int a[N], b[N];

int main(){
    int n, m, t;
    cin >> n >> m >> t;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < m; i++){
        scanf("%d", &b[i]);
    }
    for(int i = 0, j = m - 1; i < n; i++){
        while(j >= 0 && a[i] + b[j] > t)    j--;

        if(a[i] + b[j] == t){
            printf("%d %d", i, j);
            break;
        }    
        
    }
    
    return 0;
}
```




