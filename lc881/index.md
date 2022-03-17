# lc881. 救生艇




## [881. 救生艇](https://leetcode-cn.com/problems/boats-to-save-people/)

### 贪心+双指针

+ $T:O(nlogn)$

``` cpp
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int n = people.size(), cnt = 0;
        // 双指针+贪心
        // 从小到大进行排序
        // i指向最小,j指向最大
        // i和j相加小于limit,则i与所有的j都可以组合成一组,此时应该贪心选择最优策略，两个相加重量最大
        // i和j相加大于limit,则j与其他所有的i都不可以组成一组,j--
        for(int i = 0, j = n - 1; i <= j;){
            if(people[i] + people[j] <= limit){
                i++;j--;
            }else{
                j--;
            }

            cnt += 1;
        }

        return cnt;
    }
};
```


