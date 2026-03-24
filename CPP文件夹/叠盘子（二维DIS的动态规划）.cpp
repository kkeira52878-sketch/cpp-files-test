#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Plate {
    int w, h;
};
int main() {
    int n;
    vector<Plate> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].w >> p[i].h;
    }
    // 1. 排序：按宽度 w 升序排列；若宽度相同，按高度 h 降序排列
    // 降序排列的原因：宽度相同时不能互叠，降序可以确保 LIS 逻辑只选其中一个
    sort(p.begin(), p.end(), [](const Plate& a, const Plate& b) {
        if (a.w != b.w) return a.w < b.w;
        return a.h > b.h;
        });
    // 2. 对高度 h 求 LIS (动态规划)
    vector<int> dp(n, 1);
    int max_layers = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // 如果前面的盘子 j 的宽和高都小于当前盘子 i
            // 注意：因为排序了且宽度相同时高度降序，这里只需简单判断 h 即可
            if (p[j].w < p[i].w && p[j].h < p[i].h) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_layers = max(max_layers, dp[i]);
    }
    cout << max_layers << endl;
    return 0;
}