# lc528.按权重随机选择




## [528. 按权重随机选择](https://leetcode-cn.com/problems/random-pick-with-weight/)

+ 题目的意思是根据下标不同的权重产生随机数
+ $w[i]$代表产生随机数$i$的权重
+ 首先将计算所有数的和，然后依次计算前缀和，均匀分布产生的随机数$randnum$，在两个前缀和$[pre[i-1], pre[i])$之间的范围代表产生该数$i$。

+ 如$w={1,2,3,4}$，分别代表产生$p_{0}=\frac{1}{10},p_{1}=\frac{2}{10}，p_{2}=\frac{3}{10}，p_{3}=\frac{4}{10}$
  + 首先计算前缀和数组$pre=\{0,1,3,6,10\}$
  + 之后通过均匀分布产生一个在$[0,10)$之间的随机数$randnum$,根据$randnum$的取值重新产生新的随机数$i$，$randnum\in[pre[i-1],pre[i])$，表示产生随机数$i-1$
  + 也就是在前缀和数组中找到第一个大于$randnum$的前缀和下标$i$，返回$i-1$，或者找到最后一个小于等于$randnum$的前缀和下标$i$，并且返回$i$

### 第一个大于randnum的前缀和数组下标

+ $T:O(logn)$

``` cpp
class Solution {
public:
    vector<int> pre = {0};
    int range = 0;

    Solution(vector<int>& w) {
        for(auto w_: w){
            range += w_;
            pre.push_back(range);
        }
    }
    
    int pickIndex() {
        int randnum = rand() % range;

        int idx = upper_bound(pre.begin(), pre.end(), randnum) - pre.begin();

        return idx - 1;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```

### 最后一个小于等于randnum的数

``` cpp
class Solution {
public:
    vector<int> pre = {0};
    int range = 0;

    Solution(vector<int>& w) {
        for(auto w_: w){
            range += w_;
            pre.push_back(range);
        }
    }
    
    int pickIndex() {
        int randnum = rand() % range;
        // 最后一个小于等于randnum的下标i，返回i
        int l = 0, r = pre.size() - 1;
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(pre[mid] <= randnum){
                l = mid;
            }else{
                r = mid - 1;
            }
        }

        return l;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```




