# lc650.只有两个键的键盘




## [650.只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/)

### 动态规划

+ $O(n^2)$
+ 考虑状态$f[i]$为输出恰好为$i$个$A$时的最少操作此时
+ ${i \% j == 0}, f[i] = min{(f[i], f[j] + i / j)}$，对$j$复制一次，粘贴$i/j$次

``` cpp
class Solution {
public:
    int minSteps(int n) {
        vector<int> f(n + 1, 0);

        for(int i = 2; i <= n; i++){
            f[i] = INT_MAX;
            for(int j = 1; j < i; j++){
                if(i % j == 0){
                    f[i] = min(f[i], f[j] + i / j);
                }
            }
        }

        return f[n];
    }
};
```

### 动态规划优化

+ $O(n\sqrt{n})$

``` cpp
class Solution {
public:
    int minSteps(int n) {
        vector<int> f(n + 1, 0);

        for(int i = 2; i <= n; i++){
            f[i] = INT_MAX;
            for(int j = 1; j * j <= i; j++){
                if(i % j == 0){
                    int a = j, b = i / j;
                    f[i] = min(f[i], f[a] + b);
                    f[i] = min(f[i], f[b] + a);
                }
            }
        }

        return f[n];
    }
};
```


