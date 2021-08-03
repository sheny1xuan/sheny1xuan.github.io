# 987.二叉树的垂序遍历


## [987. 二叉树的垂序遍历](https://leetcode-cn.com/problems/vertical-order-traversal-of-a-binary-tree/)

+ 利用三元组记录每个节点[列，行，节点值]
+ 之后进行排序，默认的排序方式就是先按列从小到大排序，再按行从小到大排序，最后按节点值排序
+ 这里用到了c++的元组tuple，元组像pair一样。
+ 构造可以使用列表推导的方式进行构造`tuple<int, float, int> t = {1, 1.0, 2};`
+ 但是元组直接访问元素很复杂，使用`std::get<idx>(t);`,返回值是引用可以直接修改。
  + get的参数必须是编译是的常数(constant)
+ `for each`循环可以对`tuple`直接进行解包，`for(const auto& [n1, n2, n3]: rec)`
+ `std::tie(n1, n2, n3) = t`可以tuple中每个值的引用
+ c++17标准`auto [n1, n2, n3] = t`

``` cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

typedef pair<int, int> PII;
typedef tuple<int, int, int> TIII;
class Solution {
public:
    vector<TIII> rec;
    void dfs(PII cur, TreeNode* root){
        if(root == nullptr){
            return;
        }
        
        // 列, 行, 节点值
        rec.push_back({cur.second, cur.first, root->val});

        dfs({cur.first + 1, cur.second - 1}, root->left);
        dfs({cur.first + 1, cur.second + 1}, root->right);
    }

    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs({0, 0}, root);

        vector< vector<int>> res;
        sort(rec.begin(), rec.end());
        int pre = INT_MIN, idx = -1;
        for(const auto& [col, row, val]: rec){
            if(idx == -1 || pre != col){
                res.push_back({});
                idx += 1;
            }
            res[idx].push_back(val);
            pre = col;
        }

        return res;
    }
};
```




