# acwing基础课ch3-最短路问题


## 最短路问题

![image-20210528103321197](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210528103321197.png)

## 单源最短路

+ 从起点到其他所有点的最短距离。

### 所有边权都是正数

+ Dijkstra基于贪心

#### 朴素Dijkstra

+ $T:O(n^2)，n为点的数量，m为边的数量$，适合于稠密图

1. 初始化dis数组，$dis[1]=0$,$dis[i]=inf$，S为已经确定最短路径的点集
2. 迭代n次，每次确定一个点的最短路径。
3. 找到不在S中距离源点最近的点t，并将t加入到S（$n^2$次）
4. 用t更新其他点的距离:$dis[x] > dis[t] + dis(t->x)$（$m$次）

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210528112545136.png" alt="image-20210528112545136" style="zoom:67%;" />

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510;
const int INF = 0x3f3f3f3f;
// 稠密图，使用邻接矩阵
int n, m;
int g[N][N];
int dis[N];    // 从1到每个点的最短距离
bool st[N];     // 已经确定距离的点集

int dijkstra(){
    // 1.初始化为INF
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    // 2.循环n次，每次确定一个点
    for(int i = 0; i < n; i++){
        // 3.找到当前距离1最近的点
        int t = -1;
        for(int j = 1; j <= n; j++){
            if(!st[j] && (t == -1 || dis[j] < dis[t])){
                t = j;
            }
        }
        // 将该点加入确定的点的集合
        st[t] = true;
        // 4.更新其他点的距离
        for(int j = 1; j <= n; j++){
            dis[j] = min(dis[j], dis[t] + g[t][j]);
        }
    }
    if(dis[n] == 0x3f3f3f3f)    return -1;
    else return dis[n];
}

int main(){
    cin >> n >> m;
    
    // 存在重边，重边只用保留长度最短的边
    memset(g, 0x3f, sizeof(g));
    
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    
    int t = dijkstra();
    
    cout << t << endl;
    
    return 0;
    
}
```

#### 堆优化Dijkstra

+ $T:O(mlogn)$适合于稀疏图

1. 初始化dis数组，$dis[1]=0$,$dis[i]=inf$，S为已经确定最短路径的点集
2. 迭代n次，每次确定一个点的最短路径，因为使用堆优化，所以每次确定最短路径时间为$logn$。
3. 用堆找到不在S中距离源点最近的点t，并将t加入到S（$n$次）
4. 用t更新其他点的距离:$dis[x] > dis[t] + dis(t->x)$（$mlogn$次，实际为$mlogm$,因为无法堆中无法更新指定点的距离，存在冗余）。

<img src="https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210528115521335.png" alt="image-20210528115521335" style="zoom:70%;" />

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e6+10;

int h[N], ne[N], e[N], w[N], idx;
int n, m;
int dis[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dijkstra(){
    // 1. 初始化
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    
    priority_queue<PII, vector<PII>, greater<PII>> heap; 
    heap.push({dis[1], 1});
    
    while(heap.size()){
        // 2. 找到距离最短的点，并且标记
        auto t = heap.top();
        heap.pop();
        
        int node = t.second, distance = t.first;
        // 已经访问过，这个为冗余边
        if(st[node]) continue;
        st[node] = true;
        
        // 3. 用当前点更新其他点的距离。
        for(int i = h[node]; i != -1; i = ne[i]){
            int j = e[i];
            if(dis[j] > dis[node] + w[i]){
                dis[j] = dis[node] + w[i];
                heap.push({dis[j], j});
            }
        }
    }
    
    if(dis[n] == 0x3f3f3f3f)    return -1;
    else return dis[n];
}

int main(){
    cin >> n >> m;
    memset(h, -1, sizeof(h));
    
    while(m-- ){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    
    int t = dijkstra();
    
    cout << t << endl;
    
    return 0;
}
```

### 存在负边权

+ 如果存在负权回路，最短路可能不存在。

#### Bellman-Ford

+ 连续进行松弛，每次松弛时把每条边都更新一下，若在n次松弛后还能更新，则说明图中有负环。
+ $T:O(mn)$

1. 迭代k次（**k的意义:路径长度为k的最短路径**），注意把`dis`进行`backup`，防止更新过程对下一个产生影响。
2. 遍历**所有的边**，对于`a->b,w`更新`dis[b] = min(dis[b], backup[a] + w)`

