#include "sudoku.h"
#include <iostream>
using namespace std;
int main() {
    int su[9][9], IF, x, y;
    Sudoku trans;
    for(int r = 0; r < 9; ++r) {
        for(int c = 0; c < 9; ++c) {
            cin >> su[r][c];
        }
    }
    trans.setMap(su);

    cin >> IF;						//instruction format
    while(IF != 0) {
        if(IF == 1) {
            cin >> x >> y;
            trans.swapNum(x, y);
        } else if(IF == 2) {
            cin >> x >> y;
            trans.swapRow(x, y);
        } else if(IF == 3) {
            cin >> x >> y;
            trans.swapCol(x, y);
        } else if(IF == 4) {
            cin >> x;
            trans.rotate(x);
        } else if(IF == 5) {
            cin >> x;
            trans.flip(x);
        }
        cin >> IF;
    }
    trans.print();
    return 0;
}
