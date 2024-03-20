from copy import deepcopy
from math import inf 

class ttt:
    def __init__(self, dimensions, depth):
        self.dimensions = dimensions
        self.depth = depth
        self.p1 = 'X'
        self.p2 = 'O'
        
        # intiialize board with empty rows
        board = []
        for _ in range(dimensions):
            row = []
            for _ in range(dimensions):
                row.append(' ')
            board.append(row)
        
        self.board = board

    def initial_state(self, board):
        '''
            Returns true if the board is empty.
        '''

        for i in range(self.dimensions):
            for j in range(self.dimensions):
                if board[i][j] != ' ':
                    return False
        
        return True
        

    def print_board(self, board=None):

        if board == None:
            board = self.board

        # print the col indexes
        print('  ', end='')
        print(' '.join(f'{i}' for i in range(self.dimensions)))

        for i in range(self.dimensions):

            # print row indexes
            print(f'{i} ', end='')

            for j in range(self.dimensions):
                if j < self.dimensions-1:
                    print(f'{board[i][j]}', end='|')
                else:
                    print(f'{board[i][j]}')
            
            if i < self.dimensions-1:
                print('  ', end='')
                for _ in range(self.dimensions*2-1):
                    print('-', end='')
                print('')

    def player(self, board=None):
        '''
            Returns whose turn it is.
            If board is empty, return 'X'.
        '''

        if board == None:
            board = self.board
        
        if self.initial_state(board):
            return self.p1
        
        x = 0
        o = 0

        for i in range(self.dimensions):
            for j in range(self.dimensions):
                if board[i][j] == self.p1: x += 1
                elif board[i][j] == self.p2: o += 1
        
        return self.p1 if o >= x else self.p2

    def valid_move(self, row, col):
        '''
            Returns whether the given row and col is a valid move.
        ''' 

        return row >= 0 and row < self.dimensions and col >= 0 and col < self.dimensions and self.board[row][col] == ' '
    
    def turn(self, row, col):
        '''
            Places the the player whose turn it is in position (row, col)
        '''

        if not self.valid_move(row, col):
            print('ERROR: INVALID MOVE')
            return
        
        self.board[row][col] = self.player()

    def winner(self, board=None):
        '''
            Dynamically checks if there is a winner, and returns the winner.
            Returns None if there is no winner.
        '''

        if board == None:
            board = self.board

        # track if a player has filled the diagnols
        diag1 = True
        diag2 = True

        for i in range(self.dimensions):
            
            # track the rows and cols
            row = True
            col = True

            for j in range(self.dimensions):
                
                # check for empty spaces
                if board[i][j] == ' ':
                    row = False
                if board[j][i] == ' ':
                    col = False
                
                # check if the current index is the same as the previous
                if j > 0 and (row or col):
                    if board[i][j] != board[i][j-1] and row:
                        row = False
                    if board[j][i] != board[j-1][i] and col:
                        col = False
                
            
            # check diagnols
            if i > 0:
                if board[i][i] != board[i-1][i-1] or board[i][i] == ' ':
                    diag1 = False
                if board[i][self.dimensions-1-i] != board[i-1][self.dimensions-1-i+1] or board[i][self.dimensions-1-i] == ' ':
                    diag2 = False
            
            if row: return board[i][0]
            if col: return board[0][i]
        
        if diag1: return board[0][0]
        if diag2: return board[0][self.dimensions-1]

        return None

    def terminal(self, board=None):
        '''
            Returns whether the game is over or not.
        '''

        if board == None:
            board = self.board
        
        if self.winner(board):
            return True

        for i in range(self.dimensions):
            for j in range(self.dimensions):
                if board[i][j] == ' ':
                    return False
        
        return True
    
    def actions(self, board):
        '''
            Returns a list of all the empty (row, col) spaces on the board.
        '''
        
        actions_ = []
        for i in range(self.dimensions):
            for j in range(self.dimensions):
                if board[i][j] == ' ':
                    actions_.append((i, j))
        
        return actions_

    def result(self, action, board):
        '''
            Returns the resulting board given an action.
        '''
        
        board_ = deepcopy(board)

        board_[action[0]][action[1]] = self.player(board_)

        return board_
    
    def utility(self, board):
        '''
            Returns the utility of a terminal board.
            If 'X' wins, returns inf.
            If 'O' wins, returns -inf.
            Returns 0 for a tie.
        '''

        winner = self.winner(board)

        return inf if winner == self.p1 else -inf if winner == self.p2 else 0
    
    def evaluation(self, board):
        '''
            Dynamically finds which player has the most winning opportunities --- dimensions length continuous openings.
            Returns the difference between the # of openings for x and o. Will return a positive if x has more, negative if o has more, 0 if tie.
        '''

        # track the # of openings for each player
        x = 0
        o = 0

        # track the number of spots/potential spots each player has in the diagnols
        x_diag1 = 0
        o_diag1 = 0
        x_diag2 = 0
        o_diag2 = 0

        for i in range(self.dimensions):

            # check diagnols
            if board[i][i] == self.p1:
                x_diag1 += 1
            elif board[i][i] == self.p2:
                o_diag1 += 1
            else:
                x_diag1 += 1
                o_diag1 += 1
            
            if board[i][self.dimensions-1-i] == self.p1:
                x_diag2 += 1
            elif board[i][self.dimensions-1-i] == self.p2:
                o_diag2 += 1
            else:
                x_diag2 += 1
                o_diag2 += 1
            
            # track rows and cols
            row_x = 0
            row_o = 0
            col_x = 0
            col_o = 0

            for j in range(self.dimensions):

                # check row
                if board[i][j] == self.p1:
                    row_x += 1
                elif board[i][j] == self.p2:
                    row_o += 1
                else:
                    row_x += 1
                    row_o += 1
                
                # check col
                if board[j][i] == self.p1:
                    col_x += 1
                elif board[j][i] == self.p2:
                    col_o += 1
                else:
                    col_x += 1
                    col_o += 1
            
            if row_x == self.dimensions: x += 1
            if row_o == self.dimensions: o += 1
            if col_x == self.dimensions: x += 1
            if col_o == self.dimensions: o += 1
        
        if x_diag1 == self.dimensions: x += 1
        if o_diag1 == self.dimensions: o += 1
        if x_diag2 == self.dimensions: x += 1
        if o_diag2 == self.dimensions: o += 1

        return x - o
    
    def minimax(self):
        '''
            Returns the optimal move of the current player. Implements alpha-beta pruning and depth limited search.
        '''

        # if game is over, return None
        if self.terminal(self.board):
            return None
        
        # if  p1('X') turn, we want to maximize alpha
        if self.player() == self.p1:
            # set alpha to the minimum value, we want to maximize this to get the best action
            alpha = -inf

            # loop through all possible actions
            for action in self.actions(self.board):

                # find the best outcome for the opponent, given the resulting board of the current action
                v = self.min_value(self.result(action, self.board), alpha, self.depth)

                # if this outcome is better than our current best, set alpha to this outcome and best_action to this action
                if v > alpha:
                    alpha = v
                    best_action = action
        
        # else player is p2('O'), we want to minimize beta
        else:
            # set beta to the maximum value, we want to minimize this to get the best action
            beta = inf

            # loop through actions
            for action in self.actions(self.board):

                # find the best outcome for the opponent, given the resulting board of the current action
                v = self.max_value(self.result(action, self.board), beta, self.depth)

                # if this outcome is better than our current best, set beta to this outcome and best_action to this action
                if v < beta:
                    beta = v
                    best_action = action
        
        return best_action
    
    def max_value(self, board, beta, depth):
        '''
            Returns the maximum outcome of the current board. 
            Called by the minimizing player, so we take in beta to be able to prune this branch if the max we find is higher than the beta.
        '''

        # if game is over, return utility
        if self.terminal(board):
            return self.utility(board)
        
        # if depth is reached, return evaluation of current board
        if depth == 0:
            return self.evaluation(board)
        
        # set alpha to the minimum value, we want to maximize this
        alpha = -inf

        # loop through actions
        for action in self.actions(board):
            
            # set alpha to the max of the current alpha, and the best outcome of the other player given the current action and decrement depth to account for this iteration
            alpha = max(alpha, self.min_value(self.result(action, board), alpha, depth - 1))

            # if the alpha we found is greater than or equal to the beta passed in, then there is already a better outcome for the minimizing player, so we can prune this branch
            if alpha >= beta:
                break

        return alpha
    
    def min_value(self, board, alpha, depth):
        '''
            Returns the maximum outcome of the current board. 
            Called by the minimizing player, so we take in beta to be able to prune this branch if the max we find is higher than the beta.
        '''

        # if game is over, return utility
        if self.terminal(board):
            return self.utility(board)
        
        # if depth is reached, return evaluation of current board
        if depth == 0:
            return self.evaluation(board)
        
        # set beta to the max value, we want to minimize this
        beta = inf

        # loop through actions
        for action in self.actions(board):

            # set beta to the min of the current beta, and the best outcome of the other player given the current action and decrement depth to account for this iteration
            beta = min(beta, self.max_value(self.result(action, board), beta, depth - 1))

            # if the beta we found is less than or equal to the alpha passed in, then there is already a better outcome for the maximizing player, so we can prune this branch
            if beta <= alpha:
                break

        return beta

        
