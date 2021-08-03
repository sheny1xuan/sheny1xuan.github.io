# lc581.最短无序连续子数组


## [581. 最短无序连续子数组](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)

### 排序+双指针

+ T:O(nlogn)

``` cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> cpy(nums.begin(), nums.end());
        sort(cpy.begin(), cpy.end());
        
        int l = -1, r = nums.size();
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == cpy[i]){
                l = i;
            }else{
                break;
            }
        }

        if(l == nums.size() - 1)  return 0;

        for(int i = nums.size() - 1; i >= 0; i--){
            if(nums[i] == cpy[i]){
                r = i;
            }else{
                break;
            }
        }

        return r - l - 1;
    }
};
```

#### 找规律

+ T:O(n)
+ 一次遍历，最大的数决定右边界，最小的数决定左边界。

``` cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        // 一次遍历，最大的数决定右边界，最小的数决定左边界。
        // 数组可以分为3部分numsA, numsB, numsC;
        // numsB重新排序可以将整个数组变为升序排列。

        // 对于numsA中每一个数numsA[i] < numB[j]/numsC[j], j > i;
        // 从右向左遍历数组，记录右边的最小值
        // 如果当前数比最小值大，则该数的位置为左边界
        int minx = INT_MAX, left = -1;
        for(int i = nums.size() - 1; i >= 0; i--){
            if(minx < nums[i]){
                left = i;
            }else{
                minx = nums[i];
            }
        }

        int maxx = INT_MIN, right = nums.size() - 1;
        for(int i = 0; i < nums.size(); i++){
            if(maxx > nums[i]){
                right = i;
            }else{
                maxx = nums[i];
            }
        }
        if(left == -1)  return 0;
        return right - left + 1;
    }
};
```




