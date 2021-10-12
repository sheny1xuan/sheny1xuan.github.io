# lc68. 文本左右对齐




## [68. 文本左右对齐](https://leetcode-cn.com/problems/text-justification/)

+ 首先理解题目：这道题要求除了最后一行两端对齐，最后一行靠左对齐。
+ 首先先计算每一行可以放哪些单词
+ 之后将计算每行放多少空格，额外需要添加多少空格，最后一个单词空格不足的话，需要额外补足。
+ 最后对最后一行进行从左到右处理。
+ $T:O(n)$,$n$为单词的数目

``` cpp
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        vector<vector<string>> lines;   // 每一行可以放哪些单词
        
        int length = 0;
        vector<string> line;
        for(auto& word: words){

            if(length + word.size() > maxWidth){
                lines.push_back(line);
                line.clear();
                length = 0;
            }

            line.push_back(word);
            length += word.size();
            // 添加新的单词前，需要至少添加一个空格
            length++;
        }

        if(!line.empty()){
            lines.push_back(line);
        }

        string line_string;

        // 依次处理每一行
        for(int i = 0; i < lines.size() - 1; i++){
            int total_length = 0;
            auto cur = lines[i];
            for(int j = 0; j < cur.size(); j++){
                total_length += cur[j].size();
            }

            // 计算每一行平均需要添加的空格数
            // 已经左边每个空格额外需要的空个数
            int n_words = cur.size() - 1;
            int n_space = 0, extra_space = 0;
            if(n_words != 0){
                n_space = (maxWidth - total_length) / n_words;
                extra_space = (maxWidth - total_length) % n_words;
            }

            for(int j = 0; j < cur.size(); j++){
                if(j < cur.size() - 1){
                    line_string += cur[j];
                    line_string += string(n_space, ' ');
                    if(extra_space > 0){
                        line_string += string(1, ' ');
                        extra_space -= 1;
                    } 
                }else{
                    line_string += cur[j];
                }
            }

            // 如果右侧有剩余部分，添加额外空格
            int n_empty = maxWidth - line_string.size();
            if(n_empty > 0) line_string += string(n_empty, ' ');
            res.push_back(line_string);
            line_string.clear();
        }
        
        if(lines.size() - 1 >= 0){    // 处理最后一行
            auto line = lines[lines.size() - 1];
            for(int i = 0; i < line.size(); i++){
                if(i < line.size() - 1){
                    line_string += line[i];
                    line_string += string(1, ' ');
                }else{
                    line_string += line[i];
                }
            }

            int n_empty = maxWidth - line_string.size();
            if(n_empty > 0) line_string += string(n_empty, ' ');

            res.push_back(line_string);
        }

        return res;
    }
};
```


