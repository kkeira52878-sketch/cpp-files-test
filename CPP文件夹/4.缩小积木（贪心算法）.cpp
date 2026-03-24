#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> H(n);
    for (int i = 0; i < n; i++) {
        cin >> H[i];
    }

    vector<int> T(n, 1);  // 初始所有高度设为1

    // 从左到右扫描
    for (int i = 1; i < n; i++) {
        if (H[i] > H[i - 1]) {
            T[i] = T[i - 1] + 1;
        }
        else if (H[i] == H[i - 1]) {
            T[i] = T[i - 1];
        }
        // H[i] < H[i-1] 的情况保持为1，后面会修正
    }

    // 从右到左扫描，同时修正
    for (int i = n - 2; i >= 0; i--) {
        if (H[i] > H[i + 1]) {
            T[i] = max(T[i], T[i + 1] + 1);
        }
        else if (H[i] == H[i + 1]) {
            T[i] = max(T[i], T[i + 1]);
        }
    }

    // 计算总和
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += T[i];
    }

    cout << sum << endl;

    return 0;
}