# lc725.分隔链表




## [725.分隔链表](https://leetcode-cn.com/problems/split-linked-list-in-parts/)

+ 计算每一部分的长度之后，每次数出指定长度的结点即可。

``` cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    int get_list_length(ListNode* head){
        int ans = 0;
        while(head){
            ans += 1;
            head = head->next;
        }
        return ans;
    }
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int len = get_list_length(head);

        vector<ListNode*> ans(k);

        int base = len / k, offset = len % k;
        ListNode* cur = head;
        
        for(int i = 0; i < k && cur != nullptr; i++){
            ans[i] = cur;
            int target = base;

            if(offset > 0){
                target += 1;
                offset -= 1;
            }            

            for(int j = 1; j < target; j++){
                cur = cur->next;
            }

            ListNode* ne = cur->next;
            cur->next = nullptr;
            cur = ne;
        }

        return ans;
    }
};
```


