#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110;
class CHugeInt {
private:
    char digits[MAX];  
    int len;          
    void reverse(char* s) {
        int l = 0, r = strlen(s) - 1;
        while (l < r) {
            swap(s[l], s[r]);
            l++; r--;
        }
    }

    void trim() {
        while (len > 1 && digits[len - 1] == '0') {
            len--;
        }
        digits[len] = '\0';
    }

public:

    CHugeInt(const char* s) {
        len = strlen(s);
    
        for (int i = 0; i < len; i++) {
            digits[i] = s[len - 1 - i];
        }
        digits[len] = '\0';
        trim();
    }


    CHugeInt(int n) {
        if (n == 0) {
            digits[0] = '0';
            len = 1;
            digits[1] = '\0';
            return;
        }

        len = 0;
        while (n > 0) {
            digits[len++] = (n % 10) + '0';
            n /= 10;
        }
        digits[len] = '\0';
    }


    CHugeInt() {
        digits[0] = '0';
        len = 1;
        digits[1] = '\0';
    }


    friend CHugeInt operator+(const CHugeInt& a, const CHugeInt& b) {
        CHugeInt result;
        int carry = 0;
        int i = 0;
        int maxLen = max(a.len, b.len);

        result.len = 0;
        for (i = 0; i < maxLen || carry; i++) {
            int sum = carry;
            if (i < a.len) sum += (a.digits[i] - '0');
            if (i < b.len) sum += (b.digits[i] - '0');

            result.digits[i] = (sum % 10) + '0';
            carry = sum / 10;
        }
        result.len = i;
        result.digits[result.len] = '\0';
        result.trim();
        return result;
    }


    CHugeInt& operator+=(int n) {
        CHugeInt temp(n);
        *this = *this + temp;
        return *this;
    }


    CHugeInt& operator++() {
        *this = *this + CHugeInt(1);
        return *this;
    }

    CHugeInt operator++(int) {
        CHugeInt temp = *this;
        *this = *this + CHugeInt(1);
        return temp;
    }


    friend ostream& operator<<(ostream& os, const CHugeInt& num) {
        for (int i = num.len - 1; i >= 0; i--) {
            os << num.digits[i];
        }
        return os;
    }

    friend CHugeInt operator+(int n, const CHugeInt& a) {
        return CHugeInt(n) + a;
    }
};
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}