#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<windows.h>
#include<vector>
#include<cmath>
#include<string>
#include<sstream>
using namespace std;

const char blank = ' ';
char grid[8][8];

void setcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetcolor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}//清屏
class Board {
public:
	void menu() {
		cout << "欢迎游玩亚马逊棋！" << endl << "请选择：" << endl;
		cout << "1：新游戏" << endl << "2：存盘(游戏中才能存盘)" << endl << "3：读盘" << endl << "4：退出";
		cout <<endl<< "请输入选择（1-4）：";
	}
	void start() {
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				grid[i][j] = blank;
			}
		}
		grid[0][2] = 'W';
		grid[2][0] = 'W';
		grid[5][0] = 'W';
		grid[7][2] = 'W';
		grid[0][5] = 'B';
		grid[2][7] = 'B';
		grid[5][7] = 'B';
		grid[7][5] = 'B';
	}
	void run() {
		clear();
		cout << "    a  b  c  d  e  f  g  h " << '\n';
		for (int i = 0;i < 8;i++) {
			cout << " " << i << " ";
			for (int j = 0;j < 8;j++) {
				bool white = ((i + j) % 2 == 0);
				if (white)setcolor(240);
				else setcolor(8);
				cout << " " << grid[i][j] << " ";
			}
			resetcolor();
			cout << " " << i << " ";
			cout << endl;
		}
		cout << "    a  b  c  d  e  f  g  h " << '\n';
		cout << "输入menu以退出到主菜单" << endl;
	}

};//初始化和输出某一状态的棋盘
class Rule {
public:

	bool valid(int i, int j) {
		return (i >= 0 && i <= 7 && j >= 0 && j <= 7);
	}
	bool good(int i, int j, int a, int b) {
		if ((a == i && b == j) || !valid(a, b) || !valid(i, j))return 0;
		if (i == a || j == b || abs(i - a) == abs(j - b))return 1;
		return 0;
	}
	bool barrier(int i, int j, int a, int b, int n) {
		if (grid[i][j] != blank && n != 0 && n != abs(i - a))return 0;
		if (i == a && j == b)return 1;
		n++;
		if (j == b) {
			if (i > a) {
				return barrier(--i, j, a, b, n);
			}
			else  return barrier(++i, j, a, b, n);
		}
		if (i == a) {
			if (j > b) {
				return barrier(i, --j, a, b, n);
			}
			else  return barrier(i, ++j, a, b, n);
		}
		else {
			if (i > a) {
				return barrier(--i, --j, a, b, n);
			}
			else  return barrier(++i, ++j, a, b, n);
		}
	}
	bool move_valid(int i, int j, int a, int b) {
		if (good(i, j, a, b)) {
			if (barrier(i, j, a, b, 0)) {
				return 1;
			}
		}
		else return 0;
	}
};//判定是否可以移动
class Over {
private:
	Rule rule;
public:
	bool die_chess(int a, int b) {
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				if (rule.move_valid(a, b, i, j))return 0;
			}
		}
		return 1;
	}
	bool game_endW() {
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				if (grid[i][j] == 'W') {
					if (die_chess(i, j))continue;
					else return 0;
				}
			}
		}
		return 1;
	}
	bool game_endB() {
		for (int i = 0;i < 8;i++) {
			for (int j = 0;j < 8;j++) {
				if (grid[i][j] == 'B') {
					if (die_chess(i, j))continue;
					else return 0;
				}
			}
		}
		return 1;
	}
};//游戏结束判定
class Game {
private:
	Board board;
	Rule rule;
	Over over;
public:
	Game() {
	start:
		clear();
		board.menu();
		string input;
		getline(cin, input);
		stringstream ss(input);
		bool game_running = false;
		if (input == "menu") {
			cout << "已经在主菜单！" << endl;
			goto start;
		}
		int n;
		if (!(ss >> n)) {
			cout << "输入无效！请输入1-4：";
			goto start;
		}
		if (n == 1) {
			game_running = true;
			board.start();
		gaming:
			while (!over.game_endW() && !over.game_endB()) {
				string line1;
				getline(cin, line1);
				int a1 = 0;char ch1 = 0;
				stringstream ss1(line1);
				if (line1 == "menu") {
					goto start;
				}
				clear();
				board.run();
				if (!(ss1 >> ch1 >> a1)) {
					cout << "格式错误！请按照 字母数字 格式输入:" << endl;
					continue;
				}
				int a2 = 0;char ch2 = 0;int a3 = 0;char ch3 = 0;char temp = 0;
				if (!rule.valid(a1, ch1 - 'a') || grid[a1][ch1 - 'a'] != 'W') {
					cout << "起始位置不合法！" << endl;
					continue;
				}
				else {
					string line2;
					getline(cin, line2);
					stringstream ss2(line2);
					if (line2 == "menu") {
						goto start;
					}
					if (!(ss2 >> ch2 >> a2)) {
						cout << "格式错误！请按照 字母数字 格式输入:" << endl;
						continue;
					}
					if (rule.move_valid(a1, ch1 - 'a', a2, ch2 - 'a')) {
						temp = grid[a1][ch1 - 'a'];
						grid[a1][ch1 - 'a'] = blank;
						grid[a2][ch2 - 'a'] = temp;
					}
					else {
						cout << "移动不合法！";
						continue;
					}
					string line3;
					getline(cin, line3);
					stringstream ss3(line3);
					if (line3 == "menu") {
						// 回退移动
						grid[a1][ch1-'a'] = temp;
						grid[a2][ch2-'a'] = blank;
						goto start;
					}
					if (!(ss3 >> ch3 >> a3)) {
						cout << "格式错误！回退移动。" << endl;
						grid[a1][ch1-'a'] = temp;
						grid[a2][ch2-'a'] = blank;
						continue;
					}
					if (rule.move_valid(a2, ch2 - 'a', a3, ch3 - 'a')) {
						grid[a3][ch3 - 'a'] = 'X';
					}
					else {
						cout << "射箭位置不合法！";
						continue;
					}
				}
			}
			if (over.game_endW())cout << endl << "白方胜利！";
			if (over.game_endB())cout << endl << "黑方胜利！";
		}
		if (n == 2) {
			if (!game_running) {
				cout << "游戏中才能存盘";
				goto start;
			}
			else goto start;
		}
		if (n == 3) {
			goto gaming;
		}
		if (n == 4) {
			return;
		}
	}
};//运行
int main() {

	Game game;

	return 0;
}
