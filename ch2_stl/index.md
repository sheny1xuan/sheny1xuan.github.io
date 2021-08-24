# 

# STL基础知识

+ 系统为某一程序分配空间时，所需的时间与空间大小无关，与**申请次数**有关。

## vector

+ 动态数组

+ 初始化：`vector<int> a(10, 1);`
+ `a.size()`,`a.empty()`这两个操作是所有STL都有的操作
+ `a.clear()`清空动态数组
+ 倍增思想：长度不够，申请长度翻倍之后复制之前的值。
+ `a.front(), a.back()`
+ `a.push_back(), a.pop_back()`
+ `a.begin(), a.end()`

## pair

+ 存储一个二元组
+ `pair<int, int> a`
+ `a.first, a.second`
+ 可以用列表初始化`pair<int, int> a = {1, 2}`

## string

+ `size(), empty(),clear()`
+ `a.substr(begin, length)`下标从begin开始长度为length的子串，省略第二个参数的话长度默认到最后。

## queue

+ `push()`：队尾插入元素
+ `front()`：返回队头元素
+ `back()`：返回队尾元素
+ `pop()`：弹出队头元素

## priority_queue 优先队列

+ 默认大顶堆
+ 小顶堆定义`priority_queue<int, vector<int>, greater<int>> heap;`
+ `push()`：插入一个元素
+ `top()`:返回堆顶元素
+ `pop()`:删除堆顶元素

## stack

+ `push()`
+ `top()`
+ `pop()`

## deque

+ `size()`
+ `empty()`
+ `clear()`
+ `front()/back()`
+ `push_front()/ push_back()`
+ `pop_front()/pop_back()`
+ []
+ 效率很低

## set/multiset

+ 红黑树实现/有序列表

+ set不能有重复元素，重复元素忽略，multiset支持重复元素
+ `insert()`
+ `find()`
+ `count()`
+ `erase(x)`:删除所有x`O(logn+k)`
+ `lower_bound(x)`:返回大于等于x的最小元素的迭代器
+ `upper_bound(x)`:返回大于x的最小元素的迭代器

## map/multimap

+ 红黑树实现/有序映射
+ `insert()`:参数是pair
+ `find()`
+ `erase()`
+ []:时间复杂度`O(logn)`

## unordered_set/unordered_multiset

+ `O(1)`
+ 内部无序，哈希表实现
+ 不支持迭代器

## bitset/压位










