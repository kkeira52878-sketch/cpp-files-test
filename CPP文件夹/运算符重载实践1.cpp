#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char* p;
public:
	MyString(const char* s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;

	}
	~MyString() { if (p) delete[] p; }

    // 1. 拷贝构造函数：处理 MyString s2 = s1;
    MyString(const MyString& ms) {
        if (ms.p) {
            p = new char[strlen(ms.p) + 1];
            strcpy(p, ms.p);
        }
        else {
            p = NULL;
        }
    }

    // 2. 赋值运算符：处理对象间的赋值 s3 = s2;
    MyString& operator=(const MyString& ms) {
        if (this == &ms) return *this; // 防止自赋值
        if (p) delete[] p;             // 释放旧空间
        if (ms.p) {
            p = new char[strlen(ms.p) + 1];
            strcpy(p, ms.p);
        }
        else {
            p = NULL;
        }
        return *this;
    }

    // 3. 赋值运算符：处理字符串赋值 s2 = w2;
    MyString& operator=(const char* s) {
        if (p) delete[] p;
        if (s) {
            p = new char[strlen(s) + 1];
            strcpy(p, s);
        }
        else {
            p = NULL;
        }
        return *this;
    }

    // 4. Copy 成员函数：注意也要防止内存泄漏
    void Copy(const char* s) {
        if (p) delete[] p;
        if (s) {
            p = new char[strlen(s) + 1];
            strcpy(p, s);
        }
        else {
            p = NULL;
        }
    }

    // 5. 重载 <<：使 cout << s1 能够工作
    friend ostream& operator<<(ostream& os, const MyString& ms) {
        if (ms.p) os << ms.p;
        return os;
    }


	// 在此处补充你的代码
};
int main()
{
	char w1[200], w2[100];
	while (cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}