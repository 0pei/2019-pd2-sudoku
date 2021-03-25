#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
int main() {
    int su[9][9], h, x, y;
    srand(time(NULL));
    Sudoku gener;
    ifstream inFile("file.in", ios::in);

    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            inFile >> su[r][c];
        }
    }
    gener.setMap(su);

    h = rand() % 11 + 40;                           //dig 40~50 holes
    gener.generate(h);
    gener.print();
    return 0;
}
