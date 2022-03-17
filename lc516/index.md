# lc516.最长回文子序列




## [516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

### 暴力

+ 枚举所有的子序列(子集)
+ $T:O(n2^n)$

``` cpp
class Solution {
public:
    int ans = 1;
    void dfs(string& s, string& path, int idx){
        // cout << path << endl;
        bool isok = true;
        for(int i = 0, j = path.size() - 1; i < j; i++, j--){
            if(path[i] != path[j]){
                isok = false;
                break;
            }
        }
        if(isok)    ans = max(ans, int(path.size()));
        for(int i = idx; i < s.size(); i++){
            path.push_back(s[i]);
            dfs(s, path, i + 1);
            path.pop_back();
        }
    }
    int longestPalindromeSubseq(string s) {
        string path;

        dfs(s, path, 0);

        return ans;
    }
};
```

### 动态规划

+ 状态定义：$f[i][j]$表示$i,j$之间的最长回文子序列的长度
+ 状态转移:$f[i][j] = f[i+1][j-1] + 2,f[i]=f[j]$,$f[i][j] = max(f[i+1][j], f[i][j-1]), f[i]!=f[j]$
+ 注意这里状态转移会用到$i+1$所以不能从小到大进行枚举，需要大到小进行枚举
+ $T:O(n^2)$

``` cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();

        vector<vector<int>> f(n, vector<int>(n, 0));

        for(int i = n - 1; i >= 0; i--){
            f[i][i] = 1;
            for(int j = i + 1; j < n; j++){
                if(s[i] == s[j]){
                    f[i][j] = f[i + 1][j - 1] + 2;
                }else{
                    f[i][j] = max(f[i][j - 1], f[i + 1][j]);
                }
            }
        }

        return f[0][n - 1];
    }
};
```




