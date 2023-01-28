// Header Files
#include <game_functions.h> // exists in /include/game_functions.h
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <graphics.h>

// Standard Namespace
using namespace std;

// Procedure for Matrix to File Writing
void writeToFile(string filepath, int arr[][9]) {
	ofstream fileObj(filepath);
	if (fileObj.fail()) cout << "File Open Failed." << endl;
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			fileObj << arr[r][c]; 
			if (c != 8) fileObj << " ";
		}
		if (r != 8) fileObj << endl;
	}
	fileObj.close();
}

// Proceudure For Reading From File To Matrix
void readFromFile(string filepath, int arr[][9]) {
	ifstream fileObj(filepath);
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			fileObj >> arr[r][c];
		}
	}
	fileObj.close();
}

// Element Validation Function
bool isValid(const int board[][9], const int &row, const int &col) {
	// Checking Inside Column
	for (int r = 0; r < 9; r++) {
	    if (board[r][col] == board[row][col] && row != r) {
	    	return false;	
		}
	}
	// Checking Inside Row
	for (int c = 0; c < 9; c++) {
	    if (board[row][c] == board[row][col] && col != c) {
			return false;
		}
	}
	// Checking Inside The Grid
	int rGridStart = row - row % 3;
	for (int i = rGridStart; i < rGridStart + 3; i++) {
	    int cGridStart = col - col % 3;
	    for (int j = cGridStart; j < cGridStart + 3; j++) {
	        if (board[i][j] == board[row][col] && !(i == row && j == col)) {
				return false;
	    	}
		}
	}

	return true; // Return True If All Checks Fullfilled
}

// Checking If User Won
bool isWin(const int ans[][9], const int board[][9]) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (board[r][c] == 0) return false;
			if (ans[r][c] != board[r][c]) return false;
		}
	}
	return true;
}

// Procedure to Generate Unique Puzzle
void generatePuzzle(int ans[][9]) {
	// Interchanging Digits
	int arr[9]; // Temporary Array
	for (int i = 0; i < 9; i++) { // Populating The Array
		int j;
		do { 
			arr[i] = rand() % 9 + 1; // Random Elem Generation w/ Range 1 - 9 (Valid Sudoku Digits)
			for (j = 0; j < i && arr[i] != arr[j]; j++); 
		} while (j != i); // Ensuring No Duplication Within Array
	}
	// Traversing Through The Whole Board
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			// Replacing All Occurences Of A Digit With Its Randomized Counterpart
			ans[r][c] = arr[ans[r][c]-1]; 
		}
	}
	
	// For Swapping Both Columns and Rows Within Their Sets of Three
	for (int x = 1; x <= 2; x++) {
		// Swapping Rows & Columns in Their Set of Three
		int gridPrinciple = rand() % 3; // Choosing 9*3 / 3*9 Main Grid Col/Row
		int sub1 = rand() % 3;
		int sub2;
		do { // Ensuring Cols/Rows Chosen Are Not The Same
			sub2 = rand() % 3;
		} while (sub1 == sub2); // Till They're Not The Same
		// Calculating Actual Positions
		int principle1 =  gridPrinciple * 3 + sub1; 
		int principle2 =  gridPrinciple * 3 + sub2; 
		int temp; // Temp Variable for Swapping
		if (x == 1) {
			// Swapping Columns
			for (int i = 0; i < 9; i++) {
				temp = ans[principle1][i];
				ans[principle1][i] = ans[principle2][i];
				ans[principle2][i] = temp;
			}
		}
		else {
			// Swapping Rows
			for (int i = 0; i < 9; i++) {
				temp = ans[i][principle1];
				ans[i][principle1] = ans[i][principle2];
				ans[i][principle2] = temp;
			}
		}
	}

	// For Swapping Whole 9*3 / 3*9 Cols and Rows
	for (int x = 1; x <=2; x++) {
		int sub1 = rand() % 3; // Choosing 9*3 / 3*9 Main Grid Col/Row
		int sub2;
		do { // Ensuring Cols/Rows Chosen Are Not The Same
			sub2 = rand() % 3;
		} while (sub1 == sub2); // Till They're Not The Same
		// For Swapping Grid Rows
		if (x == 1) {
			int temp; // Swap Variable
			// Calculating Actual Locations
			int principle1 = sub1 * 3; 
			int principle2 = sub2 * 3;
			// Swapping
			for (int i = principle1, k = principle2; i < principle1+3 && k < principle2+3; i++, k++) {
				for (int j = 0; j < 9; j++) {
					temp = ans[i][j];
					ans[i][j] = ans[k][j];
					ans[k][j] = temp;
				}
			}
		}
		// For Swapping Grid Columns
		else {
			int temp; // Swap Variable
			// Calculating Actual Locations
			int principle1 = sub1 * 3; 
			int principle2 = sub2 * 3;
			// Swapping
			for (int i = principle1, k = principle2; i < principle1+3 && k < principle2+3; i++, k++) {
				for (int j = 0; j < 9; j++) {
					temp = ans[j][i];
					ans[j][i] = ans[j][k];
					ans[j][k] = temp;
				}
			}
		}
	}
}

