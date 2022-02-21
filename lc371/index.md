# lc371.两整数之和




## [371.两整数之和](https://leetcode-cn.com/problems/sum-of-two-integers/)

### 不使用+进行加法运算

+ 两个数无进位加法的结果是`a^b`
+ 两个数产生进位的位是`a&b`，进位的结果就是`(a&b)<<1`，重复计算进位与原来数相加的结果，直到进位为0.
+ 需要注意的是，进位左移的结果可能超过`INT_MAX`，所以需要先将其转换为`unsigned int`进行使用。

``` cpp
class Solution {
public:
    int getSum(int a, int b) {
        while(b != 0){
            // 产生进位的位为a&b, 
            unsigned int carry = (unsigned int)(a & b) << 1;
            a = a ^ b;
            b = carry;
        }

        return a;
    }
};
```




