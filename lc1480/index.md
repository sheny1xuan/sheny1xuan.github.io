# lc1480. 一维数组的动态和




## [1480. 一维数组的动态和](https://leetcode-cn.com/problems/running-sum-of-1d-array/)

### 前缀和

+ pre[i]表示前i个数的和
+ 返回`i+1->end`

``` cpp
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n + 1, 0);
        for(int i = 1; i <= n; i++){
            pre[i] = pre[i - 1] + nums[i - 1];
        }

        return vector<int>(pre.begin() + 1, pre.end());
    }
};
```


