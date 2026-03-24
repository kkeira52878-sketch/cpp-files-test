#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int manacher(string s) {
    // 预处理字符串，插入特殊字符，统一处理奇偶长度回文串
    string t = "#";
    for (char c : s) {
        t += c;
        t += '#';
    }

    int n = t.length();
    vector<int> p(n, 0);  // p[i] 表示以 i 为中心的最长回文半径

    int center = 0;  // 当前扩展的最右回文串的中心
    int right = 0;   // 当前扩展的最右回文串的右边界
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        // 利用对称性快速初始化 p[i]
        if (i < right) {
            int mirror = 2 * center - i;
            p[i] = min(right - i, p[mirror]);
        }

        // 尝试扩展
        int left = i - (1 + p[i]);
        int r = i + (1 + p[i]);
        while (left >= 0 && r < n && t[left] == t[r]) {
            p[i]++;
            left--;
            r++;
        }

        // 如果扩展后超过了当前最右边界，更新中心点和边界
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        // 更新最大长度
        max_len = max(max_len, p[i]);
    }

    return max_len;  // max_len 就是最长回文子串的长度（预处理后的半径对应原串长度）
}

int main() {
    string s;
    cin >> s;
    cout << manacher(s) << endl;
    return 0;
}