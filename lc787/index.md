# lc787. K站中转内最便宜的航班




## [787. K 站中转内最便宜的航班](https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/)

+ Bellman_ford算法解决有边数限制的最短路问题
+ K站中转就是最多有k+1条边的最短路问题
+ [acwing模板题](https://www.acwing.com/problem/content/description/855/)

```cpp
const int N = 110;
const int M = N * N / 2;
struct edge{
    int a, b, w;
    edge(int x, int y, int z):a(x), b(y), w(z){};
    edge(){};
}Edge[M];

class Solution {
public:
    int bellman_ford(int n, int m, int k, int src, int dst){
        int dis[N], backup[N];
        // 初始化距离，并且设置起点为 0
        memset(dis, 0x3f, sizeof(dis));
        dis[src] = 0;

        for(int i = 0; i < k + 1; i++){
            // 备份
            memcpy(backup, dis, sizeof(dis));

            for(int j = 0; j < m; j++){
                int a = Edge[j].a, b = Edge[j].b, w = Edge[j].w;
                dis[b] = min(dis[b], backup[a] + w);
                // cout << dis[dst] << endl;
            }
        }

        if(dis[dst] == 0x3f3f3f3f)  return -1;
        return dis[dst];
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int idx = 0;
        for(auto& flight: flights){
            Edge[idx++] = edge{flight[0], flight[1], flight[2]};
        }

        return bellman_ford(n, idx, k, src, dst);
    }
};
```




