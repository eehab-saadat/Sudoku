# include <string>
# ifndef GAME_FUNCTIONS
# define GAME_FUNCTIONS

void writeToFile(std::string, int [][9]);
void generatePuzzle(int [][9]); 
void initBoard(int [][9], int [][9], int [][9]); 
void displayBoard(int [][9]);
void initGame(int [][9]);
void newGame(int [][9], int [][9], int [][9]);
void saveGame(int [][9], int [][9], int [][9], int); 
bool loadGame(int [][9], int [][9], int [][9], int);  
bool isValid(const int [][9], const int &, const int &);
bool isWin(const int [][9], const int [][9]);
char menueScreen();
bool loadingScreen(int [][9], int [][9], int [][9]);
bool savingScreen(int [][9], int [][9], int [][9]);
void displayGameScreen(int [][9], int [][9], const int &, const int &);
void navigate(const int &, int &, int &, int &, int &); 

# endif
