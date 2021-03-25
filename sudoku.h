#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <ctime>
using namespace std;
class Sudoku {
  public:
    int result = 1;
    Sudoku();
    void setMap(int set_map[][9]);
    void anotherSetMap(int set_map[][9]);
    void print();

    //generate
    void generate(int h);

    //transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    //solve
    void fillIn();
    void anotherFillIn();
    bool solve();
    bool anotherSolve();
    bool checkSame();

  private:
    int map[9][9], anotherMap[9][9], temp[9][9], IF, x, y, p[9][9], ap[9][9], u[9][9][9], au[9][9][9];
    bool hasBlank(int &r, int &c);
    bool OK(int r, int c, int n);
    bool usedInRow(int r, int n);
    bool usedInCol(int c, int n);
    bool usedInCell(int r, int c, int n);
    bool anotherHasBlank(int &r, int &c);
    bool anotherOK(int r, int c, int n);
    bool anotherUsedInRow(int r, int n);
    bool anotherUsedInCol(int c, int n);
    bool anotherUsedInCell(int r, int c, int n);
};

#endif // SUDOKU_H
