#include "sudoku.h"
#include <iostream>
#include <ctime>
using namespace std;
Sudoku::Sudoku() {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            map[r][c] = 0;
            anotherMap[r][c] = 0;
        }
    }
}

void Sudoku::setMap(int set_map[][9]) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0 ; c < 9; ++c) {
            map[r][c] = set_map[r][c];
        }
    }
}

void Sudoku::anotherSetMap(int set_map[][9]) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            anotherMap[r][c] = set_map[r][c];
        }
    }
}

void Sudoku::print() {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 8; ++c) {
            cout << map[r][c] << " ";
        }
        cout << map[r][8] << endl;
    }
}

//generate
void Sudoku::generate(int h) {
    for(int n = 0; n < h; n++) {
        map[rand() % 9][rand() % 9] = 0;							//dig holes
    }

    //transform
    IF = rand() % 6;												//instruction format
    while(IF != 0) {
        if(IF == 1) {
            x = rand() % 9 + 1;
            y = rand() % 9 + 1;
            swapNum(x, y);
        } else if(IF == 2) {
            x = rand() % 3;
            y = rand() % 3;
            swapRow(x, y);
        } else if(IF == 3) {
            x = rand() % 3;
            y = rand() % 3;
            swapCol(x, y);
        } else if(IF == 4) {
            x = rand() % 4;
            rotate(x);
        } else if(IF == 5) {
            x = rand() % 2;
            flip(x);
        }
        IF = rand() % 6;
    }
}

//transform
void Sudoku::swapNum(int x, int y) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(map[r][c] == x) {
                map[r][c] = y;
            } else if(map[r][c] == y) {
                map[r][c] = x;
            }
        }
    }
}

void Sudoku::swapRow(int x, int y) {
    x *= 3;
    y *= 3;
    for(int r = x; r < (x + 3); ++r) {
        for(int c = 0; c < 9; ++c) {
            temp[r][c] = map[r][c];
            map[r][c] = map[y][c];
            map[y][c] = temp[r][c];
        }
        ++y;
    }
}

void Sudoku::swapCol(int x, int y) {
    x *= 3;
    y *= 3;
    for(int c = x; c < (x + 3); ++ c) {
        for(int r = 0; r < 9; ++r) {
            temp[r][c] = map[r][c];
            map[r][c] = map[r][y];
            map[r][y] = temp[r][c];
        }
        ++y;
    }
}

void Sudoku::rotate(int x) {
    if(x % 4 == 1) {												//90degree
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 6; ++j) {
                temp[i][j] = map[i][j];
                map[i][j] = map[8 - j][i];
                map[8 - j][i] = map[8 - i][8 - j];
                map[8 - i][8 - j] = map[j][8 - i];
                map[j][8 - i] = temp[i][j];
            }
        }
        temp[3][4] = map [3][4];
        map[3][4] = map[4][3];
        map[4][3] = map[5][4];
        map[5][4] = map[4][5];
        map[4][5] = temp[3][4];
    } else if(x % 4 == 2) {											//180degree
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 6; ++j) {
                temp[i][j] = map[i][j];
                map[i][j] = map[8 - i][8 - j];
                map[8 - i][8 - j] = temp[i][j];
                temp[8 - j][i] = map[8 - j][i];
                map[8 - j][i] = map[j][8 - i];
                map[j][8 - i] = temp[8- j][i];
            }
        }
        temp[3][4] = map[3][4];
        map[3][4] = map[5][4];
        map[5][4] = temp[3][4];
        temp[4][5] = map[4][5];
        map[4][5] = map[4][3];
        map[4][3] = temp[4][5];
    } else if(x % 4 == 3) {											//270degree
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 6; ++j) {
                temp[i][j] = map[i][j];
                map[i][j] = map[j][8 - i];
                map[j][8 - i] = map[8 - i][8 - j];
                map[8 - i][8 - j] = map[8 - j][i];
                map[8 - j][i] = temp[i][j];
            }
        }
        temp[3][4] = map[3][4];
        map[3][4] = map[4][5];
        map[4][5] = map[5][4];
        map[5][4] = map[4][3];
        map[4][3] = temp[3][4];
    }
}

void Sudoku::flip(int x) {
    if(x == 0) {													//up-down
        for(int c = 0; c < 9; ++c) {
            for(int r = 0; r < 4; ++r) {
                temp[r][c] = map[r][c];
                map[r][c] = map[8 - r][c];
                map[8-r][c] = temp[r][c];
            }
        }
    } else if(x == 1) {												//left-right
        for(int r = 0; r < 9; ++r) {
            for(int c = 0; c < 4; ++c) {
                temp[r][c] = map[r][c];
                map[r][c] = map[r][8 - c];
                map[r][8 - c] = temp[r][c];
            }
        }
    }
}

