#include <iostream>
#include <cmath>

using namespace std;

const int rows = 7;
const int cols = 7;

int map[rows][cols] = {0};

void addObstacle(int x, int y) {
    map[x - 1][y - 1] = 1; // 障碍物标记为1
}

void printMap() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] != 1;
}

void findNextStep(int currentX, int currentY, int nextX, int nextY, int targetX, int targetY) {
    int minDist = 1000000; // 一个足够大的数

    int dx[4] = {0, 0, -1, 1}; // 上下左右四个方向
    int dy[4] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int newX = currentX + dx[i];
        int newY = currentY + dy[i];

        if (!isValid(newX, newY)) continue; // 越界或者是障碍物

        int dist = abs(newX - targetX) + abs(newY - targetY); // 计算到终点的距离
        if (dist < minDist) {
            minDist = dist;
            nextX = newX;
            nextY = newY;
        }
    }
}

void findPath() {
    int startX = 0;
    int startY = 0;
    int endX = rows - 1;
    int endY = cols - 1;

    int currentX = startX;
    int currentY = startY;

    while (currentX != endX || currentY != endY) {
        map[currentX][currentY] = 2; // 标记走过的路为2
        findNextStep(currentX, currentY, currentX, currentY, endX, endY);
        if (currentX == startX && currentY == startY) {
            cout << "NOWAY" << endl;
            return;
        }
    }

    map[currentX][currentY] = 2; // 标记终点为2
}

int main() {
    // 用户输入障碍物数量和位置
    int obstacleCount;
    cout << "Enter number of obstacles: ";
    cin >> obstacleCount;

    for (int i = 1; i <= obstacleCount; ++i) {
        int x, y;
        cout << "Enter obstacle " << i << " position (x y): ";
        cin >> x >> y;
        addObstacle(x, y);
    }

    findPath();

    cout << "Map after finding path:" << endl;
    printMap();

    return 0;
}
