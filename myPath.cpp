#include <iostream>
#include <cmath>

using namespace std;

const int rows = 7; // Number of rows in the map
const int cols = 7; // Number of columns in the map

int map[rows][cols] = {0}; // 2D array representing the map

void addObstacle(int x, int y) {
	map[x - 1][y - 1] = 1; // Mark obstacle at position (x, y)
}

void printMap() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << map[i][j] << " "; // Print each cell of the map
		}
		cout << endl;
	}
}

int calcDis(int currentX,int currentY,int targetX,int targetY) {
	return abs(targetX-currentX)+abs(targetY-currentY); // Calculate Manhattan distance between two points
}

bool isValid(int x, int y) {
	return x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] != 1; // Check if position (x, y) is valid and not an obstacle
}

void findNextStep(int currentX, int currentY, int &nextX, int &nextY, int targetX, int targetY) {
	int minDist = rows*cols+1; // Initialize minimum distance to a large value

	int dx[4] = {0, 0, -1, 1}; // Changes in x-coordinate for up, down, left, and right movements
	int dy[4] = {-1, 1, 0, 0}; // Changes in y-coordinate for up, down, left, and right movements

	for (int i = 0; i < 4; ++i) {
		int newX = currentX + dx[i]; // Calculate new x-coordinate
		int newY = currentY + dy[i]; // Calculate new y-coordinate

		if (!isValid(newX, newY)) continue; // Skip if the new position is invalid

		int dist = calcDis(newX,newY,targetX,targetY); // Calculate distance to the target
		if (dist < minDist) { // Update minimum distance and next position if the new position is closer to the target
			minDist = dist;
			nextX = newX;
			nextY = newY;
		}
	}
}

void findPath() {
	int startX = 0; // Starting position x-coordinate
	int startY = 0; // Starting position y-coordinate
	int endX = rows - 1; // Target position x-coordinate
	int endY = cols - 1; // Target position y-coordinate

	int currentX = startX; // Current position x-coordinate
	int currentY = startY; // Current position y-coordinate

	while (currentX != endX || currentY != endY) { // Loop until reaching the target position
		map[currentX][currentY] = 2; // Mark current position as visited
		findNextStep(currentX, currentY, currentX, currentY, endX, endY); // Find the next step towards the target
		if (currentX == startX && currentY == startY) { // If the algorithm goes back to the starting position, there is no way to reach the target
			cout << "NOWAY" << endl;
			return;
		}
	}

	map[currentX][currentY] = 2; // Mark the target position as visited
}

int main() {
	int obstacleCount; // Number of obstacles
	cout << "Enter number of obstacles: ";
	cin >> obstacleCount;

	for (int i = 0; i < obstacleCount; ++i) { // Input obstacle positions
		int x, y;
		cout << "Enter obstacle " << i + 1 << " position (x y): ";
		cin >> x >> y;
		addObstacle(x, y);
	}

	findPath(); // Find the path from the starting position to the target

	cout << "Map after finding path:" << endl;
	printMap(); // Print the map showing the path

	return 0;
}
