# lc292.Nim 游戏




## [292. Nim 游戏](https://leetcode-cn.com/problems/nim-game/)

### 博弈论

+ 博弈论问题一般是两方进行对抗的问题
+ 首先如果有3枚以下的石头，那么我方一定获胜。如果有4枚石头，我方一定能获胜。
+ 考虑5颗石头的情况，由于每次只能拿$1-3$颗石头，所以我们应该考虑$f[i],i \in \{4,3,2\}$，一旦其中有必败的情况，表示我方一定获胜。

``` cpp
class Solution {
public:
    bool canWinNim(int n) {
        vector<int> f(n + 1, true);
        if(n >= 4)  f[4] = false;

        for(int i = 5; i <= n; i++){
            f[i] = false;
            for(int j = i - 1; i - j <= 3; j--){
                if(f[j] == false){
                    f[i] = true;
                }
            }

        }

        return f[n];
    }
};
```

### 找规律

+ 我们可以发现当石头的数量是4的倍数时，我们一定失败，否则一定会获胜。

``` cpp
class Solution {
public:
    bool canWinNim(int n) {
        vector<int> f(4, true);
        f[0] = false;
        
        return f[n % 4];
    }
};
```

### 类似题目进阶

+ #### [877. 石子游戏](https://leetcode-cn.com/problems/stone-game/)


