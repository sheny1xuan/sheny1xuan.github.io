# lc673.最长递增子序列的个数




## [673.最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)

+ 维护一个计数数组，记录每个递增子序列的个数。
  + 按照最长递增子序列的遍历方式，如果$nums[i] > nums[j]$
  + 如果$f[i] == f[j] + 1$说明加入当前为以$i$结尾的最长子序列的话，那么可以构成一个新的子序列，可以在$cnt[i]$中叠加$cnt[j]$（不能加一，需要加所有以$j$结尾最长递增子序列的个数）
  + 如果$f[i] < f[j] + 1$说明加入当前为以$i$结尾的最长子序列的长度可以被更新，可以更新$cnt[i]$为$cnt[i] = cnt[j]$。
+ 最后，如果$f[i] = maxn$，最终结果叠加$cnt[i]$，否则用$cnt[i]$更新最终结果
+ $T:O(n^2)$

``` cpp
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 0, maxn = 0;
        vector<int> f(n), cnt(n);

        for(int i = 0; i < n; i++){
            f[i] = 1;
            cnt[i] = 1;

            for(int j = 0; j < i; j++){
                if(nums[j] <  nums[i]){
                    if(f[j] + 1 == f[i]){
                        // 如果f[j] + 1 = f[i],表示当前这种又出现了一次最长递增子序列。
                        // 叠加j的数量
                        cnt[i] += cnt[j];
                    }else if(f[j] + 1 > f[i]){
                        // 如果f[j] + 1 > f[i],表示当前以i结尾的最长递增子序列可以更新。
                        cnt[i] = cnt[j];
                        f[i] = f[j] + 1;
                    }
                }
            }

            if(maxn == f[i]){
                ans += cnt[i];
            }else if(f[i] > maxn){
                maxn = f[i];
                ans = cnt[i];
            }
        }

        return ans;
    }
};
```


