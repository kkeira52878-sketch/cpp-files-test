#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, mod;
    cin >> n >> k >> mod;

    int N = 2 * n;
    vector<vector<ll>> B(N, vector<ll>(N, 0));

    // 读取矩阵 A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll val;
            cin >> val;
            B[i][j] = val % mod;           // 左上角: A
            B[i][j + n] = val % mod;       // 右上角: A
        }
        B[n + i][n + i] = 1;               // 右下角: I
    }

    // 矩阵快速幂计算 B^k
    vector<vector<ll>> result(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++) result[i][i] = 1;

    while (k > 0) {
        if (k & 1) {
            // result = result * B
            vector<vector<ll>> temp(N, vector<ll>(N, 0));
            for (int i = 0; i < N; i++) {
                for (int p = 0; p < N; p++) {
                    if (result[i][p] == 0) continue;
                    for (int j = 0; j < N; j++) {
                        temp[i][j] = (temp[i][j] + result[i][p] * B[p][j]) % mod;
                    }
                }
            }
            result = temp;
        }

        // B = B * B
        vector<vector<ll>> temp(N, vector<ll>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int p = 0; p < N; p++) {
                if (B[i][p] == 0) continue;
                for (int j = 0; j < N; j++) {
                    temp[i][j] = (temp[i][j] + B[i][p] * B[p][j]) % mod;
                }
            }
        }
        B = temp;

        k >>= 1;
    }

    // 输出右上角的 n×n 子矩阵（A + A^2 + ... + A^k）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) cout << " ";
            cout << result[i][j + n];
        }
        cout << '\n';
    }

    return 0;
}