#include <iostream>
#include <algorithm>
#include <limits.h>
#include "ttt.h"


ttt::ttt()
{
    dimensions = 3;
    board = vector< vector<char> >(dimensions, vector<char>(dimensions, ' '));
    depth = 5;
}


ttt::ttt(const int& dimensions)
{
    if (dimensions < 3)
    {
        this->dimensions = 3;
    }
    else
    {
        this->dimensions = dimensions;
    }
    board = vector< vector<char> >(dimensions, vector<char>(dimensions, ' '));
    depth = 5;
}


ttt::ttt(const int& dimensions, const int& depth)
{
    if (dimensions < 3)
    {
        this->dimensions = 3;
    }
    else
    {
        this->dimensions = dimensions;
    }
    board = vector< vector<char> >(dimensions, vector<char>(dimensions, ' '));
    this->depth = depth;
}


void ttt::printBoard()
{
    cout << "  ";

    for (int i = 0; i < dimensions; i++)
    {
        cout << i << " ";
    }

    cout << endl;

    for (int i = 0; i < dimensions; i++)
    {
        cout << i << " ";
        for (int j = 0; j < dimensions; j++)
        {
            cout << board[i][j];

            if (j < dimensions-1)
            {
                cout << "|";
            }
        }
        cout << endl;
        if (i < dimensions-1)
        {
            cout << "  ";
            for (int j = 0; j < dimensions+dimensions-1; j++)
            {
                cout << "-";
            }
            cout << endl;
        }
    }
}


vector< vector<char> > ttt::initial_state()
{
    return vector< vector<char> >(dimensions, vector<char>(dimensions, ' '));
}


char ttt::player()
{   
    if (board == initial_state())
    {
        return p1;
    }

    int x = 0;
    int o = 0;

    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            if (board[i][j] == p1)
            {
                x++;
            }
            else if (board[i][j] == p2)
            {
                o++;
            }
        }
    }

    return (o >= x) ? p1 : p2;
}


char ttt::player(const vector< vector<char> >& b)
{
    if (b == initial_state())
    {
        return p1;
    }

    int x = 0;
    int o = 0;

    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            if (b[i][j] == p1)
            {
                x++;
            }
            else if (b[i][j] == p2)
            {
                o++;
            }
        }
    }

    return (o >= x) ? p1 : p2;
}


bool ttt::validMove(const int& row, const int& col)
{
    return row < dimensions && row >= 0 && col < dimensions && col >= 0 && board[row][col] == ' ';
}


bool ttt::terminal()
{
    if (winner() != 'n')
    {
        return true;
    }

    return false;
}


bool ttt::terminal(const vector< vector<char> >& b)
{
    if (winner(b) != 'n')
    {
        return true;
    }

    return false;
}


char ttt::winner()
{
    /*
        Dynamically checks if there is a winner.
    */

    // track if a player filled the diagnols
    bool diag1 = true;
    bool diag2 = true;

    // track if the board is full
    bool full = true;

    for (int i = 0; i < dimensions; i++)
    {
        // track if a player filled the row/col
        bool row = true;
        bool column = true;

        for (int j = 0; j < dimensions; j++)
        { 
            // if the space is empty, the board and row is not full
            if (board[i][j] == ' ')
            {
                full = false;
                row = false;
            }

            // check row and column
            if (j > 0)
            {
                // if the jth col in ith row is not the same as the previous, row is not continous
                if (board[i][j] != board[i][j-1])
                {
                    row = false;
                }
                
                // if the jth row in the ith col is not the same as the previous, col is not continuous
                if (board[j][i] != board[j-1][i] || board[j][i] == ' ')
                {
                    column = false;
                }
            }
        }

        // check diagnols
        if (i > 0)
        { 
            // if the diagnol starting in the top left is not continous, diag1 is false
            if (board[i][i] != board[i-1][i-1] || board[i][i] == ' ')
            {
                diag1 = false;
            }

            // if the diagnol starting in the top right is not continuous, diag2 is false
            if (board[i][dimensions-1-i] != board[i-1][dimensions-1-i+1] || board[i][dimensions-1-i] == ' ')
            {
                diag2 = false;
            }
        }
        
        // if row, return the player in the ith row
        if (row)
        {
            return board[i][0];
        }

        // if column, return the player in the ith column
        if (column)
        {
            return board[0][i];
        }
    }

    // if diag1 is true, return the player in the top left space
    if (diag1)
    {
        return board[0][0];
    }

    // if diag2 is true, return the player in the top right space
    if (diag2)
    {
        return board[0][dimensions-1];
    }

    // if the board is full, return 't' for tie
    if (full)
    {
        return 't';  
    }

    // return 'n' for no winner
    return 'n';
}


