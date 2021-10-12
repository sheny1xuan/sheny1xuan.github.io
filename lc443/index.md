# lc443. 压缩字符串




## [443. 压缩字符串](https://leetcode-cn.com/problems/string-compression/)

### 使用额外空间

+ 两种情况进行判断是否需要在结果中添加该字符
  + 如果该字符是最后一个字符
  + 或者该字符与下一个字符不相同
+ $T:O(n)$
+ $S:O(n)$

``` cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), left = 0;
        string s;
        for(int i = 0; i < n; i++){
            if(i == n - 1 || chars[i] != chars[i + 1]){
                s += chars[i];
                int cnt = i - left + 1;
                left = i + 1;
                
                if(cnt == 1)    continue;
                
                s += to_string(cnt);
            }
        }

        for(int i = 0; i < s.size(); i++){
            chars[i] = s[i];
        }

        return s.size();
    }
};
```

### 不使用额外空间

+ 双指针
+ read指向已经读取的字符下标，write指向已经更新的压缩的字符下标
+ 两种情况进行判断是否需要在结果中添加该字符
  + 如果该字符是最后一个字符
  + 或者该字符与下一个字符不相同

``` cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0, left = 0;
        int n = chars.size();
        for(int read = 0; read < n; read++ ){
            // 如果是最后一个或者与下一个相等
            if(read == n - 1 || chars[read] != chars[read + 1] ){
                // 记录字母
                chars[write++] = chars[read];
                int cnt = read - left + 1;
                left = read + 1;
                // 如果只有一个字母跳过。
                if(cnt == 1)    continue;
                string s_cnt = to_string(cnt);
                for(int i = 0; i < s_cnt.size(); i++){
                    chars[write++] = s_cnt[i];
                }
                
            }
        }

        return write;
    }
};
```




