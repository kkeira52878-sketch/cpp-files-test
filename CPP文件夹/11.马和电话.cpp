#include<iostream>
#include<vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    // 定义马能跳到的位置
    vector<vector<int>> moves = {
        {4, 6},     // 从0可以跳到4,6
        {6, 8},     // 从1可以跳到6,8
        {7, 9},     // 从2可以跳到7,9
        {4, 8},     // 从3可以跳到4,8
        {3, 9, 0},  // 从4可以跳到3,9,0
        {},         // 从5不能跳
        {1, 7, 0},  // 从6可以跳到1,7,0
        {2, 6},     // 从7可以跳到2,6
        {1, 3},     // 从8可以跳到1,3
        {2, 4}      // 从9可以跳到2,4
    };

    // dp[i][j]：走了i步，最后停在数字j的号码数量
    vector<vector<long long>> dp(N + 1, vector<long long>(10, 0));

    // 初始化：第1步，可以从10个数字开始（包括5，但后面用不到）
    for (int j = 0; j <= 9; j++) {
        dp[1][j] = 1;
    }

    // 动态规划
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int next : moves[j]) {
                dp[i][next] += dp[i - 1][j];
            }
        }
    }

    // 计算总数：走了N步，最后停在所有可能位置的总和
    long long total = 0;
    for (int j = 0; j <= 9; j++) {
        total += dp[N][j];
    }

    cout << total << endl;

    return 0;
}