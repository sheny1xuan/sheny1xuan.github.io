# lc1755.最接近目标值的子序列和




## [1755.最接近目标值的子序列和](https://leetcode-cn.com/problems/closest-subsequence-sum/)

### 折半搜索

+ 数据范围比较小，但是没有到小到可以直接搜索的地步。
+ 可以将整个数据分成两部分分别进行搜索，最后进行合并即可。
+ 考虑这道题，如果是直接暴力求出所有的子集，并且计算每个子集与target的差值，那么时间复杂度是$n*2^n$，这里n的取值是40，直接暴力搜索会超时。
+ 但是如果考虑将n分为两部分，分别对每部分内部进行搜索，时间复杂度可以优化到$n*2^{n/2}$。
+ 之后需要对两部分的子集进行合并，也就是两数之和问题。先将两个子集和进行排序，然后通过双指针进行查找最接近目标值的子序列和。

``` cpp
// #define DEBUG
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size(); 
        int ln = n / 2; int rn = n - ln;

        vector<long long> lsum((1 << ln), 0);
        vector<int> lnums(nums.begin(), nums.begin() + ln);
        vector<long long> rsum((1 << rn), 0);
        vector<int> rnums(nums.begin() + ln, nums.end());

        for (int i = 0; i < (1 << ln); i++) {
            long long cal = 0;
            for (int j = 0; (1 << j) <= i; j++) {
                if ((1 << j) & i) {
                    cal += lnums[ln - j - 1];
                }
            }
            lsum[i] = cal;
        }

        for (int i = 0; i < (1 << rn); i++) {
            long long cal = 0;
            for (int j = 0; (1 << j) <= i; j++) {
                if ((1 << j) & i) {
                    cal += rnums[rn - j - 1];
                }
            }
            rsum[i] = cal;
        }

        long long ans = LONG_MAX;
        cout << ans << endl;

        // left
        for (auto& x: lsum) {
            ans = min(ans, abs(goal - x));
#ifdef DEBUG
            cout << x << " " << abs(goal - x) << endl;
            cout << ans << endl;
#endif
        }

        // right
        for (auto& x: rsum) {
            ans = min(ans, abs(goal - x));
#ifdef DEBUG
            cout << x << " " << abs(goal - x) << endl;
            cout << ans << endl;
#endif
        }

        // left & right
        int l = 0, r = rsum.size() - 1;
        sort(lsum.begin(), lsum.end());
        sort(rsum.begin(), rsum.end());

        while (l < lsum.size() && r >= 0) {
            int cal = lsum[l] + rsum[r];
#ifdef DEBUG
            cout << l << " " << r << " " << abs(cal - goal) << endl;
#endif
            ans = min(ans, abs(cal - goal));

            if (cal > goal) {
                r -= 1;
            } else {
                l += 1;
            }
        }

        return ans;
    }

    long long min(long long x, long long y) {
        return x < y ? x : y;
    }
};
```

### 参考：

+ https://leetcode-cn.com/problems/closest-subsequence-sum/solution/zhuang-ya-dp-zhi-cong-kan-shu-ju-fan-wei-kve3/
+ https://www.acwing.com/blog/content/32/
