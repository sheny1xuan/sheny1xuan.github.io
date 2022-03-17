# lc413.等差数列划分




## [413. 等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)

### 暴力

+ 枚举所有的子数组，之后对每一个数组进行判断是否满足等差数列的条件

+ $O(n^3)$：$O(n^2)$枚举所有数组，$O(n)$判断该数组是否满足条件

``` cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(isOk(i, j, nums)){
                    res += 1;
                }
            }
        }

        return res;
    }

    bool isOk(int x, int y, vector<int>& nums){
        if(y - x + 1 < 3)  return false;
        int d = nums[x + 1] - nums[x];

        for(int i = x + 2; i <= y; i++){
            if(nums[i] - nums[i - 1] != d){
                return false;
            }
        }

        return true;
    }
};
```

### 双指针

+ 枚举以$i$为起点的最长等差子序列
+ $i -> j$为长度为$len$的等差数列
+ 长度为$len$的等差数列包含$\sum_{k = 3}^{k = len}$个的长度至少为3的等差子序列
+ 其求和$\sum_{k = 3}^{k = len}$为$a1 = 1, an = len - 3 + 1$的等差数列。

``` cp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int res = 0, n = nums.size();

        // 枚举以i为起点的最长等差子序列
        for(int i = 0; i < n - 1; ){
            int j = i + 1;
            int d = nums[j] - nums[i];
            // i -> j为等差数列
            while(j + 1 < n && nums[j + 1] - nums[j] == d){
                j++;
            }
            int len = j - i + 1;
            // 这里要注意：i之后为上一个等差数列的最后一个数j
            // 不是j+1,因为与j与j+1不能延长上一个等差数列，但是他们可以构成新的等差数列。
            // 如 1 2 3 5 7
            // 1 2 3 -> i = 0, j = 2 
            // 之后
            // 3 5 7 -> i = 2, j = 4
            i = j;

            if(len < 3) continue;

            // i -> j 构成了长为len的等差数列
            // 长度为len的等差数列包含$\sum_{k = 3}^{k = len}$所有的子序列
            // 其求和为$a1 = 1, an = len - 3 + 1$的等差数列
            int a1 = 1, an = len - 3 + 1;
            res += (a1 + an) * an / 2;
        }

        return res;
    }
};
```




