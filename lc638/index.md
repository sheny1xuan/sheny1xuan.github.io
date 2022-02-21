# lc638.大礼包




## [638.大礼包](https://leetcode-cn.com/problems/shopping-offers/)

#### DFS

1. 将每个单独的商品处理成一个礼包
2. 对于每一个礼包有两种选择(好像完全背包问题):直接选择下一个礼包;继续选择这个礼包。
3. $T:O((m+n)*k^{m+n})$，$k$是每个礼包最多选择的次数，$n$是物品的个数，$m$是大礼包的个数，搜索$k^{m+n}$，每次搜索内部需要对$m+n$个大礼包进行对比。$k(10),m(100),n(10),(m+n)*k^{m+n}$感觉过不了，但是题目数据应该比较弱，实际的复杂度只有$O(m+n)*k^n=10^8$

``` cpp
class Solution {
public:
    int ans = INT_MAX;

    // check current have whether satisfy the needs
    bool checkItemsEqual(vector<int>& needs, vector<int>& have) {
        for (int i = 0; i < needs.size(); i++) {
            if(needs[i] != have[i]) {
                return false;
            }
        }

        return true;
    }

    // check current add this special whether more than the needs 
    bool checkItemsMore(vector<int>& needs, vector<int>& have, vector<int>shoppingOffer) {
        for (int i = 0; i < needs.size(); i++) {
            if(have[i] + shoppingOffer[i] > needs[i]) {
                return false;
            }
        }

        return true;
    }

    // inc to have or dec from have
    void add(vector<int>& shoppingOffer, vector<int>& have, bool inc) {
        if(inc) {
            for (int i = 0; i < shoppingOffer.size(); i++) {
                have[i] += shoppingOffer[i]; 
            } 
        } else {
            for (int i = 0; i < shoppingOffer.size(); i++) {
                have[i] -= shoppingOffer[i];
            }
        }
    }
    void dfs(vector<vector<int>>& special, vector<int>& needs, vector<int>& have, int idx) {
        if (idx == special.size()) {
            if (checkItemsEqual(needs, have)) {
                ans = min(have.back(), ans);
            }

            return;
        }
        // don't choose this idx
        dfs(special, needs, have, idx+1);

        // choose this idx
        if (checkItemsMore(needs, have, special[idx])) {
            add(special[idx], have, true);
            dfs(special, needs, have, idx);
            add(special[idx], have, false);
        }
    }
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n = price.size();
        // view a item as a shopping offers.
        for (int i = 0; i < n; i++) {
            vector<int> t(n + 1, 0);
            t[i] = 1;
            t[n] = price[i];
            // add this to shopping offers
            special.push_back(t);
        }
        // current items and prices
        vector<int> have(n + 1, 0);
        dfs(special, needs, have, 0);

        return ans;
    }
};
```




