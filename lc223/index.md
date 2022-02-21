# lc223.矩形面积




## [223.矩形面积](https://leetcode-cn.com/problems/rectangle-area/)

<img src="https://assets.leetcode.com/uploads/2021/05/08/rectangle-plane.png" alt="Rectangle Area" style="zoom: 50%;" />

### 简单的考虑

+ 计算两个图形的重叠部分，如果两个图形无重复，直接返回两个图的面积和。
+ 考虑不重叠的情况`b1x >= ax2 || ax1 >= bx2 || ay2 <= by1 || ay1 >= by2`这四种情况存在时，直接返回面积和。
+ 考虑a总在左边的情况，如果`ax1>bx1`时，将a，b互换
+ 那么最后重叠的面积就是`(min(bx2, ax2) - bx1) * (min(ay2, by2) - max(by1, ay2))`

``` cpp
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int all = get(ax2 - ax1, ay2 - ay1) + get(bx2 - bx1, by2 - by1);
        if(by1 >= ay2 || ay1 >= by2){
            return all;
        }
        if(ax1 >= bx2 || bx1 >= ax2){
            return all;
        }
        if(ax1 > bx1){
            return computeArea(bx1, by1, bx2, by2, ax1, ay1, ax2, ay2);
        }

        return all - get(min(ax2, bx2) - bx1, min(ay2, by2) - max(by1, ay1));
    }

    int get(int a, int b){
        return a * b;
    }
};
```

### 考虑矩形在轴上的投影

+ 矩形a在x,y轴投影分别为`(ax1, ax2)`，`(ay1, ay2)`，b同理
+ a,b需要在两个轴上的投影同时存在时，才能计算重叠部分的面积
+ 在某一个轴上投影有重叠的计算方法`min(ax2, bx2) - max(ax1, bx1) > 0`

``` cpp
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int all = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);

        int x_both = min(ax2, bx2) - max(ax1, bx1);
        int y_both = min(ay2, by2) - max(ay1, by1);

        return all - max(x_both, 0) * max(y_both, 0);
    }
};
```


