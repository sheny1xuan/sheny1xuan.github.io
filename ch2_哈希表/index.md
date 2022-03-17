# acwing基础课ch2-哈希表


## 哈希表

+ 将一个复杂的数据结构进行映射。
+ (key-value)pair的关系。

### 哈希表基本元素

+ key-value映射
+ 哈希函数
+ 哈希冲突解决方法

### 哈希函数

+ 一般取模(x%MOD)
+ MOD是大于数据规模的最小质数

### 哈希冲突

+ 不同的key通过哈希函数后产生了相同的value（映射）。

#### 拉链法

+ 产生了冲突之后，将产生哈希冲突的值用链表的方式存储在相应的idx之后
+ 插入：在哈希值的链表上插入一个值。
+ 查找：找到哈希值，在哈希值对应的链上查找。
+ 删除：删除链表的一个节点

![image-20210519175123969](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210519175123969.png)

``` cpp
#include <iostream>

const int N = 1e5+10;

using namespace std;

struct Listnode{
    int val;
    Listnode* next;
    Listnode(int x = 0, Listnode* ne = nullptr):val(x), next(ne) {}
};
// 哈希值
Listnode* h[N] = {nullptr};

void insert(int x){
    // 负数情况
    int t = (x % N + N) % N;
    
    Listnode* add = new Listnode(x, nullptr);
    
    if(h[t] == nullptr){
        h[t] = add;
    }else{
        add -> next = h[t] -> next;
        h[t] -> next = add;
    }
    
}

bool find(int x){
    int t = (x % N + N) % N;
    
    Listnode* root = h[t];
    
    while(root != nullptr){
        if(root -> val == x){
            return true;
        }
        root = root -> next;
    }
    return false;
}

int main(){
    int n;
    cin >> n;
    
    while(n--) {
        char op;
        int x;
        
        cin >> op >> x;
        if(op == 'I'){
            insert(x);
        }else{
            if(find(x)) cout << "Yes" << endl;
            else    cout << "No" << endl;
        }
    }
    
    return 0;
}
```



#### 开放寻址法

+ 产生了冲突之后，向后查找直到找到一个位置value没有任何key存在在这个位置
+ 添加：
+ 查找：计算哈希值，查找哈希序列，如果遇到目标值，返回该目标值的下标。否则继续查找到一个合适位置。
+ 删除：打一个特殊标记，不需要真的删除

![image-20210519180412417](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210519180412417.png)



``` cpp
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>


using namespace std;

const int N = 2e5+3;
const int null = 0;
int h[N], n;
// 开放寻址法
int find(int x){
    // 负数取余数仍是负数
    // 处理负数的情况
    int t = (x % N + N) % N;
    
    // 直到遇到空的节点，结束搜素
    while(h[t] != null){
        // 如果找到目标值返回目标值的索引
        if(h[t] == x){
            break;
        }
        
        t ++;

        if(t == N - 1){
            t = 1;
        }
    }
    // 如果没找到目标值，返回它应该在的位置
    return t;
}

int main(){
    cin >> n;
    
    while(n-- ){
        char op;
        int x;
        cin >> op >> x;
        int t = find(x);
        if(op == 'I'){
            h[t] = x;
        }else{
            if(h[t] == x) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    
    return 0;
}
```

## 字符串哈希

### 字符串前缀哈希法

1. 将字符串转换为一个k进制的数。
2. 然后将这个数取余数可以得到这个字符串的哈希值
3. 注意不能有字母映射为0，对P，Q取经验值时不会存在哈希冲突。

![image-20210519201424980](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210519201424980.png)

+ 首先求出一个字符串所有前缀的哈希值
+ 然后可以根据前缀的哈希值就可以在$O(1)$时间内求出任一子串的哈希值
+ $h[l, r] = h[r] - h[l-1] * p ^{(r - l + 1)}$

![image-20210519202411134](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210519202411134.png)

### 字符串哈希

+ 处理多次询问子串是否相同的情况

``` cpp
#include <iostream>

using namespace std;

typedef unsigned long long ull;

const int N = 1e5+10, P = 131;
ull h[N], p[N];

// 返回前缀和
ull find(int l, int r){
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    
    p[0] = 1;
    
    // 计算前缀
    for(int i = 1; i <= n; i++){
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i - 1]; 
    }
    
    while(m-- ){
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        
        if(find(l1, r1) == find(l2, r2))    cout << "Yes" << endl;
        else    cout << "No" << endl;
    }
}
```


