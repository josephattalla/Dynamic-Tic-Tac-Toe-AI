#include <iostream>
#include "ttt.h"
#include <stdlib.h>
#include <chrono>
#include <fstream>


int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();

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

    ttt t(board_size, depth);
    while (!t.terminal())
    {
        vector<int> move = t.minimax();
        t.turn(move[0], move[1]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    ofstream fout("cpp.csv", ios_base::app);
    string data = to_string(board_size) + "," + to_string(depth) + "," + to_string(elapsed.count()) + "\n";
    fout << data;
    fout.close();
}