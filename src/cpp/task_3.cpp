//the overall time complexity is O(rows * cols).
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
    int x, y, dist;
};

bool isValid(int x, int y, int rows, int cols, vector<vector<char>>& maze, vector<vector<bool>>& visited) {
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == '.' && !visited[x][y];
}

int shortestPath(vector<vector<char>>& maze, int startRow, int startCol, int exitRow, int exitCol) {
    int rows = maze.size();
    int cols = maze[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Possible moves: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    queue<Point> q;
    q.push({startRow, startCol, 0});
    visited[startRow][startCol] = true;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.x == exitRow && curr.y == exitCol) {
            return curr.dist; // Found the exit
        }

        // Explore all possible moves
        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isValid(newX, newY, rows, cols, maze, visited)) {
                q.push({newX, newY, curr.dist + 1});
                visited[newX][newY] = true;
            }
        }
    }

    return -1; // No path found
}

int main() {
    vector<vector<char>> maze = {
        {'S', '.', '.', '#', '.', '#'},
        {'.', '#', '.', '#', '.', '#'},
        {'.', '#', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '#', '.'},
        {'.', '.', '.', '#', 'E', '.'}
    };

    int startRow = 0, startCol = 0;
    int exitRow = 4, exitCol = 4;

    int result = shortestPath(maze, startRow, startCol, exitRow, exitCol);

    if (result != -1) {
        cout << "Shortest path length: " << result << endl;
    } else {
        cout << "No path found to the exit." << endl;
    }

    return 0;
}
