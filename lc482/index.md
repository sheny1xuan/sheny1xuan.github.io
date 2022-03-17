# lc482.密钥格式化




## [482. 密钥格式化](https://leetcode-cn.com/problems/license-key-formatting/)

### 逆序遍历

+ 逆序遍历可以不必计算因为不够而产生的余数部分。
+ 注意原地操作，由于字符串添加或者删除一个字符的时间复杂度是$O(n)$，所以尽量不原地操作。

``` cpp
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        int n = s.size();
        string res = "";
        for(int i = n - 1; i >= 0; ){
            int j = 0;
            while(j < k && i >= 0){
                if(s[i] != '-'){
                    res.push_back(toupper(s[i]));
                    j += 1;
                }
                i -= 1;
            }

            res.push_back('-');
        }

        int idx = 0;
        while(res.back() == '-'){
            res.pop_back();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```




