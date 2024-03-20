#include <iostream>
#include "ttt.h"
#include <stdlib.h>
#include <cctype>


int main(int argc, char* argv[])
{
    int board_size = 3;
    int depth = 10;
    if (argc > 1)
    {
        while (true)
        {
            char* arg = argv[1];
            while (*arg != '\0')
            {
                if (!isdigit(*arg))
                {
                    cout << "Please enter a digit for the size of the board." << endl;
                    return 1;
                }
                arg++;
            }
            break;
        }
        board_size = atoi(argv[1]);

        if (argc > 2)
        {
            while (true)
            {
                char* arg = argv[2];
                while (*arg != '\0')
                {
                    if (!isdigit(*arg))
                    {
                        cout << "Please enter a digit for the depth of the minimax algo." << endl;
                        return 1;
                    }
                    arg++;
                }
                break;
            }
        }
        depth = atoi(argv[2]);
    }

    ttt t(board_size, depth);
    while (!t.terminal())
    {
        vector<int> move = t.minimax();
        t.turn(move[0], move[1]);
        t.printBoard();
        if (t.terminal())
        {
            t.printBoard();
            break;
        }

        string row;
        string col;

        while (true)
        {
            while (true)
            {
                bool valid = true;
                cout << "row: ";
                cin >> row;
                for (char c : row)
                {
                    if (!isdigit(c))
                    {
                        cout << "Please enter a digit for the row." << endl;
                        valid = false;
                        break;
                    }
                }
                if (!valid)
                {
                    continue;
                }

                break;
            }
            while (true)
            {
                bool valid = true;
                cout << "col: ";
                cin >> col;
                for (char c : col)
                {
                    if (!isdigit(c))
                    {
                        cout << "Please enter a digit for the col." << endl;
                        valid = false;
                        break;
                    }
                }
                if (!valid)
                {
                    continue;
                }

                break;
            }
            if (!t.validMove(stoi(row), stoi(col)))
            {
                cout << "Invalid, try again.";
                continue;
            }

            t.turn(stoi(row), stoi(col));
            break;
        }
        t.printBoard();
    }

    if (t.winner() == 'X' || t.winner() == 'O')
    {
        cout << t.winner() << " Wins!" << endl;
    }
    else
    {
        cout << "Tie!" << endl;
    }
}