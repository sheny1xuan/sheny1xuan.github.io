# 

# 最小生成树与二分图

![image-20210608115349440](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210608115349440.png)

## 最小生成树

+ 生成树：包含所有节点的无环图。
+ 最小生成树：权值和最小的生成树。

### 朴素Prim算法

+ $O(n^2)$

1. 初始化所有点的距离
2. 遍历n个点，每次将一个点加入到最小生成树集合`S`
3. 找到距离`S`最近的点，将其加入集合，并且用改点更新其他点的距离。 

``` cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f;

int n, m;
int g[N][N];
int dis[N]; // dis表示点到集合的距离
bool st[N]; // st表示点是否在集合中

int prim(){
    memset(dis, 0x3f, sizeof(dis));
    
    int res = 0;
    
    for(int i = 0; i < n; i++){
        int t = -1;
        for(int j = 1; j <= n; j++){
            if(!st[j] && (t == -1 || dis[t] > dis[j])){
                t = j;
            }
        }
        
        // 无法继续更新，无最小生成树。
        if(i && dis[t] == INF)  return INF;
        // 第一个边不能加入最小生成树
        if(i)   res += dis[t];
        st[t] = true;
        
        for(int j = 1;j <= n; j++){
            // 注意这里是到集合的最短距离
            dis[j] = min(dis[j], g[t][j]);
        }
    }
    
    return res;
}

int main(){
    cin >> n >> m;
    
    memset(g, 0x3f, sizeof(g));
    
    while(m-- ){
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    
    int t = prim();
    
    if(t == INF)    cout << "impossible" << endl;
    else    cout << t <<endl;
    
    return 0;
}
```

### Kruskal算法

+ $O(mlogm)$

1. 将所有边按照权重从小到大排序。
2. 枚举每条边`a,b`权重为c
   1. 如果a，b不连通，将该条边加入最小生成树的集合当中
   2. 用并查集判断a，b是否在同一个连通块当中

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5+10;

int p[N], n, m;

struct edge{
    int a, b, w;
    
    bool operator<(edge ne){
        return w < ne.w;
    }
}Edge[N];

int find(int x){
    // 路径压缩
    if(p[x] != x)   p[x] = find(p[x]);
    return p[x];
}

int main(){
    cin >> n >> m;
    
    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        Edge[i] = {a, b, w};
    }
    // 1. 从小到大排序
    sort(Edge, Edge + m);
    
    for(int i = 1; i <= n; i++) p[i] = i;
    // 2.遍历所有的边
    int res = 0, cnt = 0;
    for(int i = 0; i < m; i++){
        int a = Edge[i].a, b = Edge[i].b, w = Edge[i].w;
        a = find(a), b = find(b);
        // a, b不属于同一个集合，将其加入集合
        if(a != b){
            cnt += 1;
            res += w;
            p[a] = b;
        }
    }
    
    if(cnt != n - 1)    cout << "impossible" << endl;
    else    cout << res << endl;
    
    return 0;
}
```

## 二分图问题

+ 二分图：将所有点分为两个集合，所有的边都在集合外部，集合内无边。

### 染色法判定二分图

+ 如果一个点染色， 则所有与该点相连的点的颜色都可以确定。
+ 二分图中当且仅当不含有奇数环(反证)。
+ 判断染色是否有矛盾。
+ $O(n)$

``` cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, M = 200010;

int n, m;
// 注意这里建图初始化为M条边
int h[M], e[M], ne[M], idx;
int color[N];

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool dfs(int x, int c){
    
    color[x] = c;
    
    for(int i = h[x]; i != -1; i = ne[i]){
        int j = e[i];
        
        if(!color[j]){
            // 如果没染色进行染色
            if(!dfs(j, 3 - c))  return false;
        }else{
            // 如果已经染色，判断染色是否冲突，是否有奇数环
            if(color[j] == c)   return false;
        }
    }
    
    return true;
}

int main(){
    cin >> n >> m;
    
    memset(h, -1, sizeof(h));
    
    while(m-- ){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    
    bool flag = true;
    for(int i = 1; i <= n; i++){
        if(!color[i]){
            if(dfs(i, 1) == false){
                flag = false;
                break;
            }
        }
    }
    
    if(flag == false){
        cout << "No" << endl;
    }else{
        cout << "Yes" << endl;
    }
    
    return 0;
}
```

### 匈牙利算法

+ 二分图的最大匹配
+ 二分图的两个集合可以一一匹配的最大的边数。
+ $O(nm)$

![image-20210612114149397](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210612114149397.png)

``` cpp
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 510, M = 100010;

int n1, n2, m;
int h[N], e[M], ne[M], idx;
int match[N];   // match表示右边的点对应的左边的点
bool st[N]; // st表示对于某个左边的点而言，右边的点是否访问过

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool find(int x){
    for(int i = h[x]; i != -1; i = ne[i]){
        int j = e[i];
        if(!st[j]){
            st[j] = true;
            // 如果未匹配，或者可以更改匹配
            if(match[j] == 0 || find(match[j])){
                match[j] = x;
                return true;
            }
        }
    }
    
    return false;
}

int main(){
    cin >> n1 >> n2 >> m;
    
    memset(h, -1, sizeof h);
    while(m --){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    int cnt = 0;
    for(int i = 1; i <= n1; i++){
        // 每个点只访问一次
        memset(st, false, sizeof st);
        if(find(i)) cnt += 1;
    }
    
    cout << cnt << endl;
    
    return 0;
}
```


