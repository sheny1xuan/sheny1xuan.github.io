# 152. 乘积最大子数组




### [152. 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray/)

+ `f[i]`以第`i`个数字结尾的乘积最大的子数组，与和最大的子数组不同，乘积最大的子数组由两部分转移而来。
+ `nums[i - 1] < 0`, $f[i] = max(fmin[i - 1] * nums[i - 1], nums[i - 1])$
+ `nums[i - 1] > 0`,$f[i] = max(fmax[i - 1] * nums[i - 1], nums[i - 1])$

``` cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> fmax(n + 1, 0);
        vector<int> fmin(n + 1, 0);
        fmax[0] = 1;
        fmin[0] = 1;

        for (int i = 1; i <= n; i++) {
            fmax[i] = max(nums[i - 1],
                    max(fmax[i - 1] * nums[i - 1], fmin[i - 1] * nums[i - 1]));
            fmin[i] = min(nums[i - 1],
                    min(fmax[i - 1] * nums[i - 1], fmin[i - 1] * nums[i - 1]));
        }

        return *max_element(fmax.begin() + 1, fmax.end());
    }
};
```


