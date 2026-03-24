#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

long long evaluate(long long a, long long b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw "Division by zero";
        return a / b;
    default: return 0;
    }
}

int main() {
    string line;

    while (getline(cin, line)) {
        stack<long long> st;
        stringstream ss(line);
        string token;
        bool error = false;

        try {
            while (ss >> token) {
                if (token == "@") {
                    break;
                }
                else if (token == "+" || token == "-" || token == "*" || token == "/") {
                    if (st.size() < 2) {
                        throw "Invalid expression";
                    }
                    long long b = st.top(); st.pop();
                    long long a = st.top(); st.pop();
                    long long result = evaluate(a, b, token[0]);
                    st.push(result);
                }
                else {
                    // 是数字
                    long long num = stoll(token);
                    st.push(num);
                }
            }

            if (st.size() != 1) {
                throw "Invalid expression";
            }

            cout << st.top() << endl;

        }
        catch (const char* msg) {
            if (string(msg) == "Division by zero") {
                cout << "NaN" << endl;
            }
            else {
                cout << "NaN" << endl; // 其他错误也输出NaN
            }
        }
    }

    return 0;
}