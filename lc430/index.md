#  .扁平化多级双向链表




## [430.扁平化多级双向链表](https://leetcode-cn.com/problems/flatten-a-multilevel-doubly-linked-list/)

### 迭代

+ 没碰到一个有`child`部分的节点，找到当前节点儿子链表的尾结点`tail`，将该链表添加到当前链表中，当前节点的`child`结点置空。

``` cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* get_tail(Node* head){
        while(head != nullptr && head->next != nullptr){
            head = head->next;
        }

        return head;
    }
    Node* flatten(Node* head) {
        Node* cur = head;
        while(cur){
            if(cur->child == nullptr){
                cur = cur->next;
                continue;
            }

            Node* child_tail = get_tail(cur->child);
            
            child_tail->next = cur->next;
            if(child_tail->next){
                child_tail->next->prev = child_tail;
            }
            cur->next = cur->child;
            cur->child->prev = cur;
            cur->child = nullptr;
        }

        return head;
    }
};
```



### 递归实现

+ 递归返回儿子结点的尾结点，然后将子链表添加到原链表上。

``` cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        flatten_help(head);

        return head;
    }
    Node* flatten_help(Node* head) {
        Node* cur = head;
        Node* last = head;
        while(cur != nullptr){
            last = cur;
            if(cur->child == nullptr){
                cur = cur -> next;
                continue;
            }

            Node* child_end = flatten_help(cur->child);
            // cout << child_end->val << endl;
            child_end->next = cur->next;
            if(child_end->next){
                child_end->next->prev = child_end;
            }else{
                child_end->next = nullptr;
            }
            cur->next = cur->child;
            cur->child->prev = cur;
            cur->child = nullptr;
        }

        // cout << last->val << endl;
        return last; 
    }
};
```

#### cpp匿名函数实现递归的方法

+ cpp匿名函数就是一个自动变量，因此在代码块内并不能找到该函数的地址，因此需要在递归函数中传入该匿名函数的地址，才能正确的递归调用,`auto f = [](auto& f, Node* head)->Node*{ };`

``` cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        flatten_help(head);

        return head;
    }
    Node* flatten_help(Node* head) {
        Node* cur = head;
        Node* last = head;
        while(cur != nullptr){
            last = cur;
            if(cur->child == nullptr){
                cur = cur -> next;
                continue;
            }

            Node* child_end = flatten_help(cur->child);
            // cout << child_end->val << endl;
            child_end->next = cur->next;
            if(child_end->next){
                child_end->next->prev = child_end;
            }else{
                child_end->next = nullptr;
            }
            cur->next = cur->child;
            cur->child->prev = cur;
            cur->child = nullptr;
        }

        // cout << last->val << endl;
        return last; 
    }
};
```