// Procedure to Initialize Board
void initBoard(int ans[][9], int board[][9], int locked[][9]) {
	// Hints Generator
	for (int i = 1; i <= 25; i++) {
		int row = rand() % 9;
		int col = rand() % 9;
		if (locked[row][col] == 0) {
			locked[row][col] = ans[row][col];
			board[row][col] = ans[row][col];
		} 
		else i--; // Ensure Completely Unique Hints
	}
}

// Proceudre To Display Board
void displayBoard(int board[][9]) {
	// Board Generator
	cout << string(25, '-') << endl;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (col % 3 == 0) cout << "| ";
			if (board[row][col] != 0) cout << board[row][col] << " ";
			else cout << "_ ";
			if (col == 8) cout << "|";
		}
		if (row % 3 == 2) cout << endl << string(25, '-') << endl; 
		else cout << endl;
	}
}

// Procedure To Initialize Game
void initGame(int ans[][9]) {
	// Reading Solution Into Answer Array
	string solutionfile = "txt/solutions/solution.txt";
	readFromFile(solutionfile, ans);
}

// Procedure for Generating New Game
void newGame(int ans[][9], int board[][9], int locked[][9]) {
	generatePuzzle(ans); // Generating Puzzle
	initBoard(ans, board, locked); // Initializing Hints and Game Board
	string solutionfile = "txt/solutions/solution.txt";
	writeToFile(solutionfile, ans);
} 

// Saving Game
void saveGame(int ans[][9], int board[][9], int locked[][9], int gameNum) {
	string gamefile, solutionfile, lockedfile;
	if (gameNum == 1) {
		gamefile = "txt/games/game1.txt";
		solutionfile = "txt/solutions/solution1.txt";
		lockedfile = "txt/locks/locked1.txt";
	}
	else if (gameNum == 2) {
		gamefile = "txt/games/game2.txt";
		solutionfile = "txt/solutions/solution2.txt";
		lockedfile = "txt/locks/locked2.txt";
	}
	else {
		gamefile = "txt/games/game3.txt";
		solutionfile = "txt/solutions/solution3.txt";
		lockedfile = "txt/locks/locked3.txt";
	}

	writeToFile(gamefile, board); // Save Current Board
	writeToFile(solutionfile, ans); // Save The Solution
	writeToFile(lockedfile, locked); // Save The Locked Positions
}

// Load Game
bool loadGame(int ans[][9], int board[][9], int locked[][9], int gameNum) {
	string gamefile, solutionfile, lockedfile;
	if (gameNum == 1) {
		gamefile = "txt/games/game1.txt";
		solutionfile = "txt/solutions/solution1.txt";
		lockedfile = "txt/locks/locked1.txt";
	}
	else if (gameNum == 2) {
		gamefile = "txt/games/game2.txt";
		solutionfile = "txt/solutions/solution2.txt";
		lockedfile = "txt/locks/locked2.txt";
	}
	else {
		gamefile = "txt/games/game3.txt";
		solutionfile = "txt/solutions/solution3.txt";
		lockedfile = "txt/locks/locked3.txt";
	}

	bool notEmpty = false; // Checking If File Empty Or Not
	ifstream GameFile(gamefile);
	for (int r = 0; r < 9 && !GameFile.eof(); r++) {
		if (r == 8) notEmpty = true;
		for (int c = 0; c < 9; c++) {
			GameFile >> board[r][c]; // Loading Board
		}
	}
	GameFile.close();
	if (!notEmpty) return notEmpty;
	readFromFile(solutionfile, ans); // Loading Solution
	readFromFile(lockedfile, locked); // Loading Locks
	return notEmpty;
}

