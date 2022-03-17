# lc583.两个字符串的删除操作




## [583.两个字符串的删除操作](https://leetcode-cn.com/problems/delete-operation-for-two-strings/)

### 最长公共子序列

+ 给定两个字符串`word1`和`word2`，找出使两个字符串变为相同需要删除的字母的最少的个数
+ 可以把这个问题转换为最长公共子序列问题，假设`word1.size() = n,word2.size() = m`，最长公共子序列的长度为`k`，那么两个字符串需要删除的最少的字母的个数就是等于`n + m - 2k`
+ 最长公共子序列动态规划状态表示`f[i][j]`表示长度为`i`的`word1`与长度为`j`的`word2`的最长公共子序列的长度
+ 对于长度分别为`i,j`，`word1[i - 1]==word2[j - 1]`时,`f[i][j] = f[i - 1][j - 1] + 1`，否则为`max(f[i-1][j], f[i][j-1])`

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210925144855922.png" alt="image-20210925144855922" style="zoom:50%;" />

``` cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        // 最长公共子序列
        // f[i][j]
        // word1长度为i，word2长度为j的最长公共子序列
        int n = word1.size(), m = word2.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));

        f[0][0] = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(word1[i - 1] == word2[j - 1]){
                    f[i][j] = f[i - 1][j - 1] + 1;
                }else{
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);
                }
            }
        }

        return n - f[n][m] + m - f[n][m];
    }
};
```


