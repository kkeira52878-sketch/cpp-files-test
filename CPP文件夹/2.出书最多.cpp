#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main() {
    int n, a;
    cin >> n;
    int count[26] = { 0 };

    vector<pair<int, string>> inputs;

    for (int i = 0; i < n; i++) {
        cin >> a;
        string line;
        getline(cin, line);
        inputs.push_back({ a, line });

        for (char ch : line) {
            if (ch >= 'A' && ch <= 'Z') {
                count[ch - 'A']++;
            }
        }
    }

    int max_index = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > count[max_index]) {
            max_index = i;
        }
    }

    char max_char = 'A' + max_index;
    cout << max_char << endl;

    for (const auto& input : inputs) {
        if (input.second.find(max_char) != string::npos) {
            cout  << input.first <<endl;
        }
    }
    cout << endl;

    return 0;
}