# lc187.重复的DNA序列




## [187.重复的DNA序列](https://leetcode-cn.com/problems/repeated-dna-sequences/)

### 哈希表

+ 哈希表记录每一个子串出现的次数，出现两次的子串加入到结果中（不重不漏）。
+ 注意substr操作是复制整个子串，需要$O(L)$的时间
+ $T:O(NL)$
+ $T:O(NL)$

``` cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        unordered_map<string, int> mp;

        for(int i = 0; i < s.size(); i++ ) {
            if(i + 10 > s.size()) {
                break;
            }
            string cur = s.substr(i, 10);
            mp[cur] += 1;
            if(mp[cur] == 2) {
                ans.push_back(cur);
            }
        }

        return ans;
    }
};
```

### 位运算哈希字符串+滑动窗口

+ 因为有4个字母，所以我们可用2bit表示这4个字母，然后向这个字符串中添加字母就相当于滑动窗口，首先划出前两个bit，之后划入新的两个bit，产生的20bit的结果就是每一个字符串哈希的结果。

+ $T:O(n)$
+ $S:(n)$

``` cpp
class Solution {
public:
    unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};
    vector<string> findRepeatedDnaSequences(string s) {
        int L = 10;
        vector<string> res;
        unordered_map<int, int> mp;
        int window = 0;
        for(int i = 0; i < L; i++ ) {
            window = (window << 2) | bin[s[i]];
        }
        mp[window] = 1;

        for(int i = 0; i < s.size(); i++ ) {
            if(i + L >= s.size()) {
                break;
            }
			// 滑出
            window = (window << 2) & ((1 << (L * 2)) - 1);
            // 滑入
            window = window | bin[s[i + L]];
            mp[window] += 1;
            if(mp[window] == 2) {
                res.push_back(s.substr(i + 1, L));
            }
        }

        return res;
    }
};
```


