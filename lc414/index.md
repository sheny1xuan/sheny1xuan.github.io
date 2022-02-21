# lc414.第三大的数




## [414.第三大的数](https://leetcode-cn.com/problems/third-maximum-number/)

+ 设置三个哨兵a，b，c，依次为$a>b>c$如果一个数满足在区间内，则可以更新对应的数。
+ 如果`num > a, c = b, b = a, a = num`
+ 如果`a > num > b, c = b, b = num`
+ 如果`b > num > c, c = num`

``` cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long a = LONG_MIN, b = LONG_MIN, c = LONG_MIN;

        for(auto& num: nums) {
            if(num > a) {
                c = b;
                b = a;
                a = num;
            } else if (num > b && num < a) {
                c = b;
                b = num;
            } else if (num > c && num < b) {
                c = num;
            }
        }

        return c == LONG_MIN ? a : c;
    }
};
```




