#include<iostream>
#include<vector>
#include<utility>
using namespace std;
void find(vector<vector<int>>&a, int n) {
	int max=0;
	vector<pair <int, vector<vector<int>>>>e;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			for (int k = i;k < n;k++) {
				for (int l = j;l < n;l++) {
					int sum = 0;
					for (int c = i;c <= k;c++) {
						for (int d = j;d <= l;d++) {
							sum += a[c][d];
						}
					}
					if (max < sum) {
						max = sum;
						vector<vector<int>>b(k - i + 1, vector<int>(l - j + 1));
						for (int c = i;c <= k;c++) {
							for (int d = j;d <= l;d++) {
								b[c - i][d - j] = a[c][d];
							}
						}
						pair <int, vector<vector<int>>>p1 = { sum,b };
						e.push_back(p1);
					}
				}
			}
		}
	}
	int max_cols = 0;
	for (const auto& row : e.back().second) {
		if (row.size() > max_cols) {
			max_cols = row.size();
		}
	}
	
	for (int i = 0;i <e.back().second.size();i++) {
		bool first = 1;
		for (int j = 0;j < max_cols;j++) {
			if (first)first = 0;
			else cout << " ";
			cout << e.back().second[i][j] ;
		}
		cout << endl;
	}
	cout << e.back(). first<<endl;
}
int main() {
	int n;
	cin >> n;
	vector<vector<int>>a(n, vector<int>(n));
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			cin >> a[i][j];
		}
	}
	find(a, n);
	return 0;
}