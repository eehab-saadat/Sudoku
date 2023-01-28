
# Sudoku in C++ with Graphics.h

This program is an implementation of the popular game Sudoku in C++, using the [Graphics.h BGI](https://home.cs.colorado.edu/~main/bgi/doc/) library. The program is run on the Turbo C++ or TDM-GCC-32 compiler. 

This project was made as an end-of-semester project for the *Programming Fundamentals (CS-1002)* course offered at *[Foundation for Advancement in Science & Technology - National University of Computing & Emerging Sciences (FAST-NUCES)](www.nu.edu.pk), Lahore, Pakistan*. 

## Game Instructions
1. Navigate to `./output/main.exe` and click to run the program.
2. Select your desired game mode. You can either create a new game or load a previously saved game (if any). Press <kbd>N</kbd> to create a new game or <kbd>L</kbd> to load a saved game. Press <kbd>Esc</kbd> to end program.
3.  The program will display a 9x9 grid, representing the Sudoku puzzle.
4.  Use the arrow keys (<kbd>&uarr;</kbd>, <kbd>&larr;</kbd>, <kbd>&darr;</kbd> & <kbd>&rarr;</kbd>) to navigate the grid and hence select a cell. The selected cell will be marked by the yellow square cursor.
5.  Game hints (represented by white) are locked places and hence cannot be overwritten/edited. Blank spaces however can be filled in with numbers ranging from 1-9 as per Sudoku rules.
6.  Use the number keys (<kbd>1</kbd> - <kbd>9</kbd>) to fill in the selected cell with the corresponding number.
7.  The program will check for errors in the puzzle after each entry and display the entered digit as red if caught in violation of Sudoku rules, if not, then with green.
8.  The user wins if the puzzle is completed without any violation and is congratulated with a victory message. 
9.  The user may press <kbd>M</kbd> to return to main menu, press <kbd>S</kbd> to save the current puzzle progress into any slot ranging from `1` to `3` or press <kbd>Esc</kbd> to end the program during any time of play.

![sudoku-demo](https://media.giphy.com/media/Za3dugbKe1DPJJ6WsE/giphy.gif)

## Setting Up

Please note that the Graphics.h library is an old library and only works on older versions of C++ compilers like Turbo C++ or TDM-GCC-32, it is not supported by newer versions like Visual Studio.

However, the following steps maybe followed to setup graphics.h and compile the program:
1.  Download the current repository on to your local system.
2.  Download and install the Turbo C++ or TDM-GCC-32 compiler on your computer. This project was compiled using the latter one in Visual Studio Code. For setup tutorial, click [here](https://www.youtube.com/watch?v=J0_vt-7Ok6U&t=2192s).
3. Download the Graphics.h and WinBGIM (Windows Borland Graphics Interface [BGI]) library files and copy them to the include folder of your compiler installation directory. This project utilized resources from [@SagarGaniga/Graphics-Library](https://github.com/SagarGaniga/Graphics-Library).
4. Once the compiler and linker are completely setup successfully, compile the program to generate the executable file. The program is now ready to run.

## How does it work?
### Graphics & Functions
The program utilizes analytical geometry and program logic to draw graphical elements using the functionalities provided by the graphics.h library. 

All other custom utility functions and procedures are placed in the `game_functions.cpp` (`./src/modules/`) file linked to the `game_functions.h` header file used in the `main.cpp`.

### Puzzle Generation
There are 5 types of methods utilized to generate a new puzzle every single time. The program generates a new puzzle from the previous (or default) solvable Sudoku solution stored inside the `solution.txt` (`./output/txt/solutions/`). The procedure
```cpp
void generatePuzzle(int [][9])
```
accepts the contents of `solution.txt` as a 2D 9x9 integer array and runs 5 scrambling algorithms to generate a new puzzle every time, ensuring complete uniqueness, namely: interchanging digits, interchanging rows, interchanging columns, interchanging rows in their set of three and interchanging columns in their set of three. The newly generated puzzle solution is stored back into the `solution.txt` file for future use. 

The puzzle is then generated using this new unique solution by randomizing game hints using the following function: 
```cpp
void  initBoard(int [][9], int [][9], int [][9])
```
which sets up all the game related 2D 9x9 integer arrays: `ans [][9]` (for solution), `locked [][9]` (for locked hints) and `board [][9]` (for current game board progress).

### Saving & Loading
Saving and loading is done by the following set of procedures and functions respectively:
```cpp
void  saveGame(int [][9], int [][9], int [][9], int);
bool  loadGame(int [][9], int [][9], int [][9], int);
```
which save/load the desired game into/from the selected game slot by user by saving/fetching all the related game information, i.e. current game progress, locked game hints and the game solution, as individual text files stored in individual sub-directories (`games`, `locks` & `solutions`) inside `./output/txt/`. 

## Contact

If you have any issues running the program or have suggestions for improvements, please contact me at eehab.saadat@gmail.com.
