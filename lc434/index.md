# lc434.字符串中的单词数




## [434.字符串中的单词数](https://leetcode-cn.com/problems/number-of-segments-in-a-string/)

### 实现split

+ 双指针

``` cpp
class Solution {
public:
    int countSegments(string s) {
        int cnt = 0;

        for(int i = 0, j = 0; j < s.size(); ) {
            if(s[j] != ' ') {
                while(s[j] != ' ' && j < s.size()) {
                    j ++;
                }
                cnt += 1;
            } else {
                j ++;
                i = j;
            }
        }

        return cnt;
    }
};
```

``` python
class Solution:
    def countSegments(self, s: str) -> int:
        return len([w for w in s.split(" ") if w != ""])
```






