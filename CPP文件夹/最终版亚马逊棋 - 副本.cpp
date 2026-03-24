#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<windows.h>
#include<vector>
#include<cmath>
#include<string>
#include<sstream>
#include<climits>
#include<utility>
#include<fstream>
using namespace std;
const char blank = ' ';
char grid[8][8];
char grid_backup[8][8] = { 0 };
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
}
class Board {
public:
	void menu() {
		cout << "欢迎游玩亚马逊棋！" << endl << "请选择：" << endl;
		cout << "1：新游戏" << endl << "2：存盘(游戏中才能退出到主菜单存盘)" << endl << "3：继续游戏" << endl << "4：读盘" << endl << "5：退出";
		cout << endl << "请输入选择（1-5）：";
	}
	void start() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				grid[i][j] = blank;
			}
		}
		grid[0][2] = 'B';
		grid[2][0] = 'B';
		grid[5][0] = 'W';
		grid[7][2] = 'W';
		grid[0][5] = 'B';
		grid[2][7] = 'B';
		grid[5][7] = 'W';
		grid[7][5] = 'W';
	}
	void run() {
		clear();
		cout << "    a  b  c  d  e  f  g  h " << '\n';
		for (int i = 0; i < 8; i++) {
			cout << " " << i << " ";
			for (int j = 0; j < 8; j++) {
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
		cout << "请输入三个“字母数字”的组合，组合之间以回车隔开" << endl;
		cout << "例如：\na2\nb2\nb4\n" << endl;
	}

};
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
		if (grid[i][j] != blank && n != 0)return 0;
		if (i == a && j == b)return 1;
		n++;
		if (j == b) {
			if (i > a) {
				return barrier(i - 1, j, a, b, n);
			}
			else  return barrier(i + 1, j, a, b, n);
		}
		if (i == a) {
			if (j > b) {
				return barrier(i, j - 1, a, b, n);
			}
			else  return barrier(i, j + 1, a, b, n);
		}
		else {
			if (i > a && j > b) {
				return barrier(i - 1, j - 1, a, b, n);
			}
			else if (i < a && j < b)  return barrier(i + 1, j + 1, a, b, n);
			else if (i > a && j < b) return  barrier(i - 1, j + 1, a, b, n);
			else return  barrier(i + 1, j - 1, a, b, n);
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
};
class Over {
private:
	Rule rule;
public:
	bool die_chess(int a, int b) {
		if (a != 0) {
			if (grid[a - 1][b] == blank)return 0;
		}
		if (a != 7) {
			if (grid[a + 1][b] == blank)return 0;
		}
		if (b != 0) {
			if (grid[a][b - 1] == blank)return 0;
		}
		if (b != 7) {
			if (grid[a][b + 1] == blank)return 0;
		}
		if (a != 0 && b != 0) {
			if (grid[a - 1][b - 1] == blank)return 0;
		}
		if (a != 7 && b != 0) {
			if (grid[a + 1][b - 1] == blank)return 0;
		}
		if (a != 0 && b != 7) {
			if (grid[a - 1][b + 1] == blank)return 0;
		}
		if (a != 7 && b != 7) {
			if (grid[a + 1][b + 1] == blank)return 0;
		}
		return 1;
	}
	bool game_endW() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (grid[i][j] == 'W') {
					if (die_chess(i, j))continue;
					else return 0;
				}
			}
		}
		return 1;
	}
	bool game_endB() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (grid[i][j] == 'B') {
					if (die_chess(i, j))continue;
					else return 0;
				}
			}
		}
		return 1;
	}
};
class AmazonAI {
private:
	struct Pos { int r, c; };
	struct Move { Pos from, to, arrow; };
	int maxDepth = 2;
	const int INF = 1000000;

	//char转换int处理
	int getRole(char c) {
		if (c == 'B') return 1;
		if (c == 'W') return 2;
		if (c == 'X') return -1;
		return 0;
	}

public:
	// 外部调用的主接口
	void move(char grid[8][8]) {
		int tempBoard[8][8];
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				tempBoard[i][j] = getRole(grid[i][j]);

		Move best = findBest(tempBoard, 2);

		// 执行到原棋盘
		grid[best.from.r][best.from.c] = blank;
		grid[best.to.r][best.to.c] = 'W';
		grid[best.arrow.r][best.arrow.c] = 'X';
	}

private:
	Move findBest(int board[8][8], int aiColor) {
		vector<Move> moves = generateMoves(board, aiColor);
		Move bestMove = moves[0];
		int alpha = -INF, beta = INF, bestVal = -INF;

		for (auto& m : moves) {
			execute(board, m, aiColor);
			int val = minimax(board, maxDepth - 1, alpha, beta, false, aiColor);
			undo(board, m, aiColor);
			if (val > bestVal) {
				bestVal = val;
				bestMove = m;
			}
			alpha = max(alpha, bestVal);
		}
		return bestMove;
	}

