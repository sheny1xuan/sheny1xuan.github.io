# lc524.通过删除字母匹配到字典里最长单词




## [524. 通过删除字母匹配到字典里最长单词](https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/)

### 排序+双指针

+ 双指针：判断一个字符串是不是另一个字符串的子串采用双指针,$T:O(n)$
+ 排序：首先按照字符串长度进行排序，在长度相同的情况下，按照字符串的首字母字典序进行排序。

+ $T:O(mlogm+m*n)$，$m$是字符串数组的长度，$n$是单个字符串的平均长度。排序时间复杂度$mlogm$，查询m个字符串是不是该串的子串$O(mn)$.

``` cpp
class Solution {

public:
    static bool cmp(string& a, string& b){
        if(a.size() != b.size()){
            return a.size() >= b.size();
        }else{
            return a < b;
        }
    }
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), cmp);

        for(auto& word: dictionary){
            int i = 0, j = 0;
            for(; i < s.size() && j < word.size();){
                if(s[i] == word[j]){
                    i++, j++;
                }else{
                    i++;
                }
            }
            if(j == word.size()){
                return word;
            }
        }

        return "";
    }
};
```


