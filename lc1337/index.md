# lc1337.矩阵中战斗力最弱的K行




## [1337. 矩阵中战斗力最弱的 K 行](https://leetcode-cn.com/problems/the-k-weakest-rows-in-a-matrix/)

### 二分查找+topK

+ 1总是排在前面，所以我们只需要通过二分查找找到最后一个1的位置。
+ 再利用最小堆找出topK小的数
+ `T:O(mlogn+klogm)`
  + `O(mlogn):二分查找`
  + `O(m):构建优先队列`，参考：https://www.zhihu.com/question/20729324
  + `O(klogm):topK`



``` cpp
typedef pair<int, int> PII;
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        // O(mlogn):二分查找
        vector<PII> cmp;
        for(int i = 0; i < mat.size(); i++){
            int l = -1, r = mat[i].size() - 1;
            while(l < r){
                int mid = (l + r + 1) >> 1;
                if(mat[i][mid] == 1){
                    l = mid;
                }else{
                    r = mid - 1;
                }
            }

            cmp.push_back({l, i});
        }
        // O(m):构建优先队列
        priority_queue<PII, vector<PII>, greater<PII>> q(cmp.begin(), cmp.end());
        vector<int> ans;
        // O(klogm):topK
        for (int i = 0; i < k; ++i) {
            ans.push_back(q.top().second);
            q.pop();
        }
        return ans;
    }
};
```