// Menue Screen 
char menueScreen() {
	cleardevice();
    // Getting Centeral Coordinates
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);
    
    // Drawing A Window Border
    setcolor(YELLOW); 
    setlinestyle(0,0,4);
    line(0,2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    // Displaying Game Title
    setcolor(LIGHTBLUE); 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU")/2), 20, "SUDOKU");

	// Printing Game Menue
	setcolor(LIGHTBLUE);
	settextstyle(0, HORIZ_DIR, 2);
	outtextxy(midx - textwidth("WELCOME TO SUDOKU!")/2, midy-50, "WELCOME TO SUDOKU!");
	outtextxy(midx - textwidth("Press N for New Game")/2, midy-25, "Press N for New Game");
	outtextxy(midx - textwidth("Press L to Load Game")/2, midy, "Press L to Load Game");
	outtextxy(midx - textwidth("Press Esc to Exit Game")/2, midy+25, "Press Esc to Exit Game");

	// Wait for Input
	char key = getch();
	while ((!(int)key == 27) && !((key == 'n') && !((key == 'l')))) {
		key = getch();
	}
	return key;
}

// Loading Screen
bool loadingScreen(int ans[][9], int board[][9], int locked[][9]) {
	cleardevice();
    // Getting Centeral Coordinates
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);
    
    // Drawing A Window Border
    setcolor(YELLOW); 
    setlinestyle(0,0,4);
    line(0,2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    // Displaying Game Title
    setcolor(LIGHTBLUE); 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU")/2), 20, "SUDOKU");

	// Printing Save Menue
	setcolor(LIGHTBLUE);
	settextstyle(0, HORIZ_DIR, 2);
	outtextxy(midx - textwidth("WHERE TO LOAD FROM?")/2, midy-50, "WHERE TO LOAD FROM?");
	outtextxy(midx - textwidth("Press 1 for Game 1")/2, midy-25, "Press 1 for Game 1");
	outtextxy(midx - textwidth("Press 2 for Game 2")/2, midy, "Press 2 for Game 2");
	outtextxy(midx - textwidth("Press 3 for Game 3")/2, midy+25, "Press 3 for Game 3");

	// Wait For Input
	char key = getch();
	while (!(key == '1') && !(key == '2') && !(key == '3')) {
		key = getch();
	}

	// Load Game
	bool success = loadGame(ans, board, locked, (int)key - 48);
	if (success) outtextxy(midx - textwidth("Game Loaded Successfully!")/2, midy+50, "Game Loaded Successfully!");
	else outtextxy(midx - textwidth("No Game To Load")/2, midy+50, "No Game To Load");
	delay(2000);
	return success;
}

// Save Game
bool savingScreen(int ans[][9], int board[][9], int locked[][9]) {
	cleardevice();
    // Getting Centeral Coordinates
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);
    
    // Drawing A Window Border
    setcolor(YELLOW); 
    setlinestyle(0,0,4);
    line(0,2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    // Displaying Game Title
    setcolor(LIGHTBLUE); 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU")/2), 20, "SUDOKU");

	// Printing Save Menue
	setcolor(LIGHTBLUE);
	settextstyle(0, HORIZ_DIR, 2);
	outtextxy(midx - textwidth("WHERE TO SAVE?")/2, midy-50, "WHERE TO SAVE?");
	outtextxy(midx - textwidth("Press 1 for Game 1")/2, midy-25, "Press 1 for Game 1");
	outtextxy(midx - textwidth("Press 2 for Game 2")/2, midy, "Press 2 for Game 2");
	outtextxy(midx - textwidth("Press 3 for Game 3")/2, midy+25, "Press 3 for Game 3");

	// Wait For Input
	char key = getch();
	while (!(key == '1') && !(key == '2') && !(key == '3')) {
		key = getch();
	}
	// Save Game
	saveGame(ans, board, locked, (int)key - 48);
	outtextxy(midx - textwidth("Game Saved Successfully!")/2, midy+50, "Game Saved Successfully!");
	delay(2000);
	return true;
}

