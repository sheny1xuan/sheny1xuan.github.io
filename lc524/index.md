# lc524.通过删除字母匹配到字典里最长单词




## [524. 通过删除字母匹配到字典里最长单词](https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/)

### 排序+双指针

+ 双指针：判断一个字符串是不是另一个字符串的子串采用双指针,$T:O(n+m)$
+ 如`w`是`s`的子序列， 那么将`w`中每个字母按顺序匹配到`w`中对应的最左边的字母。
+ 排序：首先按照字符串长度进行排序，在长度相同的情况下，按照字符串的首字母字典序进行排序。
+ $T:O(klogk+(m+n)*k)$，$k$是字符串数组的长度，$n$是单个字符串的平均长度，`m`是原串的长度。排序时间复杂度$klogk$，查询k个字符串是不是该串的子串$O(k(n+m))$.

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

### 状态机

+ 预处理目标字符串，使得匹配每个字符串的时间复杂度为$O(n)$
+ `next[i][j]`表示在当前下标`i`的位置，最靠近该位置的字母`j`出现的位置。
+ 如`#leetcode`,`next[0][l]=1, next[0][e]=2,next[0][t]=4`。
+ 通过对每个待匹配的字符串进行进行状态转移，如果没有对应的状态，则说明不存在该子串。
+ $T:O(n*k + klogk + m * 26)$

``` cpp
class Solution {
public:
    static bool cmp(string& x, string& y) {
        if (x.size() != y.size()) {
            return x.size() > y.size();
        } else {
            return x < y;
        }
    }
    string findLongestWord(string s, vector<string>& dictionary) {
        int n = s.size();
        s = "#" + s;

        sort(dictionary.begin(), dictionary.end(), cmp);

        // f[i][j], 下标i的最近的右边字母j的位置
        auto f = vector<vector<int>>(n + 1, vector<int>(26, -1));

        for (int i = n; i > 0; i--) {
            for (int j = 0; j < 26; j++) {
                f[i - 1][j] = f[i][j];
            }
            // 除了字母i，其余字母都可以从更靠后的字母中得到
            f[i - 1][s[i] - 'a'] = i;
        }

        for (auto& w: dictionary) {
            int idx = 0;
            bool ok = true;

            for (auto& c: w) {
                idx = f[idx][c - 'a'];

                if (idx == -1) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                return w;
            }
        }

        return "";
    }
};
```




