from ttt import *
import sys

board = 3
depth = 10
if len(sys.argv) > 1:
    try:
        board = int(sys.argv[1])
    except:
        raise Exception("Please enter a digit for the size of the board.")
    if len(sys.argv) > 2:
        try:
            depth = int(sys.argv[2])
        except:
            raise Exception("Please enter a digit for the depth of the minimax algo.")

if(board < 3):
    print("Please enter a board size greater than 2.")
    sys.exit()
if (depth < 1):
    print("Please enter a depth greater than 0.")
    sys.exit()

t = ttt(board, depth)


while not t.terminal():
    row, col = t.minimax()
    t.turn(row, col)
    t.print_board()

    if t.terminal(): 
        t.print_board()
        break

    while True:
        while True:
            try:
                row = int(input('row: '))
                break
            except:
                print("Please enter a digit for the row.")

        while True:
            try:
                col = int(input('col: '))
                break
            except:
                print("Please enter a digit for the col.")
        if not t.valid_move(row, col):
            print("Invalid, try again.")  
            continue  
        
        break

    t.turn(row, col)
    t.print_board
    
if t.winner() == 'X' or t.winner() == 'O':
    print(f"{t.winner()} Wins!")
else:
    print("Tie!")