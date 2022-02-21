# lc1109.航班预订统计




## [1109. 航班预订统计](https://leetcode-cn.com/problems/corporate-flight-bookings/)

+ 差分用于快速处理`区间的增量`。
+ 当我们需要对某一数组$a[n]$,区间$[l,r]$之间添加一个增量$inc$时，也就是对差分数组$d[n]$进行$d[l]+= inc, d[r + 1]-=inc$，之后对差分数组求前缀和，便可以对原数组进行快速的增量处理
+ $T:O(m + n)$

``` cpp
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n, 0);
        for(auto &book: bookings){
            int x = book[0] - 1, y = book[1] - 1, w = book[2];
            ans[x] += w;
            if(y < n - 1)   ans[y + 1] -= w;
        }

        for(int i = 1; i < ans.size(); i++){
            ans[i] += ans[i - 1];
        }

        return ans;
    }
};

```




