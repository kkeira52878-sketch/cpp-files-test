#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
using namespace std;
double my_atof(const string& s) {
    double num = 0.0;
    int sign = 1;
    int exp_sign = 1;
    int exponent = 0;
    bool after_decimal = false;
    bool after_exp = false;
    double decimal_divisor = 1.0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        // 处理正负号
        if (i == 0) {
            if (c == '+') continue;
            if (c == '-') {
                sign = -1;
                continue;
            }
        }
        // 遇到指数分隔符
        if (!after_exp && (c < '0' || c > '9') && c != '.') {
            after_exp = true;
            // 检查指数符号
            if (i + 1 < s.length()) {
                if (s[i + 1] == '-') {
                    exp_sign = -1;
                    i++;  // 跳过负号
                }
                else if (s[i + 1] == '+') {
                    i++;  // 跳过正号
                }
            }
            continue;
        }
        if (!after_exp) {
            // 主体部分
            if (c == '.') {
                after_decimal = true;
            }
            else if (c >= '0' && c <= '9') {
                if (!after_decimal) {
                    num = num * 10 + (c - '0');
                }
                else {
                    num += (c - '0') / (decimal_divisor * 10);
                    decimal_divisor *= 10;
                }
            }
        }
        else {
            // 指数部分
            if (c >= '0' && c <= '9') {
                exponent = exponent * 10 + (c - '0');
            }
        }
    }
    double result = sign * num;
    if (exponent > 0) {
        if (exp_sign == 1) {
            result *= pow(10.0, exponent);
        }
        else {
            result /= pow(10.0, exponent);
        }
    }
    return result;
}
int main() {
    string s;
    while (cin >> s) {
        if (s == "q") break;
        double result = my_atof(s);
        cout << fixed << setprecision(6) << result << endl;
    }
    return 0;
}