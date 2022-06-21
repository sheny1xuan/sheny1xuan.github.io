#include <iostream>
#include <vector>

using namespace std;

int KMP(string haystack, string needle) {
    int n = haystack.size(), m = needle.size();

    if (m == 0) {
        return 0;
    }

    vector<int> ne(m);
    // ne[i] -> 前缀与第i位为结尾的后缀匹配的长度
    // ababa -> ne = [0, 0, 1, ,2, 3]
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && needle[i] != needle[j]) {
            j = ne[j - 1];
        }
        if (needle[i] == needle[j]) {
            j++;
        }
        ne[i] = j;
    }

    // s:deabcababa
    // p:ababa
    // i < 2 : (j = 0, i += 1)
    // s:deabacababa
    // p:  ababa
    // i < 5 : (i += 1, j += 1)
    // i == 5, j = 4: (j = ne[j - 1] = 2)
    // s:deabacababa
    // p:    ababa
    // i == 5, j = 2 (j = ne[j - 1] = 0)
    // s:deabacababa
    // p:      ababa
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = ne[j - 1];
        }
        // if j == 0 && haystack[i] != needle[j]
        // i += 1从头进行匹配
        if (haystack[i] == needle[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1;
        }
    }
    return -1;
}

int main() {
    KMP("abc", "ababa");
}
