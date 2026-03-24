#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// 方向：N, E, S, W
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { -1, 0, 1, 0 };

int getDirectionIndex(char dir) {
    switch (dir) {
    case 'N': return 0;
    case 'E': return 1;
    case 'S': return 2;
    case 'W': return 3;
    }
    return 0;
}

bool solveMaze(vector<string>& maze, int startX, int startY, char startDir) {
    int n = maze.size(), m = maze[0].size();
    int dir = getDirectionIndex(startDir);
    int x = startX, y = startY;

    // 访问标记数组，记录在某个位置的某个方向是否访问过
    bool visited[100][100][4];
    memset(visited, false, sizeof(visited));

    while (true) {
        // 如果找到目标，返回true
        if (maze[y][x] == 'T') {
            return true;
        }

        // 如果这个状态已经访问过，说明进入循环，无法到达
        if (visited[y][x][dir]) {
            return false;
        }
        visited[y][x][dir] = true;

        // 按照左手定则尝试移动：左转、直行、右转、后退
        bool moved = false;
        for (int i = 0; i < 4; i++) {
            // 优先级：左转(i=0)、直行(i=1)、右转(i=2)、后退(i=3)
            int tryDir;
            if (i == 0) { // 左转
                tryDir = (dir + 3) % 4;
            }
            else if (i == 1) { // 直行
                tryDir = dir;
            }
            else if (i == 2) { // 右转
                tryDir = (dir + 1) % 4;
            }
            else { // 后退
                tryDir = (dir + 2) % 4;
            }

            int nx = x + dx[tryDir];
            int ny = y + dy[tryDir];

            // 如果可以移动（不是墙）
            if (maze[ny][nx] != '#') {
                x = nx;
                y = ny;
                dir = tryDir;
                moved = true;
                break;
            }
        }

        // 如果无法移动（理论上不会发生，因为最外圈都是墙）
        if (!moved) {
            return false;
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<string> maze(n);
        cin.ignore(); // 忽略换行符

        int startX = -1, startY = -1;

        for (int i = 0; i < n; i++) {
            getline(cin, maze[i]);
            // 寻找起点S
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'S') {
                    startX = j;
                    startY = i;
                }
            }
        }

        char startDir;
        cin >> startDir;
        cin.ignore(); // 忽略换行符

        if (solveMaze(maze, startX, startY, startDir)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}