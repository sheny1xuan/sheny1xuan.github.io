# lc318.最大单词长度乘积




## [318.最大单词长度乘积](https://leetcode-cn.com/problems/maximum-product-of-word-lengths/)

### 位运算哈希

+ 考虑暴力求解，对每一个字符串进行哈希，之后遍历剩余的字符串检查是否重复 $T:O(n^2l)$,$n$是字符串的个数,$l$是每个字符串的平均长度，不能通过。
+ 提前对每个字符串进行哈希，利用26位存储每个字符哈希的结果。$T:O(26*n^2 + nl)$

``` cpp
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        int ans = 0;
        vector<int> f(n, 0);
        for (int i = 0; i < n; i++) {
            for (auto& c: words[i]) {
                f[i] |= 1 << (c - 'a');
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool ok = true;
                for (int k = 0; k < 26; k++) {
                    int x = (f[i] & (1 << k)), y = (f[j] & (1 << k));
                    if (x > 0 && y > 0) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    ans = max(ans, (int)words[i].size() * (int)words[j].size());
                }
            }
        }

        return ans;
    }
};
```




