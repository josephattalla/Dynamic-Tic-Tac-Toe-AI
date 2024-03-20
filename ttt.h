#include <vector>

using namespace std;

class ttt
{
    private:

        /* 
            --------data-----------
        */
        
        vector< vector<char> > board;
        int dimensions;
        char p1 = 'X';
        char p2 = 'O';
        int depth;
        
        /*
            ---------functions--------
        */

        // returns the inital state of the board --- an empty board
        vector< vector<char> > initial_state();

        // returns all possible actions on the board in a vector of (row, col) vectors
        vector< vector<int> > actions(const vector< vector<char> >& b);

        // returns the resulting board given the current board and an action
        vector< vector<char> > result(const vector< vector<char> >& b,const vector<int>& action);

        // returns the utility of the board, INT_MAX if x wins, -INT_MAX if o wins, 0 if tie
        int utility(const vector< vector<char> >& b);

        // returns the max utility/evaluation outcome of the board, implements alpha-beta prunging and depth limited search
        int max_value(const vector< vector<char> >& b, const int& beta, const int& d);

        // returns the minimum utility/evaluation outcome of the board, implements alpha-beta prunging and depth limited search
        int min_value(const vector< vector<char> >& b, const int& alpha, const int& d);

        // returns the player whose turn it is given a state of the board
        char player(const vector< vector<char> >& b);

        // returns the winner: p1 or p2 --- 't' if tie, 'n' if no winner
        char winner(const vector< vector<char> >& b);

        // returns true if game over, else false
        bool terminal(const vector< vector<char> >& b);

        // estimates the utility by returning the difference b/w the number of winning opportunities of x and o
        int evaluation(const vector< vector<char> >& b);
    
    public:

        /*
            -------constructors------
        */

        // sets the dimensions to 3 and initiates the board by putting ' ' into a 3x3 char array
        ttt();

        // sets the dimensions to the given dimensions and initiates the board by putting ' ' into a dimensionxdimension char array
        ttt(const int& dimensions);

        // sets the dimensions and depth
        ttt(const int& dimensions, const int& depth);

        /*
            ---------functions----------
        */

        // print board 
        void printBoard();
        
        // returns whose turn
        char player();

        // returns the winner
        char winner();

        // returns if the game is over
        bool terminal();

        // returns the best possible action, using alpha beta minimax algorithm
        vector<int> minimax();

        // returns true if the move is valid
        bool validMove(const int& row, const int& col);

        // puts the player whose turn it is on the position x, y on the board
        void turn(const int& row, const int& col);
};