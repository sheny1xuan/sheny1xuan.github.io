# lc162.寻找峰值




## [162. 寻找峰值](https://leetcode-cn.com/problems/find-peak-element/)

### 寻找最大值

+ 依照题意$-1,n$位置都是比任意值要小，而且数组中没有任意两个数字完全相同，所以

最大值肯定是目标值之一。

``` cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return max_element(nums.begin(), nums.end()) - nums.begin();
    }
};
```

### 二分查找

+ 考虑一下几种情况
  + $nums[i] > nums[i - 1] \&\& nums[i] > nums[i + 1]$：目标值，满足要求
  + $nums[i] > nums[i - 1] \&\& nums[i] < nums[i + 1]$：向右移动
  + $nums[i] < nums[i - 1] \&\& nums[i] > nums[i + 1]$：向左移动
  + $nums[i] < nums[i - 1] \&\& nums[i] < nums[i + 1]$：可以向左也可以向右移动
+ 如果我们选择第四种情况向右移动的话，不满足条件的三种情况可以化简为
  + $nums[i] > nums[i + 1]$：向左移动
  + $nums[i] > nums[i + 1]$：向右移动

+ 那么对于区间$[l, r]$，如果$mid$满足条件，直接返回即可
+ 不满足条件，我们需要对$mid$进行判断，如果$nums[i] > nums[i + 1]$，则答案肯定在左半边$[i + 1, r]$直接舍去，右半边同理

+ 注意这里有`c++`匿名函数的写法
  + [外部变量访问方式说明符] (参数表) -> 返回值类型
    {
      语句块
    }
  + []:外部变量访问方式说明符可选`=`(定义在外部的变量不可以在语句块内修改),`&`(定义在外部的变量可以在语句块内修改)

``` cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;

        // 方便进行判断，如果超出数组索引，返回{0, 0}, 否则返回{1, nums[i]},那么超出索引肯定小于索引内的数
        auto get = [&](int x) -> pair<int, int> {
            if(x == -1 || x == n){
                return {0, 0};
            }
            return {1, nums[x]};
        };

        // 肯定会有满足条件的下标，则遍历所有下标
        while(l <= r){
            int mid = l + r >> 1;
            if(get(mid) > get(mid - 1) && get(mid) > get(mid + 1)){
                return mid;
            }else if(get(mid) > get(mid + 1)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }

        return -1;
    }
};
```