//solve
void Sudoku::fillIn() {
    for(int r = 0; r < 9; ++r) {									//initialize
        for(int c = 0; c < 9; ++c) {
            p[r][c] = 0;
            for(int n = 0; n < 9; ++n) {
                u[r][c][n] = 0;
            }
        }
    }
    //check unity
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(map[r][c] != 0) {
                for(int n = 1; n <= 9; ++n) {
                    u[r][c][n - 1] = 1;
                }
                for(int x = 0; x < 9; ++x) {
                    ++u[x][c][map[r][c] - 1];						//every row
                    for(int y = 0; y < 9; ++y) {
                        if(x / 3 == r / 3 && y / 3 == c / 3) {		//every cell
                            ++u[x][y][map[r][c] - 1];
                        }
                    }
                }
                for(int y = 0; y < 9; ++y) {
                    ++u[r][y][map[r][c] - 1];						//every column
                }
            }
        }
    }
    //count how many possibility
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            for(int n = 1; n <= 9; ++n) {
                if(u[r][c][n - 1] == 0) {
                    ++p[r][c];
                }
            }
        }
    }
    //fillin
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(p[r][c] == 1) {
                for(int n = 1; n <= 9; ++n) {
                    if(u[r][c][n - 1] == 0) {
                        map[r][c] = n;
                    }
                }
            }
        }
    }
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(p[r][c] == 1) {
                return fillIn();
            }
        }
    }
}

void Sudoku::anotherFillIn() {
    for(int r = 0; r < 9; ++r) {									//initialize
        for(int c = 0; c < 9; ++c) {
            ap[r][c] = 0;
            for(int n = 0; n < 9; ++n) {
                au[r][c][n] = 0;
            }
        }
    }
    //check unity
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(anotherMap[r][c] != 0) {
                for(int n = 1; n <= 9; ++n) {
                    au[r][c][n - 1] = 1;
                }
                for(int x = 0; x < 9; ++x) {
                    ++au[x][c][anotherMap[r][c] - 1];				//every row
                    for(int y = 0; y < 9; ++y) {
                        if(x / 3 == r / 3 && y / 3 == c / 3) {		//every cell
                            ++au[x][y][anotherMap[r][c] - 1];
                        }
                    }
                }
                for(int y = 0; y < 9; ++y) {
                    ++au[r][y][anotherMap[r][c] - 1];				//every column
                }
            }
        }
    }
    //count how many possibility
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            for(int n = 1; n <= 9; ++n) {
                if(au[r][c][n - 1] == 0) {
                    ++ap[r][c];
                }
            }
        }
    }
    //fillin
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(ap[r][c] == 1) {
                for(int n = 1; n <= 9; ++n) {
                    if(au[r][c][n - 1] == 0) {
                        anotherMap[r][c] = n;
                    }
                }
            }
        }
    }
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(ap[r][c] == 1) {
                return anotherFillIn();
            }
        }
    }
}

bool Sudoku::solve() {
    int r, c;
    if(hasBlank(r, c) == false) {									//find unassigned location
        return true;												//done
    }

    for(int n = 1; n <= 9; ++n) {
        if(OK(r, c, n) == true) {
            map[r][c] = n;
            if(solve() == true) {
                fillIn();
                return true;
            }
            map[r][c] = 0;											//fail, retry other n
        }
    }
    return false;													//trigger backtracking!!!
}

bool Sudoku::hasBlank(int &r, int &c) {
    for(r = 0; r < 9; ++r) {
        for(c = 0; c < 9; ++c) {
            if(map[r][c] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::OK(int r, int c, int n) {
    if(map[r][c] == 0 && usedInRow(r, n)  == false && usedInCol(c, n) == false && usedInCell(r / 3, c / 3, n) == false) {
        return true;
    }
    return false;
    //check if n is not already used in the row, column and cell
}

bool Sudoku::usedInRow(int r, int n) {
    for(int c = 0; c < 9; ++c) {
        if(map[r][c] == n) {
            return true;
        }
    }
    return false;
}

bool Sudoku::usedInCol(int c, int n) {
    for(int r = 0; r < 9; ++r) {
        if(map[r][c] == n) {
            return true;
        }
    }
    return false;
}

bool Sudoku::usedInCell(int R, int C, int n) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(r / 3 == R && c / 3 == C && map[r][c] == n) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::anotherSolve() {
    int r, c;
    if(anotherHasBlank(r, c) == false) {							//find unassigned location
        return true;												//done
    }

    for(int n = 9; n >= 1; --n) {
        if(anotherOK(r, c, n) == true) {
            anotherMap[r][c] = n;
            if(anotherSolve() == true) {
                anotherFillIn();
                return true;
            }
            anotherMap[r][c] = 0;									//fail, retry other n
        }
    }
    return false;													//trigger backtracking!!!
}

bool Sudoku::anotherHasBlank(int &r, int &c) {
    for(r = 8; r >= 0; --r) {
        for(c = 8; c >= 0; --c) {
            if(anotherMap[r][c] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::anotherOK(int r, int c, int n) {
    if(anotherMap[r][c] == 0 && anotherUsedInRow(r, n)  == false && anotherUsedInCol(c, n) == false && anotherUsedInCell( r / 3, c / 3, n) == false) {
        return true;
    }
    return false;
    //check if n is not already used in the row, column and cell
}

bool Sudoku::anotherUsedInRow(int r, int n) {
    for(int c = 0; c < 9; ++c) {
        if(anotherMap[r][c] == n) {
            return true;
        }
    }
    return false;
}

bool Sudoku::anotherUsedInCol(int c, int n) {
    for(int r = 0; r < 9; ++r) {
        if(anotherMap[r][c] == n) {
            return true;
        }
    }
    return false;
}

bool Sudoku::anotherUsedInCell(int R, int C, int n) {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(r / 3 == R && c / 3 == C && anotherMap[r][c] == n) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::checkSame() {
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            if(map[r][c] != anotherMap[r][c]) {
                return false;
            }
        }
    }
    return true;
}
