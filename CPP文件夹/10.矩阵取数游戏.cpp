#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 计算一行的最大得分
long long solveRow(vector<int>& row, int m) {
    vector<vector<long long>> dp(m, vector<long long>(m, 0));

    // 区间DP
    for (int len = 1; len <= m; len++) {
        for (int i = 0; i + len - 1 < m; i++) {
            int j = i + len - 1;
            int times = m - len + 1;  // 第几次取数

            if (len == 1) {
                dp[i][j] = row[i] * times;
            }
            else {
                dp[i][j] = max(
                    dp[i + 1][j] + row[i] * times,  // 取左端
                    dp[i][j - 1] + row[j] * times   // 取右端
                );
            }
        }
    }

    return dp[0][m - 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    long long totalScore = 0;
    for (int i = 0; i < n; i++) {
        totalScore += solveRow(matrix[i], m);
    }

    cout << totalScore << endl;
    return 0;
}




#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    long long total_score = 0;

    // 对每一行单独处理
    for (int row = 0; row < n; row++) {
        // dp[i][j] 表示从第i个元素到第j个元素区间内的最大得分
        vector<vector<long long>> dp(m, vector<long long>(m, 0));

        // 初始化：区间长度为1的情况
        for (int i = 0; i < m; i++) {
            dp[i][i] = matrix[row][i] * m; // 最后一次取数，乘以m
        }

        // 区间DP：按区间长度从小到大计算
        for (int len = 2; len <= m; len++) {
            for (int i = 0; i + len - 1 < m; i++) {
                int j = i + len - 1;
                // 当前区间长度对应的取数次数
                int step = m - len + 1;

                // 两种选择：取左边的数或者取右边的数
                long long take_left = matrix[row][i] * step + dp[i + 1][j];
                long long take_right = matrix[row][j] * step + dp[i][j - 1];

                dp[i][j] = max(take_left, take_right);
            }
        }

        total_score += dp[0][m - 1];
    }

    cout << total_score << endl;

    return 0;
}