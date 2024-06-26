#include <iostream>
#include "ttt.h"
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <ctime>
#include <cstdlib>


int main(int argc, char* argv[])
{
    // start timer
    auto start = chrono::high_resolution_clock::now();

    // get board size and depth
    int board_size = 3;
    int depth = 3;
    if (argc == 2)
    {
        board_size = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        board_size = atoi(argv[1]);
        depth = atoi(argv[2]);
    }

    // instantiate ttt object
    ttt t(board_size, depth);
    
    // set random seed
    srand(time(0));

    // play game
    while (!t.terminal())
    {
        // minimax goes first, so is X
        vector<int> move = t.minimax();
        t.turn(move[0], move[1]);

        // get actions
        vector< vector<int> > actions = t.actions(t.getBoard());

        // get number of actions available
        int len = actions.size();

        if (!t.terminal())
        {
            // choose random action 
            move = actions[rand() % len];
            t.turn(move[0], move[1]);
        }
    }

    // end timer, calculate elapsed time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // minimax won if X won
    int win = t.winner() == 'X';

    // write board size, depth, elapsed time, if minimax won to csv
    ofstream fout("cpp.csv", ios_base::app);
    string data = to_string(board_size) + "," + to_string(depth) + "," + to_string(elapsed.count()) + "," + to_string(win) + "\n";
    fout << data;
    fout.close();
}