+ 注意要对所有点的距离进行备份，防止在更新过程中收到影响。
+ bellman - ford**算法擅长解决有边数限制的最短路问题**

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510, M = 10100;

int dis[N], backup[N], n, m, k;

struct edge{
    int a, b, w;
    edge(int x, int y, int z):a(x), b(y), w(z){};
    edge(){};
}Edge[M];

int bellman_ford(){
    // 初始化距离为无穷，并且要把1点的距离置为0
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    // dis数组意义，迭代k次，路径长度为k的最短距离为dis
    for(int i = 0; i < k; i++){
        memcpy(backup, dis, sizeof(dis));	// 注意要备份
        
        for(int j = 0; j < m; j++){
            int a = Edge[j].a, b = Edge[j].b, w = Edge[j].w;
            dis[b] = min(dis[b], backup[a] + w);
        }
    }
    
    if(dis[n] > 0x3f3f3f3f / 2) return -1;
    else return dis[n];
}

int main(){
    cin >> n >> m >> k;
    
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        Edge[i] = {a, b, w};
    }
    
    int t = bellman_ford();
    if(t == -1)    cout << "impossible" << endl;
    else cout << t << endl;
    
    return 0;
}

```

#### SPFA

+ $T:O(m),最坏O(mn)$
+ SPFA**不能存在负权回路**
+ 对bellman-ford算法的距离更新进行优化，当a进行更新时，b才会更新。

![image-20210605104530328](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210605104530328.png)

+ BFS进行优化，队列中存储距离变小的节点，队列中存储可以更新其他点的点。
+ 当队列不为空，队头出队。
+ 并且访问队头元素所有的边，如果目标点的距离可以被更新则将其加入到队列中。

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5+10, M = 1e5+10;

int dis[N], h[N], n, m;
int e[M], ne[M], w[M], idx = 0;
// st表示当前节点是否在队列中
// 如果当前节点在队列中，则不可以通过其他节点更新该点。
bool st[N]; 

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; 
}

int spfa(){
    // 1.初始化所有节点距离，将1节点入队
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    
    queue<int> que;
    que.push(1);
    st[1] = true;
    // 2.队列不为空时，使用队头节点更新其他节点。
    while(!que.empty()){
        int t = que.front();
        que.pop();
        
        st[t] = false;  // 该节点已经不再队列中
        
        for(int i = h[t]; i != -1; i = ne[i]){
            int node = e[i], distance = w[i];
            if(dis[node] > dis[t] + distance){
                dis[node] = dis[t] + distance;
                // 2.1如果该节点被更新，入队。
                if(!st[node]){
                    que.push(node);
                    //  标记该节点
                    st[node] = true;
                } 
            }
        }
    }
    
    if(dis[n] == 0x3f3f3f3f)    return -1;
    else return dis[n];
}

int main(){
    cin >> n >> m;
    
    memset(h, -1, sizeof(h));
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    
    int t = spfa();
    
    if(t == -1)     cout << "impossible" << endl;
    else    cout << t << endl;
    
    return 0;
}
```

#### SPFA判断负环

+ 用`cnt`数组记录从源点到该点最短距离经过的边数。
+ 更新距离的过程中同时更新边数，`dis[b] = dis[a] + w -> cnt[b] = cnt[a] + 1`
+ 如果更新的`cnt > n`则表示存在负环。

## 多源最短路

### Floyd算法

+ 基于动态规划`d[k,i,j] = d[k-1,i,k]+d[k-1,k,j]`,k表示只经过`1->k`这些点
+ $O(n^3)$
+ 枚举中间变量`k`
+ 枚举起点`i`，枚举终点`j`,`d[i][j] = min(d[i][j], d[i][k] + d[k][j])`

``` cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, INF = 1e9;
int n, m, q;
int d[N][N];

void floyd(){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main(){
    cin >> n >> m >> q;
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            // 初始化自己到自己的距离0，自己到其他点的距离为无穷
            if(i == j)  d[i][j] = 0;
            else    d[i][j] = INF;
        }
    }
    
    while(m-- ){
        int a, b, w;
        cin >> a >> b >> w;
        d[a][b] = min(w, d[a][b]);
        
    }
    
    floyd();
    
    while(q-- ){
        int a, b;
        cin >> a >> b;
        
        if(d[a][b] > INF / 2)   cout << "impossible" << endl;
        else    cout << d[a][b] << endl;
        
    }
    
    return 0;
}
```


