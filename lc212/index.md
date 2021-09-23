# lc212.单词搜索 II




## [212.单词搜索 II](https://leetcode-cn.com/problems/word-search-ii/)

### 字典树+dfs

+ 首先将目标单词依次插入到字典树当中，方便dfs时进行查询
+ 对所有起点进行dfs，如果当前字符与字典树匹配，继续搜索，否则停止搜索。
  + 注意：因为同一个单词中一个位置只允许出现一次，所有需要先用#进行标记，使用完后回复现场。
+ $T:O(m*n*3^{l-1})$，$m$是网格的长度，$n$是网格的宽度，$l$指的是单词的最长长度，要搜索$m*n$个网格点，每个网格搜索3个方向，每个方向搜索长度为$l-1$
+ $S:O(k*l)$，k是待搜索字符串的个数，l是字符串的最长的长度

``` cpp
struct Trie_Node{
    unordered_map<char, Trie_Node*> children;
    string word;
    Trie_Node(){
        this->word = "";
    }
};

void Insert_Trie(Trie_Node* root, string& s){
    for(auto& c: s){
        if(root->children.count(c) == 0){
            root->children[c] = new Trie_Node();
        }
        root = root->children[c];
    }
    root->word = s;
}

class Solution {
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    void dfs(vector<vector<char>>& board, Trie_Node* root, int x, int y, set<string>& ans, int len){
        if(len > 10){
            return;
        }

        char ch = board[x][y];

        if(root->children.count(ch) == 0){
            return;
        }
        
        root = root->children[ch];
        if(root->word != ""){
            ans.insert(root->word);
        }

        // 同一个单词内不允许访问两次，进行标记
        board[x][y] = '#';
        for(int i = 0; i < 4; i++){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if(tx >= 0 && tx < board.size() && ty >= 0 && ty < board[0].size()){
                if(board[tx][ty] != '#')
                    dfs(board, root, tx, ty, ans, len + 1);
            }
        }
        board[x][y] = ch;

    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie_Node* root = new Trie_Node();
        vector<string> res;
        set<string> ans;

        // 把所有需要查询的结点加入到字典树当中
        for(auto& word: words){
            Insert_Trie(root, word);
        }

        // 遍历网格查找是否有合适的单词 
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                dfs(board, root, i, j, ans, 0);
            }
        }

        for(auto& word: ans){
            res.push_back(word);        
        }
        
        return res;
    }
};
```




