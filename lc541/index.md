# lc541.反转字符串II




## [541. 反转字符串 II](https://leetcode-cn.com/problems/reverse-string-ii/)

+ 按照题意进行翻转即可，使用reverse传入泛型指针进行翻转

``` cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size(), cur = 0;
        while(cur + 2 * k < n){
            reverse(s.begin() + cur, s.begin() + cur + k);
            cur += 2 * k;
        }

        if(n - cur < k){
            reverse(s.begin() + cur, s.end());
        }else{
            reverse(s.begin() + cur, s.begin() + cur + k);
        }

        return s;
    }
};
```




