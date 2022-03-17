# lc1646.获取生成数组中的最大值




## [1646. 获取生成数组中的最大值](https://leetcode-cn.com/problems/get-maximum-in-generated-array/)

+ 分两种情况
  + 奇数：`nums[i] = nums[i / 2]`
  + 偶数：`nums[i] = nums[i / 2] + nums[i / 2 + 1]`

### 模拟

``` cpp
class Solution {
public:
    int getMaximumGenerated(int n) {
        if(n <= 0)  return 0;

        vector<int> nums(n + 1, 0);
        nums[1] = 1;
        int res = 1;
        for(int i = 2; i <= n; i++){
            if(i % 2 == 0){
                nums[i] = nums[i / 2];
            }else{
                nums[i] = nums[i / 2] + nums[i / 2 + 1];
            }
            res = max(res, nums[i]);
        }

        return res;
    }
};
```




