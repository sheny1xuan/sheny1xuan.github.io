# lc802.找到最终的安全状态


## [802. 找到最终的安全状态](https://leetcode-cn.com/problems/find-eventual-safe-states/)

### 染色法(DFS)

+ **理解题目的意思**：**无论怎么走**必定到达终点

+ 也就是说该节点不能与环相连接

+ 三色标记 label[i]表示当前结点的状态

  + 0: 未访问

  + 1: 可以到达环，或者在环中

  + 2: 可以在有限步到达终点，不会进入到环。

+ T:O(m+n)

+ S:O(n)

``` cpp
class Solution {
public:
    // **理解题目的意思**：**无论怎么走**必定到达终点
    // 也就是说该节点不能与环相连接
    // 三色标记 label[i]表示当前结点的状态
    // 0: 未访问
    // 1: 可以到达环，或者在环中
    // 2: 可以在有限步到达终点，不会进入到环。
    // T:O(m+n)
    // S:O(n)
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> label(n, 0);

        function <bool(int)> safe = [&](int x){
            if(label[x] > 0){
                return label[x] == 2;
            }
            label[x] = 1;
            for(auto &y :graph[x]){
                if(safe(y) == false){
                    return false;
                }
            }
            label[x] = 2;
            return true;
        };

        vector<int> res;
        for(int i = 0; i < n; i++){
            if(safe(i)){
                res.push_back(i);
            }
        }

        return res;
    }
};
```

### 拓扑排序

+ 将所有边翻转，原来终点(出度为0)反转后入度为零
+ 在环内或者可以到达环的点，反转后经过拓扑排序入度肯定不为0.

``` cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> rg(n, vector<int>());
        vector<int> res;
        vector<int> indegree(n, 0);

        // 反向图
        for(int i = 0; i < n; i++){
            auto node = graph[i];
            for(auto& to_node: node){
                rg[to_node].push_back(i);
                indegree[i] += 1;
            }
        }
        // 拓扑排序
        queue<int> que;

        // 添加入度为0的点
        for(int i = 0; i < n; i++){
            if(indegree[i] == 0){
                que.push(i);
            }
        }

        while(!que.empty()){
            int x = que.front();
            que.pop();

            for(auto& y: rg[x]){
                indegree[y]--;
                if(indegree[y] == 0){
                    que.push(y);
                }
            }
        }

        // 把最后入度为0的点添加到结果集。
        for(int i = 0; i < n; i++){
            if(indegree[i] == 0){
                res.push_back(i);
            }
        }
        return res;
    }
};
```


