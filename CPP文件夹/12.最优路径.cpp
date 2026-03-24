#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

int main() {
    int n, m;

    while (cin >> n >> m) {
        vector<vector<int>> grid(n, vector<int>(m));

        // 读取网格
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }

        // dp[i][j] 表示到达(i,j)的最大价值
        vector<vector<long long>> dp(n, vector<long long>(m, LLONG_MIN));

        // 初始化第一行
        for (int j = 0; j < m; j++) {
            dp[0][j] = grid[0][j];
        }

        // 对于每一行
        for (int i = 0; i < n; i++) {
            // 从上到下更新
            if (i > 0) {
                for (int j = 0; j < m; j++) {
                    if (dp[i - 1][j] != LLONG_MIN) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j] + grid[i][j]);
                    }
                }
            }

            // 处理左右移动
            // 创建临时数组存储从左到右和从右到左的最大值
            vector<long long> left(m, LLONG_MIN);
            vector<long long> right(m, LLONG_MIN);

            // 从左到右
            left[0] = dp[i][0];
            for (int j = 1; j < m; j++) {
                if (left[j - 1] != LLONG_MIN) {
                    left[j] = max(dp[i][j], left[j - 1] + grid[i][j]);
                }
                else {
                    left[j] = dp[i][j];
                }
            }

            // 从右到左
            right[m - 1] = dp[i][m - 1];
            for (int j = m - 2; j >= 0; j--) {
                if (right[j + 1] != LLONG_MIN) {
                    right[j] = max(dp[i][j], right[j + 1] + grid[i][j]);
                }
                else {
                    right[j] = dp[i][j];
                }
            }

            // 合并结果
            for (int j = 0; j < m; j++) {
                dp[i][j] = max(left[j], right[j]);
            }
        }

        // 找出最后一行的最大值
        long long max_val = LLONG_MIN;
        for (int j = 0; j < m; j++) {
            max_val = max(max_val, dp[n - 1][j]);
        }

        cout << max_val << endl;
    }

    return 0;
}