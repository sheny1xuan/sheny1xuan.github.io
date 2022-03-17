# acwing基础课ch2-并查集


## 并查集

### 并查集是什么

**Union,Find,Set**

- 并查集包含Union,Find,Set3个关键词，是一种维护**集合**的基本操作。
- 并查集是一种用树表示的集合，树根的编号表示集合的编号。

![image-20210517173058846](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210517173058846.png)

### 并查集实现的方法

- 并查集由两个任务：
- **合并**：合并两个集合。
- **查找**：判断两个元素是否在一个集合内。
- 实现：数组实现，索引表示结点编号，数组的值表示索引的根节点。
  同一个集合中只能包含一个**根节点(father[i] = i)**。

+ **查找父节点**

``` cpp
int findFather(int x, int father[]){
    while(x != father[x]){
        x = father[x];
    }
    return x;
}
```

+ **合并结点**
  + 一定要使用**根节点**进行合并。
  + 查找它们的根节点，如果他们根节点不同，则属于不同的集合才可以进行合并。

``` cpp
void Union(int a, int b, int fa[]){
	fa[find(a)] = find(b);
}
```

+ **路径压缩**
  + 把当前查询结点的路径上所有节点的父亲都指向根节点。

``` cpp
int find(int x, int fa[]){
	if(x != far[x])	fa[x] = find(fa[x]);
    return fa[x];
}
```

### 写法

+ 静态

``` cpp
int fa[N];

// 初始化
for(int i = 1; i <= n; i++){
    fa[i] = i;
}

// find
int find(int x){
	if(x = fa[x])	return x;
    f[x] = find(f[x]);
    return f[x];
}
// 合并
void Union(int x){
    fa[find(x)] = find(y);
}
// 查询
int qury(int x, int y){
    return find(y) == find(y);
}
```

+ OOP

``` cpp
class findUnionSet{
  private:
  vector<int> f;
  public:
  findUnionSet(int n = N){
      f = vector<int>(n + 1, 0);
      for(int i = 1; i <= n; i++){
          f[i] = i;
      }
  }
  int find(int x) {
      if(x == f[x])	return x;
      f[x] = find(f[x]);
      return f[]
  }
  
  void un(int x, int y) {
      f[find(x)] = find(y);
  }
  
  bool qury(int x, int y) {
      return find(x) == find(y);
  }
  
};
```



## [Ac836.合并集合](https://www.acwing.com/problem/content/838/)

![image-20210517182449034](https://picture-table.oss-cn-beijing.aliyuncs.com/img/image-20210517182449034.png)

``` cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5+10;

class findUnionSet{
  private:
  vector<int> f;
  public:
  findUnionSet(int n = N){
      f = vector<int>(n + 1, 0);
      for(int i = 1; i <= n; i++){
          f[i] = i;
      }
  }
  int find(int x) {
      if(x != f[x]) f[x] = find(f[x]);
      return f[x];
  }
  
  void un(int x, int y) {
      f[find(x)] = find(y);
  }
  
  bool qury(int x, int y) {
      return find(x) == find(y);
  }
  
};

int main(){
    int n, m;
    cin >> n >> m;
    
    findUnionSet myun;
    
    while(m--){
        char op;
        int x, y;
        cin >> op >> x >> y;
        if(op == 'M'){
            myun.un(x, y);
        }
        else{
            if(myun.qury(x, y))  cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    
    return 0;
}
```


