

#include <iostream>
#include <cstring>
    using namespace std;

    class Array2 {
    private:
        int rows;      // 改为有意义的命名
        int cols;
        int* data;

    public:
        // 构造函数
        Array2(int i = 0, int j = 0) : rows(i), cols(j) {
            if (rows > 0 && cols > 0) {
                data = new int[rows * cols]();  // 初始化为0
            }
            else {
                data = nullptr;
            }
        }

        // 拷贝构造函数（必须添加）
        Array2(const Array2& other) : rows(other.rows), cols(other.cols) {
            if (rows > 0 && cols > 0) {
                data = new int[rows * cols];
                memcpy(data, other.data, rows * cols * sizeof(int));
            }
            else {
                data = nullptr;
            }
        }

        // 赋值运算符（修正）
        Array2& operator=(const Array2& other) {
            if (this != &other) {  // 自赋值检查
                // 释放原有内存
                delete[] data;

                // 复制新数据
                rows = other.rows;
                cols = other.cols;
                if (rows > 0 && cols > 0) {
                    data = new int[rows * cols];
                    memcpy(data, other.data, rows * cols * sizeof(int));
                }
                else {
                    data = nullptr;
                }
            }
            return *this;
        }

        // 析构函数
        ~Array2() {
            delete[] data;
        }

        // 代理类：支持 a[i][j]
        class RowProxy {
        private:
            int* rowData;  // 当前行的数据指针
            int cols;      // 列数

        public:
            RowProxy(int* data, int c) : rowData(data), cols(c) {}

            // 重载 [] 访问列元素
            int& operator[](int col) {
                return rowData[col];
            }

            const int& operator[](int col) const {
                return rowData[col];
            }
        };

        // 重载 [] 返回代理对象，支持 a[i][j]
        RowProxy operator[](int row) {
            return RowProxy(data + row * cols, cols);
        }

        // const 版本
        const RowProxy operator[](int row) const {
            return RowProxy(data + row * cols, cols);
        }

        // 重载 () 支持 a(i,j)
        int& operator()(int row, int col) {
            return data[row * cols + col];
        }

        const int& operator()(int row, int col) const {
            return data[row * cols + col];
        }



    };

    int main() {
        Array2 a(3, 4);
        int i, j;
        for (i = 0; i < 3; ++i)
            for (j = 0; j < 4; j++)
                a[i][j] = i * 4 + j;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 4; j++) {
                cout << a(i, j) << ",";
            }
            cout << endl;
        }
        cout << "next" << endl;
        Array2 b;     b = a;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 4; j++) {
                cout << b[i][j] << ",";
            }
            cout << endl;
        }
        return 0;
    }