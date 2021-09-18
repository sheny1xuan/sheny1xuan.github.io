# lc36.有效的数独




## [36.有效的数独](https://leetcode-cn.com/problems/valid-sudoku/)

### 暴力遍历

+ 遍历每一行，每一列，每个block进行检查。

``` cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        // row
        for(int i = 0; i < m; i++){
            vector<bool> ok(10, false);
            for(int j = 0; j < n; j++){
                if(board[i][j] == '.'){
                    continue;
                }
                int x = board[i][j] - '0';
                if(ok[x] == false){
                    ok[x] = true;
                }else{
                    return false;
                }
            }
        }


        // cout << "row ok \n";

        // col
        for(int i = 0; i < n; i++){
            vector<bool> ok(10, false);
            for(int j = 0;j < m; j++){
                if(board[j][i] == '.'){
                    continue;
                }
                int x = board[j][i] - '0';
                if(ok[x] == false){
                    ok[x] = true;
                }else{
                    return false;
                }
            }
        }

        // cout << "col ok \n";

        int dir[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1},{1, 0}, {1, 1}, {0, 0}};
        // block
        for(int i = 1; i < m; i += 3){
            for(int j = 1; j < n; j += 3){
                vector<bool> ok(10, false);
                for(int k = 0; k < 9; k++){
                    int ti = i + dir[k][0], tj = j + dir[k][1];
                    if(board[ti][tj] == '.'){
                        continue;
                    }
                    int x = board[ti][tj] - '0';
                    if(ok[x] == false){
                        ok[x] = true;
                    } else{
                        return false;
                    }
                }
            }
        }

        return true;
    }
};
```

### 一次遍历更新所有信息

``` cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // 一次遍历
        int row[9][10];
        int col[9][10];
        int block[3][3][10];

        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(block, 0, sizeof(block));

        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == '.'){
                    continue;
                }

                int x = board[i][j] - '0';
                row[i][x] ++;
                col[j][x] ++;
                block[i/3][j/3][x] ++;
                if(row[i][x] > 1 || col[j][x] > 1 || block[i/3][j/3][x] > 1){
                    return false;
                }
            }
        }

        return true;
    }
};
```


