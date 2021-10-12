# lc345.反转字符串中的元音字母




## [345. 反转字符串中的元音字母](https://leetcode-cn.com/problems/reverse-vowels-of-a-string/)

### 双指针

+ 这里可以使用`string.find(c)`，如果找到了该字母返回该字母的下标，否则返回`std::npos`，这个是一个固定值。npos 是一个常数，用来表示不存在的位置。
+ `i`找到左边元音字母，`j`找到右边元音字母。

``` cpp
class Solution {
public:
    string aeiou = "aeiouAEIOU";
    string reverseVowels(string s) {
        for(int i = 0, j = s.size() - 1; i < j;){
            if(aeiou.find(s[i]) == aeiou.npos){
                i++;
                continue;
            }
            if(aeiou.find(s[j]) == aeiou.npos){
                j--;
                continue;
            }
            swap(s[i], s[j]);
            i++; j--;
        }
        return s;
    }
};
```




