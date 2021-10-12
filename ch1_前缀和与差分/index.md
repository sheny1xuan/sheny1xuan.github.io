# acwing基础课ch1-前缀和与差分


## 前缀和

### 一维前缀和

+ 利用存储的部分前缀和快速计算部分数组的和
+ 前缀和数组长度为n+1
+ s[0] = 0, s[i]表示nums[i]前所有数的和，不包括nums[i]
+ s[i]表示前i个数的前缀和

``` cpp
#include <iostream>

using namespace std;

const int N = 1e5+10;
int a[N], s[N]; 

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)  scanf("%d", &a[i]);
    
    for(int i = 1; i <= n; i++){
        s[i] = s[i - 1] + a[i - 1];
    }
    // 注意这里输入的数据是前l, r个数字。
    while(m--){
        int l, r;
        cin >> l >> r;
        printf("%d\n", s[r] - s[l - 1]);
    }
    return 0;
}
```

### 二维前缀和->计算指定区域内的和

+ $s[i][j]$表示的是前i行，前j列的区域和。

``` cpp
#include <iostream>

using namespace std;

const int N = 1010;

int a[N][N], s[N][N];

int main(){
    int n, m, q;
    cin >> n >> m >> q;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            s[i][j] = a[i - 1][j - 1] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    
    while(q-- ){
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%d\n", s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1]);
    }
    
    return 0;
    
}
```



## 差分

+ 构造一个新的数组使原数组成为该数组的前缀和。
+ 作用：用O(1)的时间让某个区间[l, r]全部加上一个值
+ 原数组求差分数组相当于差分数组在对应位置插入原数组的值，a[l] + c, a[r+1] - c。

![image-20210509223554789](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210509223554789.png)

![image-20210509224652013](../pic/image-20210509224652013.png)

``` cpp
#include <iostream>

using namespace std;

const int N = 1e5+10;
int a[N], b[N];

void insert(int l, int r, int c){
    b[l] += c;
    b[r + 1] -= c;
}

int main(){
    int n, m;
    cin >> n >> m;
    
    for(int i = 1; i <= n; i++)  scanf("%d", &a[i]);
    // 原数组相当于差分数组在对应位置插入原数组的值
    for(int i = 1; i <= n; i++)  insert(i, i, a[i]);
    
    while(m--){
        int l, r, c;
        scanf("%d%d%d",&l, &r, &c);
        // 进行插入操作
        insert(l, r, c);
    }
    
    // 对b数组求前缀和得到修改以后的数组
    for(int i = 1; i <= n; i++){
        b[i] += b[i-1];
        printf("%d ",b[i]);
    }
    
    return 0;
    
}
```

### 二维差分数组

+ 在二维区域内$a[x1][y1]->a[x2][y2]$区域间所有的数加上一个数c.
+ 等同于其差分数组$b[x1][y1] += c$，$b[x2+1][y1]-=c$，$b[x1][y2+1]-=c$，$b[x2+1][y2+1]+=c$

![image-20210510154600293](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210510154600293.png)

``` cpp
#include <iostream>

using namespace std;

const int N = 1010;

int a[N][N], b[N][N];

void insert(int x1,int y1,int x2,int y2, int c){
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;
}

int main(){
    int n, m, q;
    
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
            insert(i, j, i, j, a[i][j]);
        }
    }
    
    while(q-- ){
        int x1, y1, x2, y2, c;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
        insert(x1, y1, x2, y2, c);
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            // 计算前缀和
            b[i][j] = b[i - 1][j] + b[i][j - 1] + b[i][j] - b[i - 1][j - 1];
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    
    return 0;
    
}
```


