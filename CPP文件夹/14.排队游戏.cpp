#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
void pai(vector<int>& a, vector<pair<int, int>>&pairs) {
	int count = 0;
	for (int i = 0;i < a.size();i++) {
		if (a[i] != 0)break;
		else count++;
	}
	if (count == a.size())return;
	for (int i = 0;i < a.size() - 1;i++) {
		if (a[i] == 1) {
			for (int j = i;j < a.size();j++) {
					if (a[j] == 2) {
						if (j == i + 1) {
						cas:
							pairs.push_back({ i,j });
							a[i] = a[j] = 0;
						goo:
							break;
						}
						for (int m = i+1;m < j;m++) {
							if (a[m] != 0)goto goo;
						}
						goto cas;
				}
			}
		}
	}
	pai(a, pairs);
}
int main() {
	string line;
	getline(cin, line);
	vector<int>a(line.length());
	for (int i = 0;i < line.length();i++) {
		if (line[i] == line[0])a[i] = 1;
		else a[i] = 2;
	}
	vector<pair<int, int>>pairs;
	pai(a, pairs);
	sort(pairs.begin(), pairs.end(),
		[](const auto& a, const auto& b) {
			return a.second < b.second;
		}
	);
	for (int i = 0;i < a.size() / 2;i++) {
		cout << pairs[i].first << " " << pairs[i].second << endl;
	}
	return 0;
}