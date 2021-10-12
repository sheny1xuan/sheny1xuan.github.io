# lc611.有效三角形的个数


## [611.有效三角形的个数](https://leetcode-cn.com/problems/valid-triangle-number/)

### DFS超时

+ $T:O(2^n)$
``` cpp
class Solution {
public:
    int res = 0;
    void dfs(vector<int>& nums, vector<int>& path, int idx){
        if(path.size() >= 3){            
            int a = path[0], b = path[1], c = path[2];
            // cout << a << ' ' << b << ' ' << c << ' ' << res << endl;
            if((a + b > c) && (abs(a - b) < c)){
                res += 1;
            }
            return ;
        }

        for(int i = idx; i < nums.size(); i++){
            path.push_back(nums[i]);
            dfs(nums, path, i + 1);
            path.pop_back();
        }
    }
    int triangleNumber(vector<int>& nums) {
        vector<int> path;

        dfs(nums, path, 0);

        return res;
    }
};
```
### 暴力枚举

+ O(n^3)
+ 超时

``` python
class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        res = 0
        n = len(nums)
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    fisrt, second, third = nums[i], nums[j], nums[k]
                    if fisrt + second > third and abs(fisrt - second) < third:
                        res += 1
        return res
			
```

### 预排序+双指针

+ 注意逆向扫描，正向扫描不对，逆向扫描可以保证两边之差肯定小于第三边，只需要判断两边之和是否大于第三边。
+ 如果l，r满足条件，则l->r-1 与r构成的三角形都满足。
+ $T:O(n^2)$

``` python
 class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;

        for(int i = nums.size() - 1; i >= 0; i--){
            int l = 0, r = i - 1;
            // 已经保证两数之差小于第三边
            while(l < r){
                // 如果 l + r > nums[i]
                // l -> r - 1 与 r 以及num[i]肯定可以组成三角形
                if(nums[l] + nums[r] > nums[i]){
                    res += r - l;
                    r -= 1;
                }else{
                    // 否则增大l边
                    l += 1;
                }
            }
        }

        return res;
    }
};
```