	int minimax(int board[8][8], int depth, int alpha, int beta, bool isMax, int aiColor) {
		if (depth == 0) return evaluate(board, aiColor);

		int turnColor = isMax ? aiColor : (3 - aiColor);
		vector<Move> moves = generateMoves(board, turnColor);
		if (moves.empty()) return isMax ? -INF + 10 : INF - 10;

		if (isMax) {
			int maxEval = -INF;
			for (auto& m : moves) {
				execute(board, m, aiColor);
				maxEval = max(maxEval, minimax(board, depth - 1, alpha, beta, false, aiColor));
				undo(board, m, aiColor);
				alpha = max(alpha, maxEval);
				if (beta <= alpha) break;//剪枝
			}
			return maxEval;
		}
		else {
			int minEval = INF;
			for (auto& m : moves) {
				execute(board, m, 3 - aiColor);
				minEval = min(minEval, minimax(board, depth - 1, alpha, beta, true, aiColor));
				undo(board, m, 3 - aiColor);
				beta = min(beta, minEval);
				if (beta <= alpha) break;
			}
			return minEval;
		}
	}

	int evaluate(int board[8][8], int aiColor) {
		int m1 = countMobility(board, aiColor);
		int m2 = countMobility(board, 3 - aiColor);
		return m1 - m2;
	}//综合价值

	int countMobility(int board[8][8], int color) {
		int count = 0;
		int dr[] = { -1,-1,-1,0,0,1,1,1 }, dc[] = { -1,0,1,-1,1,-1,0,1 };
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board[r][c] == color) {
					for (int i = 0; i < 8; i++) {
						int nr = r + dr[i], nc = c + dc[i];
						while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && board[nr][nc] == 0) {
							count++; nr += dr[i]; nc += dc[i];
						}
					}
				}
			}
		}
		return count;
	}

	vector<Move> generateMoves(int board[8][8], int color) {
		vector<Move> moves;
		int dr[] = { -1,-1,-1,0,0,1,1,1 }, dc[] = { -1,0,1,-1,1,-1,0,1 };
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board[r][c] != color) continue;
				for (int i = 0; i < 8; i++) {
					int nr = r + dr[i], nc = c + dc[i];
					while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && board[nr][nc] == 0) {
						int old = board[nr][nc];
						board[r][c] = 0; board[nr][nc] = color;
						for (int j = 0; j < 8; j++) {
							int ar = nr + dr[j], ac = nc + dc[j];
							while (ar >= 0 && ar < 8 && ac >= 0 && ac < 8 && board[ar][ac] == 0) {
								moves.push_back({ {r,c}, {nr,nc}, {ar,ac} });
								ar += dr[j]; ac += dc[j];
							}
						}
						board[nr][nc] = old; board[r][c] = color;
						nr += dr[i]; nc += dc[i];
					}
				}
			}
		}
		return moves;
	}

	void execute(int b[8][8], Move m, int c) { b[m.from.r][m.from.c] = 0; b[m.to.r][m.to.c] = c; b[m.arrow.r][m.arrow.c] = -1; }
	void undo(int b[8][8], Move m, int c) { b[m.arrow.r][m.arrow.c] = 0; b[m.to.r][m.to.c] = 0; b[m.from.r][m.from.c] = c; }
};
class Game {
private:
	Board board;
	Rule rule;
	Over over;
	AmazonAI amazon_ai;
	// 保存到本地文件
	void saveToFile() {
		ofstream fout("savegame.txt"); // 创建输出文件流
		if (!fout.is_open()) {
			cout << "无法创建存档文件！" << endl;
			return;
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// 将空格替换为特殊字符（如'.'），防止读取时被跳过
				char c = (grid[i][j] == ' ') ? '.' : grid[i][j];
				fout << c;
			}
			fout << endl;
		}
		fout.close();
		cout << "存档已成功写入硬盘 (savegame.txt)" << endl;
	}

	// 从本地文件读取
	bool loadFromFile() {
		ifstream fin("savegame.txt"); // 打开输入文件流
		if (!fin.is_open()) {
			return false; // 文件不存在
		}
		string line;
		for (int i = 0; i < 8; i++) {
			if (getline(fin, line)) {
				for (int j = 0; j < 8; j++) {
					// 还原空格
					grid[i][j] = (line[j] == '.') ? ' ' : line[j];
				}
			}
		}
		fin.close();
		return true;
	}