// Game Screen Function
void displayGameScreen(int board[][9], int locked[][9], const int &activex, const int &activey) {
    cleardevice();
    // Getting Centeral Coordinates
    int midx = (getmaxx() / 2);
    int midy = (getmaxy() / 2);
    
    // Drawing A Window Border
    setcolor(YELLOW); 
    setlinestyle(0,0,4);
    line(0,2, getmaxx(), 2);
    rectangle(0, 0, getmaxx(), getmaxy());

    // Displaying Game Title
    setcolor(LIGHTBLUE); 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(midx - (textwidth("SUDOKU")/2), 20, "SUDOKU");

    // Drawing The Game Grid
    int gridStartX = midx - 153;
    int gridStartY = midy - 153;
    // Total Grid Width = 306 As 306 Is Divisible By 9
    setcolor(LIGHTBLUE);
    // Drawing Horizontal Lines
    for (int i = gridStartX, count = 0; i <= gridStartX + 306; i += 34, count++) {
        if (count % 3 == 0) setlinestyle(0, 0, 3);
        else setlinestyle(0,0,0);
        line(i, gridStartY, i, gridStartY + 306);
    }  
    // Drawing Verticle Lines
    for (int i = gridStartY, count = 0; i <= gridStartY + 306; i += 34, count++) {
        if (count % 3 == 0) setlinestyle(0, 0, 3);
        else setlinestyle(0, 0, 0);
        line(gridStartX, i, gridStartX + 306, i);			
    }

    // Displaying Board Elements
    settextstyle(0, HORIZ_DIR, 3);
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
			char elem[3];
            if (board[r][c] == 0) continue;
			if (locked[r][c] != 0) {
				setcolor(WHITE);
				sprintf(elem, "%d", board[r][c]);
            	outtextxy(gridStartX + 5 + c*34, gridStartY + 8 + r*34, elem);
			}
			else if (isValid(board, r, c)) {
				setcolor(GREEN);
				sprintf(elem, "%d", board[r][c]);
            	outtextxy(gridStartX + 5 + c*34, gridStartY + 8 + r*34, elem);
				setcolor(WHITE);
			}
			else if (!isValid(board, r, c)) {
				setcolor(RED);
				sprintf(elem, "%d", board[r][c]);
            	outtextxy(gridStartX + 5 + c*34, gridStartY + 8 + r*34, elem);
				setcolor(WHITE);
			}		
		}
	}
	
	// Sidebar Text
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(10,200,"M-Menu");
	outtextxy(10,230,"S-Save");
	outtextxy(10,260,"Esc-Exit");
}

// Procedure for Navigating Cursor
void navigate(const int &keyPressed, int &activex, int &activey, int &tempx, int &tempy) {
	// Getting Grid Starting
	int gridStartX = getmaxx() / 2 - 153;
	int gridStartY = getmaxy() / 2 - 153;

	// Erase Previous Cursor Position
	if (tempx != -1) {
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		rectangle(
			gridStartX + tempx * 34 + 2, gridStartY + tempy * 34 + 2,
			gridStartX + (tempx+1) * 34 - 2, gridStartY + (tempy+1) * 34 - 2
		);
	}
	
	// Updating Variables
	if (keyPressed == 72) { // Up Arrow Pressed
		if (activey == 0) activey = 8;
		else activey--;
	}	
	else if (keyPressed == 80) { // Down Arrow Pressed
		if (activey == 8) activey = 0;
		else activey++;
	}
	else if (keyPressed == 75) { // Left Arrow Pressed
		if (activex == 0) activex = 8;
		else activex--;
	}	
	else if (keyPressed == 77) { // Right Arrow Pressed
		if (activex == 8) activex = 0;
		else activex++;
	}
	// New Cursor Position				
	setcolor(YELLOW);
	setlinestyle(0, 0, 3);
	tempx = activex;
	tempy = activey;
	rectangle(
		gridStartX + activex * 34 + 2, gridStartY + activey * 34 + 2,
		gridStartX + (activex+1) * 34 - 2, gridStartY + (activey+1) * 34 - 2 
	);	
}