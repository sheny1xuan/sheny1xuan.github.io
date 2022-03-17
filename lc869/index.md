# lc869.重新排序得到 2 的幂




## [869.重新排序得到 2 的幂](https://leetcode-cn.com/problems/reordered-power-of-2/)

### 排列+LBit

+ 计算所有的排列
+ 对每一个排列通过LBit判断其是否是2的幂(2的幂只有一位为1)。
+ `T:O(m!)`，m是数字的位数，排列的时间复杂度为`O(m!)`

``` cpp
// #define DEBUG
class Solution {
public:
    bool ans = false;
    bool isValid(int x) {
        // x & x - 1 将 x 的最高位置位为0
        return (x & x - 1) == 0;
    }
    bool reorderedPowerOf2(int x) {
        string numStr = to_string(x);
        int n = numStr.size(); 
        sort(numStr.begin(), numStr.end());
        vector<bool> vis(n, false);

        dfs(numStr, 0, vis, 0); 

        return ans;
    }

    void dfs(string& num, int idx, vector<bool>& vis, int path) {
#ifdef DEBUG
        cout << path << endl;
#endif
        if (idx == num.size()) {
            if (isValid(path)) {
                ans = true;
            }
            return;
        }

        for (int i = 0; i < num.size(); i++) {
            // frefix
            if (path == 0 && num[i] == '0') {
                continue;
            }

            // delete same num
            if (i > 0 && num[i] == num[i - 1] && vis[i - 1] == false) {
                continue;
            }

            if (ans == true) {
                return ;
            }

            if (vis[i] == false) {
                vis[i] = true;

                dfs(num, idx + 1, vis, path * 10 + num[i] - '0');

                vis[i] = false;
            }
        }
    }
};
```




