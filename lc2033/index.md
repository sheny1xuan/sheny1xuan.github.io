# lc2033.获取单值网格的最小操作数




## [2033.获取单值网格的最小操作数](https://leetcode-cn.com/problems/minimum-operations-to-make-a-uni-value-grid/)

### 中位数

1. 什么情况下，所有的数都可以通过加减`x`变为同一个数。可以选择第一个数作为base，其他所有的数与`base`的差值都是`x`的倍数，那么这些数就可以通过变换变为同一个数
   1. `[base, base+x, base+2x, base+3x]`
2. 如果这些数字都可以变为同一个数，那么哪一个数字`y`是最佳的数字呢。
   1. 需要找的是`min(|x1 - y| + |x2 - y| + |x3 - y| ... + |xn - y|)`
   2. 那么y就是中位数距离所有的点都是最近的点。

``` cpp
// #define DEBUG
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int n = grid.size(), m = grid[0].size();

        vector<int> f;
        int base = grid[0][0];

        for(auto& g: grid) {
            for(auto& c: g) {
                if((c - base) % x != 0) {
                    return -1;
                }        
                f.push_back(c);
            }
        }

        sort(f.begin(), f.end());
        int ans = 0;
#ifdef DEBUG
        printv(f);
        cout << f[m * n / 2] << endl;
#endif
        for(int i = 0; i < f.size(); i++) {
            ans += abs(f[m * n / 2] - f[i]) / x;
        }

        return ans;
    }

    void printv(vector<int>& v) {
        for(int i = 0; i < v.size(); i++) {
            cout << v[i] << ' ';
        }
        cout << endl;
    }
};
```




