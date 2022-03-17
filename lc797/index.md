# lc797.所有可能的路径




## [797. 所有可能的路径](https://leetcode-cn.com/problems/all-paths-from-source-to-target/)

### DFS

+ 有向无环图`DAG`不会重复访问同一个点，所以不需要记录这些点是否访问过。

``` cpp
class Solution {
public:
    vector<vector<int>> res;
    void dfs(vector<vector<int>>& g, int begin, vector<int>& path, int n ){
        if(begin == n){
            res.push_back(path);
            return;
        }
        for(int i = 0; i < g[begin].size(); i++){
            path.push_back(g[begin][i]);
            dfs(g, g[begin][i], path, n);
            path.pop_back();
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int> path;
        int n = graph.size() - 1;
        path.push_back(0);
        dfs(graph, 0, path, n);

        return res;
    }
};
```




