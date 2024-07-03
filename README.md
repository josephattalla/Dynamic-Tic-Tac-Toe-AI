# Dynamic Tic-Tac-Toe AI Algorithm

This repository contains implementations of a variable-length Tic-Tac-Toe minimax algorithm in both C++ and Python. The AI is capable of playing Tic-Tac-Toe on boards of different sizes and utilizes the minimax algorithm for decision-making. Additionally, alpha-beta pruning and depth limitation is implemented to optimize the search process.

## Files

- `cpp/` contains the C++ code.
- `python/` contains the Python code.
- `data/` contains the bash script and drivers used to test, and the csv's storing the results.
- `analysis.ipynb` is the Jupyter Notebook used to visualize testing results.

## Usage

**Python**
```
python3 python/play.py <board size> <depth>
```

**C++**
```
g++ cpp/play.cpp cpp/ttt.cpp -o play
./play <board size> <depth>
```

## Minimax Algorithm

The minimax algorithm is used to find the best possible move to make. This is done by first choosing who is the minimizing and maximizing player. The maximizing player wants the end value of the game to be as big as possible, and the minimizing player want the end value of the game to be as small as possible. If it is the maximizing player's turn, then we want to choose the action that has the best chance of resulting in the largest end value. To do this, we explore what will happen choosing each possible action. When we explore an action, if the game hasn't ended, we are now the oppenent (minimizing player), so we choose the best possible action for the minimizing player by exploring all actions they can take. This is done iteratively until we find the value of each action the curent player can take. By doing this, we can take the action that will most likely result in the best outcome for the current player.

![image](https://github.com/josephattalla/Dynamic-Minimax/assets/121779512/b40fc2ca-dbcb-43f5-a136-43801afae68e)
Image source: https://cs50.harvard.edu/ai/2024/notes/0/

- Green is an optimizing player, red is a minimizing player
- The first state (top) has 3 possible actions
- These actions put the state into the opponents turn, the opponent is the minimizing player and when their optimal actions are taken, the end game value is the number within their triangle
- The top state chooses the max of these actions which is 9


## Optimization

If we do this for every possible board state in a 3x3 tic tac toe, we would explore around 260,000 possibilities. As the board expands, the amount of possible board states exponentially increases, significantly increasing execution time. To optimize this, I implemented 2 methods that significantly decrease how many states are explored.

1. Alpha-Beta Pruning
    - Reduces the states explored by holding the max value the maximizing player has found (alpha) and the min value the minimzing player has found (beta)
    - If the action being explored will not be better than the value that has been already found, then we stop exploring that action

    - ![](image.png) Image source: https://cs50.harvard.edu/ai/2024/notes/0/
        - The top state is the maximizing player and is the current state
        - In the first action explored (left most minimizing player) the end game value we get by minimizing the end game value of the posible actions at that state is 4, and will be the current alpha. The next action explored (middle minimizing player) we see that the minimizing player gets a 3, which is less than our alpha, 4, and from there the minimzing player could only choose a number smaller than 3 so we know that action will not result in a better outcome for the maximizing player. The last action explored (right most minimizing player) the minimzing player gets a 2, which is worse than our alpha so we can stop exploring that action.

2. Depth Limited Search
    - Alpha-beta pruning reduces runtime at each state, but there will still be many states to explore. To reduce the amount of states to explore I implemented a depth limited search. Given a certain depth, we explore that many levels down from the current state to determine the best action. By doing this we cannot get the end game value, so we estimate it using a heurstic function. The heuristic I used was the amount of winning oppurtunities available, by finding how many continuous dimension-length openings for a given player there are. The player with most winning oppurtunities is the predicted winner.

## Testing

To test the execution time and the AI's ability to make the best possible move, I created a driver for each language in which the AI plays against random moves. I did this for board sizes 3-6 and depths of 1-5, 5 times for each combination.

###### Execution Time vs Depth
![Execution Time vs Depth](plots/Execution%20Time%20vs%20Depth.png)

###### Losses vs Board Size
![Losses vs Board Size](plots/Number%20of%20losses%20per%20Board%20Size.png)

###### Losses vs Depth
![Losses vs Depth](plots/Number%20of%20losses%20per%20Depth.png)

## Results Interpretation

###### Execution Time
C++ is significantly faster as exepcted, but is only noticeable for board sizes greater than 5. It seems as board size and depth increase, execution time increases exponentially. For Python, growth of the exponential is greater.

###### Decision Making
For a board size of 3, the AI seems to be able to find the best possible action with no 0 losses. At board sizes greater than 3, the AI does worse, and at a board size of 6 the AI does the worst with 23 total losses. Additionally, depth plays a crucial role in the decision making. At a depth of 5, the AI does best with 0 losses. Depth sizes lower than 5, the AI struggles to find the best possible action as it has more guesswork to do. The AI does worst at a depth of 1 with 16 total losses, and interestingly a depth of 2 does second best with a total of 7 losses. Strangely, C++ has more losses than Python although the AI is identical. This is likely due to the fact the opponent is making random moves.
