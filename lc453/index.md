# lc453.最小操作次数使数组元素相等




## [453.最小操作次数使数组元素相等](https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements/)

1. 使其他每个元素就是相当于对一个元素减1
2. 操作到最后所有元素应该等于最小的元素。

``` cpp
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int min_ele = *min_element(nums.begin(), nums.end());
        int ans = 0;

        for(auto& x: nums) {
            ans += x - min_ele; 
        }

        return ans;
    }
};
```




