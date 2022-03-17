# acwing基础课ch2-字符串问题


## 字符串问题

### 字符串单模匹配

> 给你一个字符串haystack和needle，找出needle再haystack中第一个出现的位置。
>
> 如果needle未曾出现再haystack时，返回-1。
>
> 如果needle是空串，返回0

[28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

### 暴力算法

+ 枚举haystack中的每个字串

+ $T:O(m*n)$

``` cpp
ssssssclass Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle == ""){
            return 0;
        }
        if(haystack.size() < needle.size()){
            return -1;
        }
        for(int i = 0; i < haystack.size(); i++){
            bool flag = true;
            for(int j = 0;j < needle.size(); j++){
                if(haystack[i+j] != needle[j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                return i;
            }
        }
        return -1;
    }
};
```

### KMP算法

> s[n]为目标串，p[n]为模式串

> next[i] = j 以i-1为结尾的字符串与前缀匹配的最长的长度为j（p[1,j]和p[i-j, i-1]匹配）

![image-20210420145025229](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210420145025229.png)

> 图中的j是模式串的位置，如果第i个数匹配不成功，向后移动查看p[ne[j]+1]和s[i]是否能匹配成功。

如何计算next数组->类似的思想，如果不匹配，向后移动ne[j]个字符。

>  匹配成功j = ne[j]向后移动继续匹配下一个串
>
> 理解j=ne[j]是向后移动：**j是已经匹配了的字符串的长度**，继续匹配第j+1个字符

![image-20210420150715222](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210420150715222.png)

> ne数组：ne[i]:与下标i结尾的后缀相同的前缀的长度，取值范围为$0->i-1$，前缀的长度小于当前子串长度

![image-20210421214133524](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210421214133524.png)

> $T:O(2*m+n)$，$j$在`while(j && p[i] != p[j + 1])​`中最多减$m$次，而$j$在for循环中最多加$m$次。

``` cpp
#include <iostream>
#include <string>
#include <algorithm>

#define N 1000001
char s[N], p[N];
int n, m;
int ne[N];

using namespace std;

int main(){
    // 从第1个字符开始
    cin >> n >> p + 1 >> m >> s + 1;
    // ne[1] = 0,因为第一个不匹配时
    // 都可以让目标串向后移动一位
    // 求ne数组：ne[i]:与下标i结尾的后缀相同的前缀的长度
    for(int i = 2, j = 0; i <= n; i++){
        while(j && p[i] != p[j + 1])    j = ne[j];
        if(p[i] == p[j + 1])    j += 1;
        ne[i] = j;
    }
    // 查看next数组 j = 0,意味着从零开始匹配，ne[0]无意义。
    // for(int i = 0; i <= n; i++){
    //   cout << ne[i] << ' ' ;
    // }
    // cout << endl;
    // KMP匹配
    // i表示开始匹配的目标串的下标
    // j表示匹配的长度
    for(int i = 1, j = 0; i <= m; i++){
        while(j && s[i] != p[j + 1])    j = ne[j];
        if(s[i] == p[j + 1])    j += 1;
        if(j == n){
            // 计数从1开始所以不用减去1
            cout << i - n << ' ';
            // 一定要是ne[j]不能是把整个字符串右移。
            j = ne[j];
        }
    }
    // cout << ne[n+1];
    return 0;
}
```


