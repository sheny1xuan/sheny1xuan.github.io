# acwing基础课ch1-高精度运算


# 高精度运算

## 数据存储

+ 利用**数组倒序**存储大的数据，进位在最后一位添加一个数十分方便。

![image-20210507224141339](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210507224141339.png)

## 高精度加法

+ 模拟加法进位
+ 字符串输入，取反存入数组中
+ 计算返回数组倒序输出。

``` cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<int> add(vector<int>& A, vector<int>& B){
    vector<int> res;
    int up = 0;
    for(int i = 0; i < A.size() || i < B.size() || up; i++){
        if(i < A.size())    up += A[i];
        if(i < B.size())    up += B[i];
        res.push_back(up % 10);
        up = up / 10;
    }
    return res;
}

int main(){
    string a, b;
    vector<int> A, B;
    cin >> a >> b;
    
    // 注意这里的字符串转换
    for(int i = a.size() - 1; i >= 0; i--)  A.push_back(a[i] - '0');
    for(int i = b.size() - 1; i >= 0; i--)  B.push_back(b[i] - '0');
    
    vector<int> C = add(A, B);
    
    for(int i = C.size() - 1; i >= 0; i--)  printf("%d", C[i]);
    
    return 0;
}
```

## 高精度减法

+ 保证A>=B
+ $A-B(A>=B)$，$-(B-A)(A<B)$
+ 注意减法会有前导零，要删除前导零
+ 关键点有两个：如何判断两个数大小和如何进行模拟减法。

``` cpp
#include <iostream>
#include <vector>

using namespace std;

bool cmp(vector<int>& A, vector<int>& B){
    if(A.size() != B.size())    return A.size() > B.size();
    else{
        for(int i = A.size() - 1;i >= 0; i--){
            if(A[i] != B[i])    return A[i] > B[i];
        }
    }
    return true;
}

vector<int> sub(vector<int>& A, vector<int>& B){
    vector<int> res;
    int help = 0;
    for(int i = 0; i < A.size(); i++){
        help += A[i];
        if(i < B.size())    help -= B[i];
        if(help >= 0){
            res.push_back(help);
            help = 0;
        }else{
            res.push_back(help + 10);
            help = -1;
        }
    }
    
    while(res.size() > 1 && res.back() == 0)    res.pop_back();
    return res;
}

int main(){
    string a, b;
    vector<int> A, B, C;
    cin >> a >> b;
    
    for(int i = a.size() - 1;i >= 0; i--)   A.push_back(a[i] - '0');
    for(int i = b.size() - 1;i >= 0; i--)   B.push_back(b[i] - '0');
    
    if(cmp(A, B)){
        C = sub(A, B);
    }else{
        C = sub(B, A);
        printf("-");
    }
    
    for(int i = C.size() - 1; i >= 0; i--)  printf("%d", C[i]);
}
```

## 高精度乘法

+ 每一项乘乘数，每次处理结果的最后一位，其余作为进位。

``` cpp
#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int>& A, int b){
    vector<int> res;
    int t = 0;
    for(int i = 0; i < A.size(); i++){
        t += A[i] * b;
        // 添加个位
        res.push_back(t % 10);
        // 进位
        t /= 10;    
    }
    // 处理多余的进位
    while(t){
        res.push_back(t % 10);
        t /= 10;
    }
    // 去除前导0
    while(res.size() > 1 && res.back() == 0)    res.pop_back();
    
    return res;
}

int main(){
    string a;
    int b;
    cin >> a >> b;
    vector<int> A, C;
    
    for(int i = a.size() - 1; i >= 0; i--)  A.push_back(a[i] - '0');
    
    C = mul(A, b);
    
    for(int i = C.size() - 1; i >= 0; i--)  printf("%d", C[i]);
    
    return 0;
}
```

## 高精度除法

+ 除法是正着计算的，其余都是按照逆运算进行进位的。
+ 商的位数小于等于被除数的位数。
+ 上次除的余数*10 / 除数 就是该位的结果，之后更新除数即可。

``` cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 商的位数小于等于被除数的位数。
// 模拟除法
// 上次除的余数*10 / 除数 就是该位的结果
// 之后更新除数即可。
// A/b = C ... k
vector<int> div(vector<int>& A, int b, int& k){
    vector<int> res(A.size());
    
    for(int i = A.size() - 1; i >= 0; i--){
        k = k * 10 + A[i];
        res[i] = k / b;
        k = k % b;
    }
    
    while(res.size() > 1 && res.back() == 0)    res.pop_back();
    
    return res;
}

int main(){
    string a;
    int b, k = 0;
    vector<int> A, C;
    
    cin >> a >> b;
    
    for(int i = a.size() - 1; i >= 0; i--)  A.push_back(a[i] - '0');
    
    C = div(A, b, k);
    
    for(int i = C.size() - 1; i >= 0; i--)  printf("%d", C[i]);
    printf("\n%d", k);
    
    return 0;
    
    
}
```


