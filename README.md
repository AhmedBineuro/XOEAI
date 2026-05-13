# X-O Game

This is a simple command line implementation of the classic TicTacToe game. The board is encoded in a single 18-bit bitset where every 2 bits represent a cell with a state of Empty, X, or O. The winning patterns are also encoded in 18-bit bitsets.

The game features a simple AI using the MinMax algorithm.

- The AI has 5 difficulty levels, with levels 3 and above being nearly impossible to beat.

## Installing and Running

### Requirements

- A C++ compiler
- Makefile

### Helpful Commands

- `make g++` — compile and run the game for G++
- `make clang` — compile and run the game for Clang 
- `make testG++` — compile and run the test suite for G++
- `make testClang` — compile and run the test suite for Clang
- `make runTest` — run the compiled test suite
- `make run` — run the compiled game  

- `make clean` — delete the generated executables

## Note

Previously, I was planning to develop a handful of AI models on top of this game for learning purposes. Eventually, I chose to implement only one here, and reserve the others for more complex projects where the benefits of each model could be better showcased.

Maybe I will add a graphical application version in the future, but for now this is sufficient.
