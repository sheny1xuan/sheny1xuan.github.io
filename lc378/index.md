# lc378.有序矩阵中第K小的元素




## [378.有序矩阵中第 K 小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/)

+ 如何判断一个数`num`在矩阵中处于第k小？从左下角向上移动，如果当前位置`matrix[x][y] <= num`，那么说明这一列前面所有的行都比该数小，那么叠加`x+1`，列向右移动`y+=1`。否则`x`向上移动(也就是行向上移动)，直到满足`matrix[x][y] <= num`或者移动出有序矩阵。
+ 知道如何判断一个数处于第k大之后，那么我们可以将`l=matrix[0][0], r=matrix[m-1][n-1]`，对于这个区间内的数字进行二分查找，查找第一个满足处于第k小的元素。
+ 这个元素一定在矩阵当中。举例`[1, 2, 4, 10]`，`k=3`，对任意数`4<=x<10`均满足在矩阵中满足条件的元素个数`cnt=3`，但是第一个满足`cnt=3`的元素一定是4，因为它包含等于的情况， 也就是它自己。
+ $T:O(nlog(r-l))$，`r`是矩阵中的最大值，`l`是矩阵中的最小值，`n`是矩阵的大小

``` cpp
class Solution {
public:
    bool check(int t, vector<vector<int>>& matrix, int k) {
        int cnt = 0;
        int m = matrix.size(), n = matrix[0].size();

        // 查找左下角满足条件个数
        int x = m - 1, y = 0;
        while (x >= 0 && y < n) {
            if (matrix[x][y] <= t) {
                // 向右移动
                cnt += x + 1;
                y += 1;
            } else {
                // 向上移动
                x -= 1;
            }
        }
        // cnt >= k说明当前数过大，向左收缩边界
        return cnt >= k;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int l = matrix[0][0], r = matrix[m - 1][n - 1];

        // 二分查找第一个[(矩阵左下角小于等于该元素个数)大于等于k]的值。
        while (l < r) {
            int mid = ((r - l) >> 1) + l;
            if (check(mid, matrix, k)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        // l一定在矩阵当中
        // 因为第一个满足条件的个数大于等于k的元素肯定在矩阵中。
        // 如示例1 ,k = 8 时, res = 13, 当mid为14时也满足条件，但是由于我们找的是第一个，所以他会向左收缩边界(r = mid)。
        return l;
    }
};
```


