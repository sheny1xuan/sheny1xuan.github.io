# lc600.不含连续1的非负整数




## [600. 不含连续1的非负整数](https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/)

### 暴力位运算

+ $O(n)$

+ 注意运算符优先级：“单算移关与，异或逻条赋”
+ 关系运算符优先级要比位运算优先级要高。

``` cpp
class Solution {
public:
    bool is_ok(int n ){

        for(int i = 0; (1 << i + 1) <= n; i++){
            int cur = 1 << i, next = 1 << i + 1;
            if((cur & n) > 0 && (n & next) > 0){
                return false;
            }
        }
        return true;
    }
    int findIntegers(int n) {
        int ans = 0;

        for(int i = 0; i <= n; i++){
            if(is_ok(i)){
                ans += 1;
            }
        }
        return ans;
    }
};
```

### DFS

+ $O(m)$, m为满足条件的数字个数

``` cpp
class Solution {
public:
    int ans = 0;
    int max_n;
    int findIntegers(int n) {
        ans = 1;
        max_n = n;
        dfs(1);

        return ans;
    }
    void dfs(int x){
        if(x > max_n)   return;
        ans += 1;
        // 最后一位是1,后面只能添加一位1
        if(x & 1 == 1){
            dfs(x << 1);
        }else{  // 最后一位是0,后面可以添加1/0
            dfs(x << 1);
            dfs((x << 1) + 1);
        }
    }
};
```



### 动态规划

+ **数位DP**一般都是询问$[a, b]$区间内，符号条件的个数有多少个。通常需要实现查询$[0, x]$区间内满足条件的个数，则$[a, b]$之间满足的个数应该为$dp[b]-dp[a-1]$
+ 还需要理解

``` cpp
class Solution {
public:
    int get_len(int n ){
        for(int i = 31; i >= 0; i--){
            if(n >> i & 1)  return i;
        }

        return 0;
    }
    int findIntegers(int n) {
        int len = get_len(n);
        int f[50][2];
        f[1][0] = 1, f[1][1] = 2;

        for(int i = 1; i <= 32; i++){
            f[i + 1][0] = f[i][1];
            f[i + 1][1] = f[i][1] + f[i][0];
        }
        int ans = 0, pre = 0;
        for(int i = len; i >= 0; i--){
            int cur = n >> i & 1;
            if(cur == 1)     ans += f[i + 1][0];
            if(cur == 1 && pre == 1)    break;
            pre = cur;
            if(i == 0)   ans += 1;
        }

        return ans;
    }
};
```


