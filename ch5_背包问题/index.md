# 

# 背包问题

## 01背包问题

### 问题描述

![image-20210615101106667](../pic/image-20210615101106667.png)

+ `dp[i][v]`表示前`i`个物品，总体积小于等于`v`的最大质量。
+ 状态表示
  + 集合表示：只从前i个物品中选，总体积小于等于v的所有选法
  + 属性：max，min，数量
+ 状态计算：集合的划分

![image-20210615103129168](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615103129168.png)

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, V;
int v[N], w[N];
int f[N][N];

int main(){
    cin >> n >> V;
    
    for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    
    // 初始条件f[0][v] = 0
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= V; j++){
            // 1.不包含第i件物品
            f[i][j] = f[i - 1][j];
            // 2.包含第i件物品
            if(j >= v[i]){
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            }
        }
    }
    
    cout << f[n][V] << endl;
    
    return 0;

}
```

+ 滚动数组
+ 倒着枚举体积v

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, V;
int v[N], w[N];
int f[N];

int main(){
    cin >> n >> V;
    
    for(int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    
    // 初始条件f[v] = 0
    
    for(int i = 1; i <= n; i++){
        // 倒着枚举fi只与fi-1有关，且在同一侧
        for(int j = V; j >= v[i]; j--){
            // 1.不包含第i件物品
            // 2.包含第i件物品
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    
    cout << f[V] << endl;
    
    return 0;

}
```

## 完全背包问题

### 问题描述

![image-20210615105423819](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615105423819.png)

+ 状态计算

![image-20210615110055596](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615110055596.png)

+ 朴素做法

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N][N];

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++) cin >>v[i] >> w[i];
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 0; k * v[i] <= j; k++){
                f[i][j] = max(f[i - 1][j - k * v[i]] + k * w[i], f[i][j]);
            }
        }
    }
    
    cout << f[n][m] << endl;
    
    return 0;
}
```

![image-20210615111908094](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615111908094.png)

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N][N];

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++) cin >>v[i] >> w[i];
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            f[i][j] = f[i - 1][j];
            if(j >= v[i]){
                f[i][j] = max(f[i][j], f[i][j - v[i]] + w[i]);
            }
        }
    }
    
    cout << f[n][m] << endl;
    
    return 0;
}
```

+ 滚动数组优化

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int v[N], w[N];
int f[N];

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++) cin >>v[i] >> w[i];
    
    for(int i = 1; i <= n; i++){
        for(int j = v[i]; j <= m; j++){
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    
    cout << f[m] << endl;
    
    return 0;
}
```

## 多重背包问题

### 问题描述

![image-20210615115300988](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615115300988.png)

![image-20210615115237119](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615115237119.png)

+ 朴素做法
+ $O(mns)$

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;
int v[N], w[N], s[N];
int f[N][N];

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++) cin >> v[i] >> w[i] >> s[i];
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 0; k <= s[i] && k * v[i] <= j; k++){
                f[i][j] = max(f[i][j], f[i - 1][j - k * v[i]] + k * w[i]);
            }
        }
    }
    
    cout << f[n][m] << endl;
    
    return 0;
    
}
```

+ **二进制优化**
+ 用多个子物品代替该物品，然后对这些重新分类的物品进行一次01背包
+ 比如`s=200, 1, 2, 4, 8, 16, 32, 64, 73`
+ $s:1, 2, 4, 8, 16, ..., 2^k, x;s < 2^{k+1}$
+ $T:O(mnlogs)$

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 25000, M = 2010;
int n, m;
int v[N], w[N];
int f[N];

int main(){
    cin >> n >> m;
    
    int cnt = 0;
    // 二进制优化进行拆分1, 2, 4, 8.. 
    for(int i = 0; i < n; i++){
        int a, b, s;
        cin >> a >> b >> s;
        for(int k = 1; k <= s; k *= 2){
            cnt ++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
        }
        if(s){
            cnt ++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
        
    }
    
    n = cnt;
    // 01背包
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= v[i]; j--){
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    
    cout << f[m] << endl;
    
    return 0;
}
```

## 分组背包问题

### 问题描述

![image-20210615150223595](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615150223595.png)

![image-20210615151340393](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210615151340393.png)

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int v[N][N], w[N][N], s[N];
int f[N];
int n, m;

int main(){
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++){
        cin >> s[i];
        for(int j = 1; j <= s[i]; j++){
            cin >> v[i][j] >> w[i][j];
        }
    }
    
    // 01背包
    for(int i = 1; i <= n; i++){
        for(int j = m; j >= 0; j--){
            // 每一组找出一个
            for(int k = 1; k <= s[i]; k++){
                if(j >= v[i][k])    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]); 
            }
        }
    }
    
    cout << f[m] << endl;
    
    return 0;
}
```


