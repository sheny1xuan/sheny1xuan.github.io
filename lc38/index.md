# lc38.外观数列




## [38.外观数列](https://leetcode-cn.com/problems/count-and-say/)

### 字符串模拟

+ 双指针逐位进行模拟。
+ 注意最后结尾的时候，要对最后的字符进行单独处理。

``` cpp
class Solution {
public:
    string countAndSay(int n) {
        string ans = "1";
        while(--n) {
            string t = "";
            for(int i = 0, j = 0; j < ans.size(); ) {

                if(ans[j] != ans[i] ) {
                    // j - i >= 0
                    t += to_string(j - i);
                    t += ans[i];
                    i = j;
                }
                j ++;

                if(j == ans.size()) {
                    
                    t += to_string(j - i);
                    t += ans[i];
                }
            }

            ans = t;
        }

        return ans;
    }
};
```




