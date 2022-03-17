# lc447.回旋镖的数量




## [447. 回旋镖的数量](https://leetcode-cn.com/problems/number-of-boomerangs/)

+ 计算两两点之间的距离
+ 假如相同距离的点为$n$个的话，则满足条件的三元组有$A_{n}^{2} = n * (n - 1)$个

``` cpp
class Solution {
public:
    // A_{n}^{2} = n * (n - 1)
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int ans = 0;

        for(auto& p1: points){
            unordered_map<int, int> mp;
            for(auto& p2: points){
                int dis = (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
                mp[dis] += 1;
            }
            for(auto& [_, cnt]: mp){
                cnt *= cnt - 1;
                ans += cnt;
            }
        }

        return ans;
    }
};
```


