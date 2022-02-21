# acwing基础课ch3-搜索算法


## 搜索算法

## DFS与BFS

+ DFS:	stack， $O(h)$，h指的是深度
+ BFS： queue,  $O(2^h)$，具有最短路的性质
+ DFS可以使用递归树进行理清思路
+ 剪枝：直接判断当前状态不合法，直接不继续向下搜索。

## DFS习题

### 全排列（无重复数字）

+ 回溯搜索

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10;

int a[N], vis[N], path[N];
// c表示当前路径上的个数
void dfs(int n, int c){
    // 递归终止条件
    if(c >= n){
        for(int i = 0; i < n; i++ )    cout << path[i] << ' ';
        cout << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        if(vis[i] == 0){
            // 递归
            vis[i] = 1;
            path[c] = a[i];
            dfs(n, c + 1);
            // 回溯
            vis[i] = 0;
        }
    }
    
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        a[i] = i + 1;
    }
    
    dfs(n, 0);
    
    return 0;
}

```

+ 使用next_permutation()

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10;

int a[N];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        a[i] = i;
    }
    
    do{
        for(int i = 1; i <= n; i++){
            cout << a[i] << ' ';
        }
        cout << endl;
    }while(next_permutation(a+1, a+1+n));
    
    return 0;
}

```

### 子集问题

### 八皇后问题

+ 相同行，列，对角线不能存在皇后

``` cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10;

char g[N][N];
int n;
int dx[] = {-1, -1, -1, 1, 1, 1}, dy[] = {-1, 0, 1, -1, 0, 1};
// 检查每行每列是否满足要求
bool check(int x, int y){
    for(int i = 0; i < 6; i++){
        int x1 = x + dx[i], y1 = y + dy[i];
        while(x1 >= 0 && x1 < n && y1 >= 0 && y1 < n){
            if(g[x1][y1] == 'Q')    return false;
            x1 = x1 + dx[i], y1 = y1 + dy[i];
        }
    }
    return true;
}

void dfs(int cur){
    if(cur >= n){
        for(int i = 0; i < n; i++)  cout << g[i] << endl;
        cout << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        if(check(cur, i)){
            g[cur][i] = 'Q';
            dfs(cur+1);
            g[cur][i] = '.';
        }
    }
}

int main(){
    cin >> n;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            g[i][j] = '.';
        }
    }
    
    dfs(0);
    
    return 0;
}
```

## BFS习题

+ 宽度优先搜索最大的优势就是最短路径，所有的路径权重都是1的情况。
+ 队列

### AC844. 走迷宫

![image-20210525155420009](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210525155420009.png)

``` cpp
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<int, int> PII;

const int N = 100;
// a存储整个地图，vis存储每个节点到原点的距离。
int a[N][N];
int vis[N][N];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};

int main(){
    int n, m;
    cin >> n >> m;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    queue<PII> que;
    
    que.push({0, 0});
    
    while(!que.empty()){
        // 队头元素
        auto f = que.front();
        que.pop();
        int row = f.first, col = f.second;
        if(row == n - 1 && col == m - 1){
            cout << vis[row][col] << endl;
            break;
        }
        
        // 队头元素进行拓展
        for(int i = 0; i < 4; i++){
            int x =row + dx[i], y = col + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < m){
                if(vis[x][y] == 0 && a[x][y] == 0){
                    que.push({x, y});
                    vis[x][y] = vis[row][col] + 1;
                }
            }
        }
    }
    
    return 0;
    
}


```


