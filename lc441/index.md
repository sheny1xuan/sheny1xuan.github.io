# lc441.排列硬币




## [441.排列硬币](https://leetcode-cn.com/problems/arranging-coins/)

#### 二分查找

+ `1-k`行求和相当于等差数列求和`s=(k+1)k/2`
+ 目的是求出来最后一个行的和小于等于n的行。

+ 注意会爆int
+ $T:O(n)$

``` cpp
class Solution {
public:
    int arrangeCoins(int n) {
        int l = 1, r = n;
        if(n == 1)  return 1;
        // 找最后一个小于等于n的数
        while(l < r) {
            int mid = (r - l + 1 >> 1) + l;
            if((long long) mid * (mid + 1) <= n * 2ll) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }

        return l;
    }
};
```




