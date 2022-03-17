# lc502. IPO




## [502. IPO](https://leetcode-cn.com/problems/ipo/)

+ 如果没有k的限制：依次将资本消耗从小到大进行排序，然后投资capital[i],之后w+=profits[i]
+ 有了k的限制
  + 首先仍是将资本消耗从小到大排序
  + 但是在选择项目时需要考虑利润的因素，每一次需要选择所有满足资本投资capital[i] < w中利润最大的项目，可以利用最大堆获取。
  + 这里需要注意的是，在每次投资之后资本w1会变大为w2，每次只需将w1->w2之间的项目入堆即可。
+ $O(n + k)logn$

``` cpp
typedef pair<int, int> PII;

class Solution {
public:
    // 如果没有k的限制：依次将资本消耗从小到大进行排序，然后投资capital[i],之后w+=profits[i]
    // 有了k的限制
    // 首先仍是将资本消耗从小到大排序
    // 但是在选择项目时需要考虑利润的因素，每一次需要选择所有满足资本投资capital[i] < w中利润最大的项目，可以利用最大堆获取。
    // 这里需要注意的是，在每次投资之后资本w1会变大为w2，每次只需将w1->w2之间的项目入堆即可。
    // $O(n + k)logn$
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<PII> projects;
        int n = profits.size(), idx = 0;
        priority_queue<int, vector<int>> hp;

        for(int i = 0; i < n; i++){
            projects.push_back({capital[i], profits[i]});
        }
        // 排序
        sort(projects.begin(), projects.end());

        for(int i = 0; i < k; i++){
            while(idx < n && projects[idx].first <= w){
                hp.push(projects[idx].second);
                idx++;
            }

            if(hp.empty()){
                break;
            }else{
                w += hp.top();
                hp.pop();
            }
        }

        return w;
    }
};
```