char ttt::winner(const vector< vector<char> >& b)
{
    /*
        Dynamically checks if there is a winner.
        Same implementation as the no parameter winner function, but using a given board rather than the objects board.
    */

    bool diag1 = true;
    bool diag2 = true;
    bool full = true;

    for (int i = 0; i < dimensions; i++)
    {
        bool row = true;
        bool column = true;

        for (int j = 0; j < dimensions; j++)
        {
            if (b[i][j] == ' ')
            {
                full = false;
                row = false;
            }
            if (j > 0)
            {
                if (b[i][j] != b[i][j-1])
                {
                    row = false;
                }
                if (b[j][i] != b[j-1][i] || b[j][i] == ' ')
                {
                    column = false;
                }
            }
        }

        if (i > 0)
        {
            if (b[i][i] != b[i-1][i-1] || b[i][i] == ' ')
            {
                diag1 = false;
            }
            if (b[i][dimensions-1-i] != b[i-1][dimensions-1-i+1] || b[i][dimensions-1-i] == ' ')
            {
                diag2 = false;
            }
        }
        
        if (row)
        {
            return b[i][0];
        }
        if (column)
        {
            return b[0][i];
        }
    }

    if (diag1)
    {
        return b[0][0];
    }
    if (diag2)
    {
        return b[0][dimensions-1];
    }

    if (full)
    {
        return 't';  
    }

    return 'n';
}


void ttt::turn(const int& row, const int& col)
{
    if (!validMove(row, col))
    {
        cout << "ERROR: INVALID MOVE" << endl;
        return;
    }

    board[row][col] = player();
}


vector< vector<int> > ttt::actions(const vector< vector<char> >& b)
{
    /*
        Returns all the empty spaces as a vector of (row, col) vectors 
    */

    vector< vector<int> > actions_;

    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            if (b[i][j] == ' ')
            {
                vector<int> a;
                a.push_back(i);
                a.push_back(j);
                actions_.push_back(a);
            }
        }
    }

    return actions_;
}


vector< vector<char> > ttt::result(const vector< vector<char> >& b, const vector<int>& action)
{
    /*
        returns the resulting board given a board and an action.
    */

    vector< vector<char> > board_(b);

    for (int i = 0 ; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            board_[i][j] = b[i][j];
        }
    }

    board_[action[0]][action[1]] = player(board_);
    return board_;
}


int ttt::utility(const vector< vector<char> >& b)
{
    /*
        returns utility of a terminal board, INT_MAX if x wins, -INT_MAX if o wins, 0 if tie. 
    */

    char winner_ = winner(b);
    
    if (winner_ == p1)
    {
        return INT_MAX;
    }
    else if (winner_ == p2)
    {
        return -INT_MAX;
    }
    return 0;
}


int ttt::evaluation(const vector< vector<char> >& b)
{
    /*
        Dynamically finds which player has the most winning opportunities --- dimensions length continuous openings.
        Returns the difference between the # of openings for x and o. Will return a positive if x has more, negative if o has more, 0 if tie.
    */

    // track the # of openings for each plauer
    int x = 0;
    int o = 0;

    // track the number of spots/potential spots each player has in the diagnols
    int x_diag1 = 0;
    int o_diag1 = 0;
    int x_diag2 = 0;
    int o_diag2 = 0;

    for (int i = 0; i < dimensions; i++)
    {

        // check diagnols
        if (b[i][i] == p1)
        {
            x_diag1++;
        }
        else if (b[i][i] == p2)
        {
            o_diag1++;
        }
        else
        {
            x_diag1++;
            o_diag1++;
        }

        if (b[i][dimensions-1-i] == p1)
        {
            x_diag2++;
        }
        else if (b[i][dimensions-1-i] == p2)
        {
            o_diag2++;
        }
        else
        {
            x_diag2++;
            o_diag2++;
        }

        // count how many openings/filled spots for x and o in the rows and columns
        int row_x = 0;
        int row_o = 0;
        int col_x = 0;
        int col_o = 0;
        for (int j = 0; j < dimensions; j++)
        {
            // check row
            if (b[i][j] == p1)
            {
                row_x++;
            }
            else if (b[i][j] == p2)
            {
                row_o++;
            }
            else
            {
                row_o++;
                row_x++;
            }

            // check col
            if (b[j][i] == p1)
            {
                col_x++;
            }
            else if (b[j][i] == p2)
            {
                col_o++;
            }
            else
            {
                col_x++;
                col_o++;
            }
        }

        // add to the # of opportunites for each player in the rows and columns
        if (row_x == dimensions)
        {
            x++;
        }
        if (row_o == dimensions)
        {
            o++;
        }
        if (col_x == dimensions)
        {
            x++;
        }
        if (col_o == dimensions)
        {
            o++;
        }
    }

    // add to the # of opportunites for each player in the diagnols
    if (x_diag1 == dimensions)
    {
        x++;
    }
    if (o_diag1 == dimensions) 
    {
        o++;
    }
    if (x_diag2 == dimensions)
    {
        x++;
    }
    if (o_diag2 == dimensions)
    {
        o++;
    }


    return x-o;
}


