# lc165. 比较版本号




## [165. 比较版本号](https://leetcode-cn.com/problems/compare-version-numbers/)

### split后双指针比较

+ 先对字符串做split提取出每个小的版本号
+ 之后对每个小版本号进行比较即可。
+ $T:O(n)$
+ $S:O(n)$

``` cpp
class Solution {
public:
    vector<int> split_s(string& s){
        vector<int> res;
        for(int i = 0, num = 0; i < s.size(); i++){
            if(s[i] == '.'){
                res.push_back(num);
                num = 0;
            }else{
                num = num * 10 + s[i] - '0';
                if(i == s.size() - 1)   res.push_back(num);
            }
        }
        
        return res;
    }
    int compareVersion(string version1, string version2) {
        vector<int> split_v1 = split_s(version1);
        vector<int> split_v2 = split_s(version2);

        int n1 = split_v1.size(), n2 = split_v2.size();

        for(int i = 0, j = 0; i < n1 || j < n2; i++, j++){
            int x = 0, y = 0;
            if(i < n1) x = split_v1[i];
            if(j < n2) y = split_v2[j];

            if(x > y)   return 1;
            if(x < y)   return -1;
        }

        return 0;
    }
};
```

### 直接使用双指针，边split边比较

``` cpp
class Solution {
public:
    unsigned int get_num(string& version, int& idx){
        if(idx >= version.size())   return 0;
        unsigned int ans = 0;

        while(idx < version.size()){
            if(version[idx] == '.'){
                idx++;
                break;
            }
            ans = ans * 10 + version[idx] - '0';
            idx ++;
        }

        return ans;
    }
    int compareVersion(string version1, string version2) {
        int idx1 = 0, idx2 = 0;
        // 类似于split，每次提取出来的两个.之间的数字
        // 如果下标已经超过了字符串的大小，则直接返回零进行比较。
        while(idx1 < version1.size() || idx2 < version2.size()){
            unsigned int n1 = get_num(version1, idx1);
            unsigned int n2 = get_num(version2, idx2);
            // cout << n1 << ' ' << n2 << endl;

            if(n1 > n2) return 1;
            if(n1 < n2) return -1;
        }

        return 0;
    }
};
```




