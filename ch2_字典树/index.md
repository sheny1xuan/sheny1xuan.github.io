# acwing基础课ch2-字典树


## 字典树

### 作用

+ 高效地存储与查找字符串。(O(logn)的时间复杂度进行查找)
+ 支持两种操作：插入一个字符串(insert)
+ 查找是否存在一个字符串(qury)
+ 一个关键点：字典树是通过边存储字符串的。 

![image-20210511194133006](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210511194133006.png)

#### 静态实现

``` cpp
#include <iostream>

using namespace std;

const int N = 1e5+10;

// 最多有N*26个节点
int son[N][26], cnt[N], idx; 
char str[N], op[2];

// 插入一个字符串
void insert(char str[]){
    int p = 0;
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a';
        if(!son[p][u])  son[p][u] = ++ idx;
        p = son[p][u];
    }
    
    cnt[p]++ ;
}

// 查询一个字符串，并且返回该字符串出现的次数。
int query(char str[]){
    int p = 0;
    for(int i = 0; str[i]; i++){
        int u = str[i] - 'a';
        if(!son[p][u])  return 0;
        p = son[p][u];
    }
    
    return cnt[p];
}

int main(){
    int n;
    scanf("%d", &n);
    while(n-- ){
        scanf("%s%s", &op, &str);
        
        if(op[0] == 'I'){
            insert(str);
        }else{
            printf("%d\n", query(str));
        }
    }
    
    return 0;
}
```

#### OOP实现

+ 无内存管理，存在内存泄漏

``` cpp
#include <iostream>

using namespace std;

class Trie{
    private:
    int cnt = 0;
    Trie* next[26] = {nullptr};
    public:
    Trie(){}
    
    void insert(string& s){
        Trie* root = this;
        for(int i = 0; i < s.size(); i++){
            int x = s[i] - 'a';
            if(root -> next[x] == nullptr)  root -> next[x] = new Trie();
            root = root -> next[x];
        }
        root -> cnt += 1;
    }
    
    int qury(string& s){
        Trie* root = this;
        for(int i = 0; i < s.size(); i++){
            int x = s[i] - 'a';
            if(root -> next[x] == nullptr)  return 0;
            root = root -> next[x];
        }
        
        return root->cnt;
    }
};

int main(){
    int n;
    cin >> n;
    Trie* root = new Trie();
    
    while(n--){
        char op;
        string s;
        cin >> op >> s;
        if(op == 'I'){
            root -> insert(s);
        }else{
            cout << root -> qury(s) << endl;
        }
    }
    
    return 0;
}
```

+ 内存管理->析构函数

``` cpp
#include <iostream>

using namespace std;

class TrieNode{
    public:
    int cnt = 0;
    TrieNode* ne[26] = {nullptr};
};

class Trie{
    private:
    TrieNode* root;
    void delRoot(TrieNode* root){
        if(root == nullptr){
            return;
        }
        for(int i = 0; i < 26; i++){
            delRoot(root -> ne[i]);
        }
        
        delete root;
    }
    public:
    Trie(){
        root = new TrieNode();
    }
    void insert(string s){
        TrieNode* t = root;
        for(int i = 0; i < s.size(); i++){
            int x = s[i] - 'a';
            if(t -> ne[x] == nullptr)    t -> ne[x] = new TrieNode();
            t = t -> ne[x];
        }
        t -> cnt += 1;
    }
    int qury(string s){
        TrieNode* t = root;
        for(int i = 0; i < s.size(); i++){
            int x = s[i] - 'a';
            if(t -> ne[x] == nullptr)   return 0;
            t = t -> ne[x];
        }
        return t -> cnt;
    }
    ~Trie(){
        delRoot(root);
    }
};

int main(){
    int n;
    cin >> n;
    Trie myTrie;
    
    while(n--){
        char op;
        string s;
        cin >> op >> s;
        if(op == 'I'){
            myTrie.insert(s);
        }else{
            cout << myTrie.qury(s) << endl;
        }
    }
    
    return 0;
}
```



## 最大异或对

### 题目描述

找出一个数组中异或最大的两个数。

### 暴力

+ 枚举所有的数的组合，分别计算异或值$O(n^2)$

## 字典树

+ 首先建立每个数的二进制字典树
+ 之后查询字典树，对于每一位优先选择相反的位以获得该位最大的收益。

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5+10;
// 每个数有31位，所以有31*n个节点
int son[N * 31][2], a[N], index = 0;

void insert(int x){
    int p = 0;  //根节点
    // 倒序，最高位靠近根节点。
    for(int i = 30; i >= 0; i--){
        int u = x >> i & 1;
        if(!son[p][u])  son[p][u] = ++index;
        p = son[p][u];
    }

}

int qury(int x){
    int p = 0, res = 0;
    for(int i = 30; i >= 0; i--){
        int u = x >> i & 1;
        if(son[p][!u]){
            p = son[p][!u];
            // 该位与查询数不同，异或值为1
            res += 1 << i;
        }else{
            p = son[p][u];
        }
    }
    
    return res;
}

int main(){
    int n, res = 0;
    cin >> n;
    // 建立字典树
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        insert(a[i]);
    }
    // 对于每个数字，查询z
    for(int i = 0; i < n; i++)  res = max(res, qury(a[i]));
    
    cout << res;
    
    return 0;
}
```