vector<int> ttt::minimax()
{
    /*
        Returns the optimal move of the current player. Implements alpha-beta pruning and depth limited search.
    */

    // if the game is over, return an invalid position (-1, -1)
    if (terminal(board))
    {
        return vector<int>(2, -1);
    }


    // all possible actions
    vector< vector<int> > actions_ = actions(board);

    // variable to hold the best action
    vector<int> best_action;

    // if  p1('X') turn, we want to maximize alpha
    if (player() == p1)
    {
        // set alpha to the minimum value, we want to maximize this to get the best action
        int alpha = INT_MIN;
        
        // loop through the possible actions
        for (int i = 0; i < actions_.size(); i++)
        {
            // find the best outcome for the opponent, given the resulting board of the current action
            int v = min_value(result(board, actions_[i]), alpha, depth);

            // if this outcome is better than our current best, set alpha to this outcome and best_action to this action
            if (v > alpha)
            {
                alpha = v;
                best_action = actions_[i];
            }
        }
    }

    // else player is p2('O'), we want to minimize beta
    else
    {
        // set beta to the maximum value, we want to minimize this to get the best action
        int beta = INT_MAX;

        // loop through the possible actions
        for (int i = 0; i < actions_.size(); i++)
        {
            // find the best outcome for the opponent, given the resulting board of the current action
            int v = max_value(result(board, actions_[i]), beta, depth);

            // if this outcome is better than our current best, set beta to this outcome and best_action to this action
            if (v < beta)
            {
                beta = v;
                best_action = actions_[i];
            }
        }
    }


    return best_action;
}


int ttt::max_value(const vector< vector<char> >& b, const int& beta, const int& d)
{
    /*
        Returns the maximum outcome of the current board. 
        Called by the minimizing player, so we take in beta to be able to prune this branch if the max we find is higher than the beta.
    */

    // if game is over, return the utility
    if (terminal(b))
    {
        return utility(b);
    }

    // if depth is reached, return evaluation of the current baord
    if (d == 0)
    {
        return evaluation(b);
    }

    // set alpha to the minimum value, we want to maximize this
    int alpha = INT_MIN;

    // all possible actions
    vector< vector<int> > actions_ = actions(b);

    // loop through the actions
    for (int i = 0; i < actions_.size(); i++)
    { 
        // set alpha to the max of the current alpha, and the best outcome of the other player given the current action and decrement depth to account for this iteration
        alpha = max(alpha, min_value(result(b, actions_[i]), alpha, d-1));

        // if the alpha we found is greater than or equal to the beta passed in, then there is already a better outcome for the minimizing player, so we can prune this branch
        if (alpha >= beta)
        {
            break;
        }
    }

    return alpha;
}


int ttt::min_value(const vector< vector<char> >& b, const int& alpha, const int& d)
{
    /*
        Returns the minimum outcome of the current board. 
        Called by the maximizing player, so we take in alpha to be able to prune this branch if the min we find is lower than alpha.
    */

    // if game is over, return the utility
    if (terminal(b))
    {
        return utility(b);
    }

    // if depth is reached, return evaluation of the current baord
    if (d == 0)
    {
        return evaluation(b);
    }

    // set beta to the max value, we want to minimize this
    int beta = INT_MAX;

    // all possible actions
    vector< vector<int> > actions_ = actions(b);

    // iterate through the actions
    for (int i = 0; i < actions_.size(); i++)
    {
        // set beta to the min of the current beta, and the best outcome of the other player given the current action and decrement depth to account for this iteration
        beta = min(beta, max_value(result(b, actions_[i]), beta, d-1));

        // if the beta we found is less than or equal to the alpha passed in, then there is already a better outcome for the maximizing player, so we can prune this branch
        if (beta <= alpha)
        {
            break;
        }
    }

    return beta;
}


vector< vector<char> > ttt::getBoard()
{
    return board;
}