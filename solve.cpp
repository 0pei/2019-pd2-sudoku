#include "sudoku.h"
#include <iostream>
using namespace std;
int main() {
    int su[9][9];
    Sudoku solve;
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            cin >> su[r][c];
        }
    }
    solve.setMap(su);
    solve.anotherSetMap(su);
    solve.fillIn();
    solve.anotherFillIn();
    if(solve.solve() == true) {
        if(solve.anotherSolve() == true && solve.checkSame() == false) {
            cout << 2 << endl;
        } 
		else if(solve.anotherSolve() == true && solve.checkSame() == true) {
            cout << 1 << endl;
            solve.print();
        }
    } else {
        cout << 0 << endl;
    }
    return 0;
}
