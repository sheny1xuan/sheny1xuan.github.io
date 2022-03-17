# lc543.二叉树的直径




## [543.二叉树的直径](https://leetcode-cn.com/problems/diameter-of-binary-tree/)

+ 某个结点二叉树的高度等于左右子树中最高的高度+1。
+ 二叉树最大直径，可以在计算高度过程中计算每个结点左右子树的最大路径长度`(max(l+r))`。

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
    int diameterOfBinaryTree(TreeNode* root) {
        height(root);
        return ans;
    }

    int height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int l = height(root->left);
        int r = height(root->right);
        ans = max(ans, l + r);

        return max(l, r) + 1;
    }
};
```


