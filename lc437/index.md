# lc437.路径总和 III




## [437.路径总和 III](https://leetcode-cn.com/problems/path-sum-iii/)

### dfs+bfs

+ 因为从每个结点开始都有可能向下产生指定的路径和，所以我们可以从每个结点开始遍历，找到从该节点向下的所有的路径和。

``` cpp
class Solution {
public:
    int target, cnt;
    void dfs(TreeNode* root, int sum){
        if(root == nullptr){
            return;
        }

        int cur = sum + root->val;
        if(cur == target){
            cnt ++;
        }

        dfs(root->left, cur);
        dfs(root->right, cur);
    } 
    int pathSum(TreeNode* root, int targetSum) {
        if(root == nullptr){
            return 0;
        }
        target = targetSum; 
        cnt = 0;
        queue<TreeNode*> que;

        que.push(root);

        while(!que.empty()){
            auto f = que.front();
            que.pop();

            dfs(f, 0);
            // cout << f->val << ' ' << cnt << endl;
            if(f->left){
                que.push(f->left);
            }
            if(f->right){
                que.push(f->right);
            }
        }

        return cnt;
    }
};
```

### DFS+DFS

+ 当然这里遍历所有节点和寻找指定结点和的过程都可以通过DFS来做，也可以都通过BFS来做，这里再写一种双DFS的写法
+ 先序遍历访问所有的结点

``` cpp
class Solution {
public:
    int target, cnt;
    void dfs(TreeNode* root, int sum){
        if(root == nullptr){
            return;
        }

        int cur = sum + root->val;
        
        if(cur == target){
            cnt ++;
        }

        dfs(root->left, cur);
        dfs(root->right, cur);
    }

    void pre_travel(TreeNode* root){
        if(root == nullptr){
            return;
        }
        dfs(root, 0);
        pre_travel(root->left);
        pre_travel(root->right);
    }
    int pathSum(TreeNode* root, int targetSum) {
        target = targetSum; 
        cnt = 0;
        
        pre_travel(root);

        return cnt;
    }
};
```




