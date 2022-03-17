# lc743.网络延迟时间




## [743. 网络延迟时间](https://leetcode-cn.com/problems/network-delay-time/)

### dijkstra最短路问题

+ 题意为找距离`k`最短路径中的最大值作为传递时间

+ `Cpp Tips:`在对象内初始化`vector`注意事项
  + class内部成员`vector<int> x(n, 0)`不可以使用，这样会被编译器认为是返回值为`vector<int>`的成员函数，报错`unknown type`.
  + 但是可以通过复制构造函数进行构造`c++11/c++15`
  + [参考链接](https://stackoverflow.com/questions/29977828/c-error-unknown-type-name)

``` cpp
class t{
    public:
    // vector<int> s(5, 0); 	// 编译错误，unknown type of 5
    vector<int> s = vector<int>(5, 0);	// 复制构造函数
}
```

#### 稠密图：朴素dijkstra()

+ `T:O(mn + n*n)`
``` cpp
const int N = 110, M = 6100;

class Solution {
public:
    int h[N], e[M], w[M], ne[M];
    bool vis[N];
    int dis[N];
    int idx = 0, n = 0;

    int dijkstra(int k){
        memset(vis, false, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));

        dis[k] = 0;

        // dijkstra找到距离起点最短距离的最长路径(无堆优化)
        // T: O(nm)
        for(int i = 0; i < n; i++){
            int find = -1;
            for(int j = 1; j <= n; j++){
                if(vis[j] == false && (find == -1 || dis[j] < dis[find] )){
                    find = j;
                }
            }
            vis[find] = true;

            for(int u = h[find]; u != -1; u = ne[u]){
                int x = e[u];
                dis[x] = min(dis[find] + w[u], dis[x]);
            }
        }

        for(int i = 1; i <= n ; i++){
            if(dis[i] == 0x3f3f3f3f)   return -1;
        }

        return *max_element(dis+1, dis+n+1);
    }
    int networkDelayTime(vector<vector<int>>& times, int n_, int k) {
        n = n_;

        for(int i = 1; i <= n; i++){
            h[i] = -1;
        }

        for(auto& edge: times){
            add(edge[0], edge[1], edge[2]);
        }

        int res = dijkstra(k);

        if(res != -1){
            return res;
        }else{
            return -1;
        }
    }

    void add(int a, int b, int w_){
        e[idx] = b; w[idx] = w_; ne[idx] = h[a]; h[a] = idx++;
    }
};
```

#### 稀疏图：堆优化dijkstra()

+ `T:O(nlogm)`

``` cpp
const int N = 110, M = 6100;
typedef pair<int, int> PII;

class Solution {
public:
    int h[N], e[M], w[M], ne[M];
    bool vis[N];
    int dis[N];
    int idx = 0, n = 0;

    int dijkstra(int k){
        memset(vis, false, sizeof(vis));
        memset(dis, 0x3f, sizeof(dis));

        dis[k] = 0;

        // dijkstra堆优化，优化找最短路径的过程
        // 稀疏图
        // T: O(mlogn)
        priority_queue<PII, vector<PII>, greater<PII> > heap;
        heap.push({dis[k], k});

        while(heap.size()){
            auto t = heap.top();
            heap.pop();

            int distance = t.first, node = t.second;
            if(vis[node])   continue;
            vis[node] = true;
            
            for(int u = h[node]; u != -1; u = ne[u]){
                int x = e[u];
                if(dis[x] > dis[node] + w[u]){
                    dis[x] = dis[node] + w[u];
                    heap.push({dis[x], x});
                }
            }
        }

        for(int i = 1; i <= n ; i++){
            if(dis[i] == 0x3f3f3f3f)   return -1;
        }

        return *max_element(dis+1, dis+n+1);
    }
    int networkDelayTime(vector<vector<int>>& times, int n_, int k) {
        n = n_;

        for(int i = 1; i <= n; i++){
            h[i] = -1;
        }

        for(auto& edge: times){
            add(edge[0], edge[1], edge[2]);
        }

        int res = dijkstra(k);

        if(res != -1){
            return res;
        }else{
            return -1;
        }
    }

    void add(int a, int b, int w_){
        e[idx] = b; w[idx] = w_; ne[idx] = h[a]; h[a] = idx++;
    }
};
```


