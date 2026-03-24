#include <iostream>
#include<vector>

using namespace std;
void move(vector<int>&a,int n) {
	int temp = a[n - 1];
	for (int i = n-2;i>=0;i--) {
		a[i] = a[i + 1];
	}
	a[0] = temp;
}
void remove(vector<int>& a, int n) {
	int temp = a[0];
	for (int i = n - 2;i >= 0;i--) {
		a[i+1] = a[i ];
	}
	a[n-1] = temp;
}
void roll(int m, vector<vector<int>>&a,int n, int& min) {
	if (m == 0) {
		int sum = 0;int temp = 0;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				sum += a[j][i];
			}
			if (sum > temp) {
				temp = sum;
			}
			sum = 0;
		}
		if (min > temp) {
			min = temp;
		}
		return;
	}
	for (int i = 1;i <= n ;i++) {
		move(a[n - m], n);
		roll(m - 1, a, n, min);
		remove(a[n - m], n);
	}
}
int main() {
	int n;
	while (cin >> n && n != -1) {
		vector<vector<int>>a(n,vector<int>(n));
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				cin >> a[i][j];
			}
		}
		int min = 99999999999;
		int sum = 0;int temp = 0;
		for (int i = 0;i < n;i++) {
			for (int j = 0;j < n;j++) {
				sum += a[j][i];
			}
			if (sum > temp) {
				temp = sum;
			}
			sum = 0;
		}
		if (min > temp) {
			min = temp;
		}
		roll(n, a, n, min);
		cout << min << endl;
	}
	return 0;
}





#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// 向右循环移动k次（修正版）
void rotateRight(vector<int>& arr, int k) {
	int n = arr.size();
	k = k % n;
	if (k == 0) return;

	vector<int> temp(k);
	// 保存最后k个元素
	for (int i = 0; i < k; i++) {
		temp[i] = arr[n - k + i];
	}
	// 移动前面的元素
	for (int i = n - 1; i >= k; i--) {
		arr[i] = arr[i - k];
	}
	// 放置保存的元素
	for (int i = 0; i < k; i++) {
		arr[i] = temp[i];
	}
}

void roll(int currentRow, vector<vector<int>>& matrix, int n, int& minSum) {
	if (currentRow == n) {
		// 计算当前配置的最大列和
		int maxColSum = 0;
		for (int col = 0; col < n; col++) {
			int colSum = 0;
			for (int row = 0; row < n; row++) {
				colSum += matrix[row][col];
			}
			if (colSum > maxColSum) {
				maxColSum = colSum;
			}
		}

		if (maxColSum < minSum) {
			minSum = maxColSum;
		}
		return;
	}

	// 尝试当前行的所有旋转可能
	for (int rotation = 0; rotation < n; rotation++) {
		rotateRight(matrix[currentRow], 1);  // 每次旋转1位
		roll(currentRow + 1, matrix, n, minSum);
	}
	// 回溯：旋转n次后回到原始状态
	rotateRight(matrix[currentRow], 1);
}

int main() {
	int n;
	while (cin >> n && n != -1) {
		vector<vector<int>> matrix(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> matrix[i][j];
			}
		}

		int minSum = INT_MAX;
		roll(0, matrix, n, minSum);
		cout << minSum << endl;
	}
	return 0;
}