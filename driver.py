from ttt import *
import sys
import time
import csv

start_time = time.time()

board = 3
depth = 3
if len(sys.argv) > 1:
    board = int(sys.argv[1])
    if len(sys.argv) > 2:
        depth = int(sys.argv[2])

t = ttt(board, depth)


while not t.terminal():
    row, col = t.minimax()
    t.turn(row, col)

end_time = time.time()
elapsed_time = end_time - start_time

with open("python.csv", "a", newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow([board, depth, elapsed_time])