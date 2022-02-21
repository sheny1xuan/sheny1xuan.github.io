# lc29.两数相除






## [29.两数相除](https://leetcode-cn.com/problems/divide-two-integers/)

### 二分查找+快速乘

+ 快速乘：根据每一位的权重进行乘法。
+ 对于$y/x$查找第一个$x*?<y$的数。
+ $T:O(log^2n)$,快速乘$log(n)$，二分查找$log(n)$,$n$为32位数字表示的最大的数字。

``` cpp
class Solution {
public:
    using ll = long long;
    int divide(int dividend, int divisor) 
        bool neg = false;
        if((dividend ^ divisor) < 0) {
            neg = true;
        }

        ll x = dividend, y = divisor;
        if(x < 0) {
            x = -x;
        }
        if(y < 0) {
            y = -y;
        }

        // 找到最后一个y*? <= x
        ll l = 0, r = x;

        while(l < r) {
            ll mid = (r - l + 1 >> 1) + l;
            cout << mid << endl;
            if(mul(mid, y) <= x) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        
        l = neg ? -l : l;

        if(l > INT_MAX) return INT_MAX;
        return l;
    }
    ll mul(ll x, ll y) {
        ll ans = 0;
        while(x) {
            if(x & 1) {
                ans += y;
            } 
            x >>= 1;
            y += y;
        }

        return ans;
    }
    
};
```




