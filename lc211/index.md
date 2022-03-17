# lc211.添加与搜索单词 - 数据结构设计




## [211.添加与搜索单词 - 数据结构设计](https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/)

### Trie的通配符匹配

+ 需要新建一个`TrieNode`表示`Trie`树的结点。
+ 对于通配符`.`需要遍历所有的子树，所以普通的搜索方法不再适用，需要适用`DFS/BFS`遍历所有的子节点。
+ 后续遍历释放每一个结点的内存

``` cpp
struct trierNode {
    trierNode* child[26];
    bool isEnd;
    trierNode() {
        for(int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
        isEnd = false;
    }
};

class trier {
    public:
        trierNode* root;
    public:
        trier() {
            root = new trierNode;
        }
        ~trier() {
            // 后续遍历析构
            delhelp(root);
        }
        void addWord(string word) {
            trierNode* cur = root;
            for(auto& c: word) {
                if(cur->child[c - 'a'] == nullptr) {
                    cur->child[c - 'a'] = new trierNode;
                }
                cur = cur->child[c - 'a'];
            }
            cur->isEnd = true;
        }

        bool search(string word) {
            trierNode* cur = root;
            return dfs(cur, word, 0);
        }
    private:
        bool dfs(trierNode* node, string& word, int idx) {
            if(node == nullptr) {
                return false;
            }
            if(idx >= word.size()) {
                return node->isEnd;
            }

            if(word[idx] == '.') {
                for(int i = 0; i < 26; i++) {
                    if(dfs(node->child[i], word, idx + 1)) {
                        return true;
                    }
                }
            } else {
                return dfs(node->child[word[idx] - 'a'], word, idx + 1);
            }

            return false;
        }

        void delhelp(trierNode* node) {
            if(node == nullptr) {
                return;
            }
            for(int i = 0; i < 26; i++) {
                delhelp(node->child[i]);
            }
            delete node; 
        }
};

class WordDictionary {
public:
    trier* mt;
    WordDictionary() {
        mt = new trier;
    }
    ~WordDictionary() {
        delete mt;
    }
    
    void addWord(string word) {
        mt->addWord(word);
    }
    
    bool search(string word) {
        return mt->search(word);
    }

};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
```


