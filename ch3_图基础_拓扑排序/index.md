# acwing基础课ch3-图基础与拓扑排序


## 图基础

### 有向图

+ 节点之间存在方向

#### 存储方法

+ 邻接矩阵：二维数组。
+ 邻接表：n个单链表，类似于哈希表的拉链法。

+ 邻接表存储模板

``` cpp
// 邻接表
int h[N], e[N * 2], ne[N * 2], idx;
// add a -> b
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
```

### 树与图的深度优先搜索

#### 有向图DFS模板

``` cpp
// 需要标记数组st[N],  遍历节点的每个相邻的边
void dfs(int u) {
    st[u] = true; // 标记，j
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            dfs(j);
        }
    }
}
```

#### 树的重心

![image-20210527100218768](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210527100218768.png)

+ 后序遍历

![image-20210527100348627](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210527100348627.png)

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5+10;
// h表示每个节点的链表头节点，e表示使用的下标为idx的节点的值
// ne表示下标为idx的节点的下一个节点，idx表示当前使用的节点个数。
// 注意所有节点的链表节点头要初始化为-1
int h[N], e[N*2], ne[N*2], idx;
bool vis[N];
int n, ans = N;

// 有向图邻接表
// a->b插入一个节点
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
// 相当于是后序遍历，dfs返回每个子树节点的个数。
int dfs(int u){
    vis[u] = true;
    
    int num = 1, res = 0;
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(!vis[j]){
            vis[j] = true;
            
            int t = dfs(j);
            res = max(res, t);
            num += t;
        }
    }
    // n-num为树上半部分的节点数
    res = max(res, n - num);
    ans = min(res, ans);
    
    return num;
}

int main(){
    memset(h, -1, sizeof(h));
    cin >> n;
    
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        // 无向图
        add(a, b), add(b, a);
    }
    
    dfs(1);
    
    cout << ans << endl;
    
    return 0;
}
```

### 树与图的宽度优先搜索

+ 解决权重相同的最短路问题
+ 使用队列进行宽度优先搜索

``` cpp
queue <- head
while(queue){
    t <- queue head
    标记t已经访问
    拓展t
}
```

#### 图中点的层次

![image-20210527103239597](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210527103239597.png)

+ 相同权重的最短路问题

``` cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5+10;

int h[N], e[N], ne[N], idx;
// d表示每个节点到1节点的距离。
int d[N];
int n, m;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int bfs(int x){
    queue<int> que;
    
    que.push(x);
    
    memset(d, -1, sizeof(d));
    d[x] = 0;
    
    while(!que.empty()){
        int t = que.front();

        que.pop();
        
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];

            if(d[j] == -1){
                d[j] = d[t] + 1;
                que.push(j);
            }
            
        }
    }
    
    return d[n];
}

int main(){
    cin >> n >> m;
    
    memset(h, -1, sizeof(h));
    
    while(m--){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    cout << bfs(1) << endl;
    
    return 0;
}
```

## 拓扑排序

+ 有向图
+ 宽度优先搜索的应用。
+ 起点在其对应的终点前面。
+ 有向无环图一定存在拓扑序列，也称为拓扑图。

![image-20210527104615087](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210527104615087.png)

+ 步骤
  + 所有入度为0的点入队
  + 依次出队，删除入度为0的点，修改该点的邻接点的入度数
  + 如果邻接点的入度数为0，将该邻接点入队。

### 有向图的拓扑序列

![image-20210527112652006](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210527112652006.png)

``` cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5+10;

int h[N], e[N*2], ne[N*2], idx;
// d存储每个节点的入度个数。
int d[N];
int n, m;

void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    d[b] += 1;
}

bool topsort(vector<int>& res){
    queue<int> que;
    
    for(int i = 1; i <= n; i++){
        if(d[i] == 0){
            que.push(i);
        }
    }
    int in_que = 0;

    while(!que.empty()){
        int t = que.front();
        // 出队顺序就是拓扑排序的顺序
        res.push_back(t);
        que.pop();
        in_que += 1;
        
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            d[j] -= 1;
            if(d[j] == 0){
                que.push(j);
            }
        }
    }
    
    return in_que == n;
}

int main(){
    memset(h, -1, sizeof(h));
    
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    vector<int> res;
    if(topsort(res)){
        for(int i = 0; i < res.size(); i++){
            cout << res[i] << ' ';
        }
        cout << endl;
    }else{
        cout << -1 << endl;
    }
    
    return 0;
}
```