public:
	Game() {
		bool game_running = false;
		bool kedu = 0;
	start:
		clear();
		board.menu();
		string input;
		getline(cin, input);
		stringstream ss(input);
		if (input == "menu") {
			cout << "已经在主菜单！" << endl;
			Sleep(1000);
			goto start;
		}
		int n;
		if (!(ss >> n)) {
			cout << "输入无效！请输入1-5：";
			Sleep(1000);
			goto start;
		}
		if (n == 1) {
			game_running = true;
			board.start();
		gaming:
			while (!over.game_endW() && !over.game_endB()) {
				clear();
				board.run();
				string line1;
				getline(cin, line1);
				int a1 = 0; char ch1 = 0;
				stringstream ss1(line1);
				if (line1 == "menu") {
					goto start;
				}
				if (!(ss1 >> ch1 >> a1)) {
					cout << "格式错误！请按照 字母数字 格式输入:" << endl;
					Sleep(1000);
					continue;
				}
				int a2 = 0; char ch2 = 0; int a3 = 0; char ch3 = 0; char temp = 0;
				if (!rule.valid(a1, ch1 - 'a') || grid[a1][ch1 - 'a'] != 'B') {
					cout << "起始位置不合法！" << endl;
					Sleep(1000);
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
						Sleep(1000);
						continue;
					}
					if (rule.move_valid(a1, ch1 - 'a', a2, ch2 - 'a')) {
						temp = grid[a1][ch1 - 'a'];
						grid[a1][ch1 - 'a'] = blank;
						grid[a2][ch2 - 'a'] = temp;
					}
					else {
						cout << "移动不合法！";
						Sleep(1000);
						continue;
					}
					string line3;
					getline(cin, line3);
					stringstream ss3(line3);
					if (line3 == "menu") {
						// 回退移动
						grid[a1][ch1 - 'a'] = temp;
						grid[a2][ch2 - 'a'] = blank;
						goto start;
					}
					if (!(ss3 >> ch3 >> a3)) {
						cout << "格式错误！回退移动。" << endl;
						Sleep(1000);
						grid[a1][ch1 - 'a'] = temp;
						grid[a2][ch2 - 'a'] = blank;
						continue;
					}
					if (rule.move_valid(a2, ch2 - 'a', a3, ch3 - 'a')) {
						grid[a3][ch3 - 'a'] = 'X';
						// 检查玩家走完后，黑方是否把白方围死了
						if (over.game_endW()) {
							clear(); board.run();
							cout << "黑方胜利！" << endl;
							Sleep(2000);
							goto start;
						}
						// 检查 AI 走完后，是否把黑方围死了
						if (over.game_endB()) {
							clear(); board.run();
							cout << "白方胜利！" << endl;
							Sleep(2000);
							goto start;
						}
						cout << "AI正在思考...";
						Sleep(500);
						amazon_ai.move(grid); // AI 执行移动并射箭
					}
					else {
						cout << "射箭位置不合法！";
						grid[a1][ch1 - 'a'] = temp;
						grid[a2][ch2 - 'a'] = blank;
						Sleep(1000);
						continue;
					}
				}
			}
			if (over.game_endW()) {
				cout << endl << "白方胜利！";
				Sleep(1000);
			}
			if (over.game_endB()) {
				cout << endl << "黑方胜利！";
				Sleep(1000);
			}

		}
		if (n == 2) {
			if (!game_running) {
				cout << "游戏中才能存盘！";
			}
			else {
				saveToFile(); // 调用刚才写的函数
			}
			Sleep(1000);
			goto start;
		}
		if (n == 3) {
			if (!game_running) {
				cout << "没有进行中的游戏！" << endl;
				Sleep(1000);
				goto start;
			}
			else goto gaming;
		}
		if (n == 4) {
			if (loadFromFile()) {
				cout << "读盘成功！正在恢复游戏...";
				game_running = true; // 确保读盘后标记为游戏中
				Sleep(1000);
				goto gaming;
			}
			else {
				cout << "未发现存档文件！";
				Sleep(1000);
				goto start;
			}
		}
		if (n == 5) {
			return;
		}
		if (!(n == 1 || n == 2 || n == 3 || n == 4)) {
			cout << "数字不合法！\n请输入1-5：" << endl;
			Sleep(1000);
			goto start;
		}
	}
};
int main() {
	Game game;
	return 0;
}