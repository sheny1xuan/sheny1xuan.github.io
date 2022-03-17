# lc124.二叉树中的最大路径和




## [124.二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

``` 
    a
b       c
```
+ 最大路径可能有三种情况
  + $b \rightarrow a \rightarrow c $
  + $b \rightarrow a \rightarrow a'father$
  + $c \rightarrow a \rightarrow a'father$
+ 该节点向上返回值为该节点能够提供的最大路径
  + 小于零时，舍弃该结点的儿子结点。
  + 如果以该节点作为最优路径根节点
    + $path = left + right + root -> val$
  + 如果该节点作为左右子树的结点
    +  $return \ max(left, right) + root -> val$
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
class Solution {
public:
    int ans = INT_MIN;
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }

    // return root substree maxval
    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int l = dfs(root->left);
        int r = dfs(root->right);

        // subtree value
        ans = max(l + r + root->val, ans);

        return max(0, max(l, r) + root->val);
    }
};
```

### 类似题目
+ [687. 最长同值路径](https://leetcode-cn.com/problems/longest-univalue-path/)
+ [543. 二叉树的直径](https://leetcode-cn.com/problems/diameter-of-binary-tree/)
