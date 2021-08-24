# 446.等差数列划分 II - 子序列




## [446. 等差数列划分 II - 子序列](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/)

### 暴力枚举所有子序列

+ 枚举子集就是枚举所有的子序列

``` cpp
typedef long long LL;
class Solution {
public:
    int ans = 0;
    void dfs(vector<int>& nums, vector<LL>& path, int cur){
        if(path.size() >= 3){
            for(int i = 1; i < path.size(); i++){
                if(path[i] - path[i - 1] != path[1] - path[0]){
                    return;
                }
            }
            ans += 1;
        }

        for(int i = cur; i < nums.size(); i++){
            path.push_back(nums[i]);
            dfs(nums, path, i + 1);
            path.pop_back();
        }
    }
    int numberOfArithmeticSlices(vector<int>& nums) {
        vector<LL> path;

        dfs(nums, path, 0);

        return ans;
    }
};
```




