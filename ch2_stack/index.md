# acwing基础课ch2-栈


## 栈

### 栈的静态实现

+ 维护一个栈顶的指针，哨兵为0，当栈顶指针指向0的时候，整个栈为空栈。

### 栈的STL操作



## 栈模板题

### 静态实现
[Ac828.模拟栈](https://www.acwing.com/problem/content/description/830/)

``` cpp
#include <iostream>
#define N 100010 

using namespace std;

int st[N], tt;
void push_st(int x){
    st[++tt] = x;
}
void pop_st(){
    tt--;
}
bool empty_st(){
    return tt == 0;
}
int query_st(){
    return st[tt];
}
int main(){
    int m;
    tt = 0;
    cin >> m;
    string op;
    while(m--){
        cin >> op;
        if(op == "push"){
            int x;
            cin >> x;
            push_st(x);
        }
        else if(op == "pop"){
            pop_st();
        }
        else if(op == "empty"){
            if(empty_st()){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
        else if(op == "query"){
            cout << query_st() << endl;
        }
    }
    return 0;
}
```

### [Ac3302.表达式求值](https://www.acwing.com/problem/content/description/3305/)

+ 我们可以将表达式抽象为一颗计算树。
+ 这棵树的叶子节点是数字，树中的节点是计算操作。
+ 树中节点操作符的优先级从下往上依次降低。
+ 想要计算某个节点的值，必须计算左右子树的值才可以，这也是为什么后缀计算更加方便。

> 计算树如$1*2+3*4$

![07f087fdfe5661662ab7a1e53f404ef](https://picture-table.oss-cn-beijing.aliyuncs.com/img/07f087fdfe5661662ab7a1e53f404ef.png)

``` cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;
// 数字栈与运算符栈
stack<int> nums;
stack<char> op;
// 运算符栈优先级
unordered_map<char, int> pri = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void eval(){
    int b = nums.top(); nums.pop();
    int a = nums.top(); nums.pop();
    char p = op.top(); op.pop();
    int res = 0;
    if(p == '+') res = a + b;
    if(p == '-') res = a - b;
    if(p == '*') res = a * b;
    if(p == '/') res = a / b;
    nums.push(res);
}


int main(){
    string s;
    cin >> s;
    for(int i = 0;i < s.size(); i++){
        // 计算数字
        if(isdigit(s[i])){
            int num = 0;
            int j = i;
            while(j < s.size() && isdigit(s[j])){
                num = num * 10 + s[j] - '0';
                j ++;
            }
            i = j-1;
            // 数字入栈
            nums.push(num);
        }
        else{
            // 左括号直接入栈
            if(s[i] == '('){
                op.push(s[i]);
            }
            else if(s[i] == ')'){
                // 计算括号内的所有运算符
                // 运算符优先级递减
                while(op.top() != '('){
                    eval();
                }
                op.pop();
            }
            else{
                // 如果当前运算符优先级低于栈顶运算符
                // 计算栈顶运算符。
                while(op.size() && pri[s[i]] <= pri[op.top()]){
                    eval();
                }
                op.push(s[i]);
            }
        }
    }
    // 栈内保证后面入栈的元素优先级更高
    // 因此可以从后往前计算。
    while(op.size()) eval();
    // 栈内最后一个元素就是结果
    cout << nums.top() << endl;
    return 0;
}
```

### [150.逆波兰表达式求值](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

+ 后缀表达式，相当于已经计算了先计算左右子树，无需考虑符号问题
+ python写字符串还是比较爽，cpp太复杂了

```cpp
class Solution {
public:
    int get_number(string &s){
        int x = 0;
        for(int i = 0; i < s.size(); i++){
            x = x * 10 + s[i] - '0';
        }
        return x;
    }
    bool isnumber(string &s, int &x){
        int n = s.size();
        if(isdigit(s[0])){
            x = get_number(s);
            return true;
        }
        else if(s[0] == '-' && n > 1){
            string t = s.substr(1);
            x = -get_number(t);
            return true;
        }
        return false;
    }
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(int i = 0; i < tokens.size(); i++){
            int x;
            if(isnumber(tokens[i], x)){
                st.push(x);
            }else{
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if(tokens[i][0] == '+'){
                    st.push(a+b);
                }
                if(tokens[i][0] == '-'){
                    st.push(a-b);
                }
                if(tokens[i][0] == '*'){
                    st.push(a*b);
                }
                if(tokens[i][0] == '/'){
                    st.push(a/b);
                }
            }
        }
        return st.top();
    }
};
```

``` python
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        for c in tokens:
            if c in ['+', '-', '*', '/']:
                num2 = stack.pop()
                num1 = stack.pop()
                if c == '+': stack.append(num1 + num2)
                if c == '-': stack.append(num1 - num2)
                if c == '*': stack.append(num1 * num2)
                if c == '/': 
                    res = num1 / num2
                    res = floor(res) if res > 0 else ceil(res)
                    stack.append(res)
            else:
                stack.append(int(c))
        return stack[0]
```

## 单调栈

### [模板一. 输出左边比当前值小的数](https://www.acwing.com/problem/content/1455/)

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210425221432274.png" alt="image-20210425221432274" style="zoom:80%;" />

+ 维护一个单调递增的单调栈：因为比当前元素大的左边的数一定不可能是左边最近的最小的数。

``` cpp
#include <iostream>
#include <string>
#include <stack>

using namespace std;

const int N = 1e5+1;

stack<int> st;

int main(){
    int n;
    cin >> n;
    int x;
    for(int i = 0; i < n; i++){
        cin >> x;
        while(!st.empty() && st.top() >= x) st.pop();
        if(!st.empty()){
            cout << st.top() << ' ';
        }else{
            cout << -1 << ' ';
        }
        st.push(x);
    }
    cout << endl;
    return 0;
    
}
```

### [模板二. 移掉K位数字](https://www.acwing.com/problem/content/1455/)

![image-20210426104249428](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210426104249428.png)

+ 删除前导0，空字符串返回0
+ 情况一：字符串内的数字单调递增（非严格单调递增），删除k个数使其最大，则删除的后面k个数
+ 情况二：如果当前字符串非单调递增， 单调栈内构建的为单调递增的字符串，删除前面较大的数字一定能得到更小的数字，缩小解的空间。

``` cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    string res = "0";
    string s;
    int k;
    cin >> s >> k;
    for(auto ch:s){
        // 单调递增栈
        while(k && res.back() > ch){
            res.pop_back();
            k -= 1;
        }
        res += ch;
    }
    int n = 0;
    // 从后往前删除多余的数
    while(k--)  res.pop_back();
    // 删除前导0
    while(n < res.size() && res[n] == '0')  n++;
    // 空字符串返回0，否则返回子串
    if(n == res.size()) cout << "0";
    else cout << res.substr(n);
    return 0;
}
```


