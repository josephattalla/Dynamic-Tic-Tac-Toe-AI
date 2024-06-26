from ttt import *
import sys
import time
import csv
import random

# start timer
start_time = time.time()

# get board size and depth
board = 3
depth = 3
if len(sys.argv) > 1:
    board = int(sys.argv[1])
    if len(sys.argv) > 2:
        depth = int(sys.argv[2])

# instantiate ttt object
t = ttt(board, depth)

# play game
while not t.terminal():

    # minimax goes first, is X
    row, col = t.minimax()
    t.turn(row, col)

    if (not t.terminal()):
        # choose random action to take
        row, col = random.choice(t.actions(t.board))
        t.turn(row, col)

# end time, get elapsed time
end_time = time.time()
elapsed_time = end_time - start_time

# minimax won if X won
winner = t.winner()
win = 1 if winner == 'X' else 0

# write board size, depth, elapsed time, if minimax won to csv
with open("python.csv", "a", newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow([board, depth, elapsed_time, win])