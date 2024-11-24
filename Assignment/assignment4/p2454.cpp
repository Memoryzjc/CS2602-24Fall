#include <iostream>
#include <queue>

struct Cell {
    int fish;
    int row;
    int col;
    Cell(int f, int r, int c) : fish(f), row(r), col(c) {}
};

int main() {
    int m, n, fish;
    int result = 0, sum = 0;
    int lake[102][102];
    std::cin >> m >> n;

    // Initialization
    for (int i = 0; i < 102; i++) {
        for (int j = 0; j < 102; j++) {
            if (i == 0 || j == 0 || i > m || j > n) {
                lake[i][j] = 0;
            } else {
                std::cin >> fish;
                lake[i][j] = fish;
            }
        }
    }

    std::queue<Cell> que;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (!lake[i][j]) {
                continue;
            }

            que.push(Cell(lake[i][j], i, j));
            lake[i][j] = 0; // Mark as visited

            sum = 0; // Reset sum for each new component
            while (!que.empty()) {
                Cell current = que.front();
                que.pop();

                sum += current.fish;

                // Check and push adjacent cells
                if (lake[current.row - 1][current.col]) {
                    que.push(Cell(lake[current.row - 1][current.col], current.row - 1, current.col));
                    lake[current.row - 1][current.col] = 0; // Mark as visited
                }
                if (lake[current.row][current.col - 1]) {
                    que.push(Cell(lake[current.row][current.col - 1], current.row, current.col - 1));
                    lake[current.row][current.col - 1] = 0; // Mark as visited
                }
                if (lake[current.row][current.col + 1]) {
                    que.push(Cell(lake[current.row][current.col + 1], current.row, current.col + 1));
                    lake[current.row][current.col + 1] = 0; // Mark as visited
                }
                if (lake[current.row + 1][current.col]) {
                    que.push(Cell(lake[current.row + 1][current.col], current.row + 1, current.col));
                    lake[current.row + 1][current.col] = 0; // Mark as visited
                }
            }

            if (sum > result) {
                result = sum;
            }
        }
    }

    std::cout << result << std::endl;

    return 0;
}