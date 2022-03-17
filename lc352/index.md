# lc352.将数据流变为多个不相交区间




## [352.将数据流变为多个不相交区间](https://leetcode-cn.com/problems/data-stream-as-disjoint-intervals/)

### 有序哈希

+ 可以考虑将一个区间左值作为key，右值作为val进行哈希。
+ 每次加入一个值考虑其最近的两个区间，这里可以考虑第一个左值大于该值的区间`p1={l1,r1}`和最后一个左值小于等于该值的区间`p0={l0,r0}`。
+ p1可以通过`upper_bound()`得到，`p0`可以通过迭代器`prev`得到，这里主要考虑`p1`前面没有元素的情况。
  + `prev(it, n = 1)`获取迭代器的第前n个元素指针，默认n为1
  + `next(it, n = 1)`获取迭代器的第后n个元素指针，默认n为1
+ 考虑一下五种情况
  + `l0<=val<=r0`在`p0`区间内，则加入该值不需要任何操作，直接返回即可。
  + `val == r0 + 1 && val == l1 - 1`，这个时候需要合并两个区间，注意需要提前存储节点值，之后删除结点，合并后的区间为`{l0, r1}`
  + `val == r0 + 1 && val != l1 - 1`，这个时候需要扩展`p0`区间，`p0={l0, val}`
  + `val != r0 + 1 && val == l1 - 1`，这个时候需要扩展`p1`区间，`p1={val, r1}`
  + `val`不满足以上任何一种情况，`{val, val}`单独是一个区间

``` cpp
class SummaryRanges {
public:
    map<int, int> mp;
    SummaryRanges() {

    }
    
    void addNum(int val) {
        // the first one gt val
        auto p1 = mp.upper_bound(val); 
        // the most close left area
        auto p0 = (p1 == mp.begin()) ? mp.end() : prev(p1);

        if(p0 != mp.end() && val >= p0->first && val <= p0->second) {
            // don't do anything
            // 1. [l0, ..., val, ... , r0]
            return;
        }

        bool left = (p0 != mp.end()) && (p0->second == val - 1);
        bool right = (p1 != mp.end()) && (p1->first == val + 1);

        if(left && right) {
            // 2. [l0, ..., val, ..., r1]
            int l = p0->first, r = p1->second;
            mp.erase(p0);
            mp.erase(p1);
            mp.emplace(l, r);
        } else if (right) {
            // 3. [val, ..., r1]
            int r = p1->second;
            mp.erase(p1);
            mp.emplace(val, r);
        } else if (left) {
            // 4. [l0, val] 
            p0->second += 1;
        } else {
            mp.emplace(val, val);
        }
    }
    
    vector<vector<int>> getIntervals() {

        vector<vector<int>> ans;
        for(const auto& [f, s]: mp) {
            ans.push_back({f, s});
        }

        return ans;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
```






