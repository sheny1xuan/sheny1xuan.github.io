# lc687.最长同值路径




## [687.最长同值路径](https://leetcode-cn.com/problems/longest-univalue-path/)

+ 如果是普通的图，那么这个题目就是岛屿问题(DFS)，最大的连通图。
+ 但是由于有限制是单条路径，所以要返回左右子树的路径最大值。
+ 并且在搜索过程中把该节点为根节点作为计算左右子树相加的最大值。

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
    int ans = 0;    
    int longestUnivaluePath(TreeNode* root) {

        dfs(root);
        return ans;
    }

    // 返回与root值相同的最长同值路径的长度。
    int dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // 与root->left相同的最长同值路径长度
        int l = dfs(root->left);
        // 与root->right相同的最长同值路径长度
        int r = dfs(root->right);

        // 如果根节点与左子节点值相同，延伸该子树，否则左边路径长度为0
        if (root->left && root->left->val == root->val) {
            l += 1;
        } else {
            l = 0;
        }

        if (root->right && root->right->val == root->val) {
            r += 1;
        } else {
            r = 0;
        }

        // 向上延伸或者包含根节点的最大值。
        ans = max(l + r, ans);
        return max(l, r);
    }
};
```


