# lc678.有效的括号字符串




## [678. 有效的括号字符串](https://leetcode-cn.com/problems/valid-parenthesis-string/)

+ 使用两个栈分别记录左括号和星号（栈内记录其下标），遇到右括号时，首先匹配左括号栈，之后匹配星号栈。

+ 对于左括号栈和星号栈的剩余部分，需要星号匹配左括号，所以星号的下标应该大于左括号。从栈顶开始比较两个栈的下标。

``` cpp
class Solution {
public:
    bool checkValidString(string s) {
        int cnt = 0;
        stack<int> l_st;
        stack<int> s_st;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                l_st.push(i);
            }else if(s[i] == '*'){
                s_st.push(i);
            }

            if(s[i] == ')'){
                if(!l_st.empty()){
                    l_st.pop();
                }else if(!s_st.empty()){
                    s_st.pop();
                }else{
                    return false;
                }
            }
        }

        while(!l_st.empty()){
            if(s_st.empty()){
                return false;
            }
            if(l_st.top() < s_st.top()){
                l_st.pop(); s_st.pop();
            }else{
                return false;
            }
        }

        return true;
    }
};
```




