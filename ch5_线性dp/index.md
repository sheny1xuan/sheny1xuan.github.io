# 

# 线性DP

## 数字三角形问题

### 问题描述

![image-20210618112232813](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210618112232813.png)

### DP

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210618113134149.png" alt="image-20210618113134149" style="zoom:67%;" />

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510;

int a[N][N], n;
int f[N][N];

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++) cin >>a[i][j];
    }
    // 注意初始化从零开始，并且结束在i+1结束
    // 因为最左边0是非法值
    // 最右边i+1是非法值
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i + 1; j++) f[i][j] = -0x3f3f3f3f;
    }
    f[1][1] = a[1][1];
    
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= i; j++){
            f[i][j] = max(f[i - 1][j - 1] + a[i][j], f[i - 1][j] +a[i][j]);
        }
    }
    
    int res = f[1][1];
    for(int i = 1; i <= n; i++){
        res = max(f[n][i], res);
    }
    
    cout << res << endl;
    
    return 0;
}
```

## 最长上升子序列

### 问题描述

+ N < 1000

![image-20210622114320085](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210622114320085.png)

### 问题解决

![image-20210622114656603](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210622114656603.png)

+ 时间复杂度：状态数目*计算数目$O(n^2)$

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1100;

int a[N];
int f[N];

int main(){
    int n; 
    cin >> n;
    
    for(int i = 1; i <= n; i++ )    cin >> a[i];
    
    int ans = 1;
    for(int i = 1; i <= n; i++){
        f[i] = 1;
        for(int j = 1; j < i; j++){
            if(a[i] > a[j]) f[i] = max(f[j] + 1, f[i]);
        }
        
        ans = max(ans, f[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
```

## 最长上升子序列 II

### 问题描述

![image-20210622204927693](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210622204927693.png)

+ 注意此题目是上一题的时间优化，时间复杂度是$O(nlogn)$
+ 二分+贪心思想，十分巧妙。

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5+10;

int a[N];

int find(vector<int>& stk, int t){
    int l = 0, r = stk.size() - 1;
    
    while(l < r){
        int mid = l + r >> 1;
        if(stk[mid] >= t){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    
    return l;
}

int main(){
    int n;
    
    cin >> n;

    for(int i = 0;i < n; i++ )     cin >> a[i];
    // 模拟栈，不使用栈是为了使用二分
    // 快速找出第一个大于等于当前值的数
    // 栈内单调递增
    vector<int> stk = {a[0]};
    
    for(int i = 1; i < n; i++){
        // 贪心，找到大于栈顶的数加入栈内
        if(a[i] > stk.back()){
            stk.push_back(a[i]);
        }
        else{
            // 为什么这么做，其实按道理来应该删除从第一个大于等于到最后的所有数
            // 但是需要最长的长度，无法保证删除之后话会比当前的长度更长
            // 替换该数既保证了贪心思想之后可以从此获得更长长度，有保证了当前长度。
            // *lower_bound(stk.begin(), stk.end(), a[i]) = a[i];
            int idx = find(stk, a[i]);
            stk[idx] = a[i];
        }
    }
    
    cout << stk.size() << endl;
    
    return 0;
}

```

## 最长公共子序列问题

### 题目描述

![image-20210624113418514](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210624113418514.png)

![image-20210624113351118](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210624113351118.png)

+ 求最大最小的属性不一定要保证不重复，但一定要保证不漏掉

``` cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int N = 1100;
int f[N][N];
char s1[N], s2[N];

int main()
{
    int n, m;
    
    cin >> n >> m >> s1 + 1 >> s2 + 1;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            f[i][j] = max(f[i-1][j], f[i][j-1]);
            if(s1[i] == s2[j]){
                f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
            }
        }
    }
    
    cout << f[n][m] << endl;
    
    return 0;
}
```


