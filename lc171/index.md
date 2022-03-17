# lc171.Excel表列序号


## [171. Excel 表列序号](https://leetcode-cn.com/problems/excel-sheet-column-number/)

### 正向遍历

``` cpp
class Solution {
public:
    int titleToNumber(string columnTitle) {
        // 正向遍历->叠加权重
        int ans = 0, n = columnTitle.size();

        for(int i = 0; i < n; i++){
            ans = columnTitle[i] - 'A' + ans * 26 + 1;
        }

        return ans;
    }
};
```

### 反向遍历

+ 计算每一位的权重

``` cpp
class Solution {
public:
    int titleToNumber(string columnTitle) {
        // 反向->计算位权重
        int ans = 0, n = columnTitle.size();
        long long weight = 1;
        for(int i = n - 1; i >= 0; i--){
            ans += (columnTitle[i] - 'A' + 1) * weight;
            weight *= 26;
        }

        return ans;
    }
};
```




