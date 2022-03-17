# lc58.最后一个单词的长度




## [58.最后一个单词的长度](https://leetcode-cn.com/problems/length-of-last-word/)

### 从后往前遍历，找到最后一个单词

``` cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        int idx = n - 1, ans = 0;

        while(s[idx] == ' '){
            idx --;
        }

        while(idx >= 0 && s[idx] != ' '){
            idx --;
            ans ++;
        }

        return ans;
    }
};
```



### 利用split得到所有空格分开的字符串

``` cpp
class Solution {
public:
    vector<string> split(string& s){
        vector<string> ans;
        int n = s.size();
        for(int i = 0, j = 0; j < n;){
            if(s[j] == ' '){
                if(i == j){
                    i++, j++;
                }else{
                    ans.push_back(s.substr(i, j - i));
                    j ++;
                    i = j;
                }
            }else{
                j++;
            }
            
            if(j == n){
                if(i != j){
                    ans.push_back(s.substr(i, j - i));
                }
            }
        }

        return ans;
    }
    int lengthOfLastWord(string s) {
        vector<string> ans = split(s);

        return ans.back().size(); 
    }
};
```


