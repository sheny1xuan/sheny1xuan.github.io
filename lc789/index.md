# lc789.逃脱阻碍者




## [789. 逃脱阻碍者](https://leetcode-cn.com/problems/escape-the-ghosts/)

+ 起始点和阻碍者应该同时沿着最短路向目标移动。
+ 由于类似于棋盘的网格状，因此最短路径距离就是曼哈顿距离。
+ 存在以下三种情况。
  + 存在任一阻碍者到达目标的最短路比起始点短，返回false
  + 存在任一阻碍者到达目标的最短路与起始点相同，二者同时到达，返回false
  + 所有阻碍者到达目标的最短路都比起始点远，则可以从起点到达目标点，返回true

``` cpp
class Solution {
public:
    int calmanhattanDistance(vector<int>& p1, vector<int> p2){
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
    }
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int okDistance = calmanhattanDistance(target, {0, 0});

        for(auto& ghost: ghosts){
            int curDistance = calmanhattanDistance(target, ghost);
            if(curDistance <= okDistance){
                return false;
            }
        }

        return true;
    }
};
```




