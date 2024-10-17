#include <iostream>

bool isLegal(const int sudoku[9][9]) {
    // check rows
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                if (k != j && sudoku[i][k] == sudoku[i][j]) {
                    return false;
                }
            }
        }
    }

    // check columns
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            for (int k = 0; k < 9; k++) {
                if (k != i && sudoku[k][j] == sudoku[i][j]) {
                    return false;
                }
            }
        }
    }

    // check blocks
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int ki = 0; ki < 3; ki++) {
                for (int kj = 0; kj < 3; kj++) {
                    for (int ii = 0; ii < 3; ii++) {
                        for (int jj = 0; jj < 3; jj++) {
                            if ((ii != ki || jj != kj) && sudoku[3*i + ii][3*j + jj] == sudoku[3*i + ki][3*j + kj]) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    int num;  // the number of sudoku
    std::cin >> num;

    int sudoku[9][9];
    bool result[num];

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 9; k++) {
                std::cin >> sudoku[j][k];
            }
        }

        result[i] = isLegal(sudoku);
    }

    for (int i = 0; i < num; i++) {
        if (result[i]) {
            std::cout << "Right" << std::endl;
        } else {
            std::cout << "Wrong" << std::endl;
        }
    }
    return 0;
}