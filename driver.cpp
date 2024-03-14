#include <iostream>
#include "ttt.h"


int main()
{
    ttt t(5);

    while (!t.terminal())
    {
        t.printBoard();
        vector<int> move = t.minimax();
        t.turn(move[0], move[1]);
    }
    cout << t.winner() << endl;
}