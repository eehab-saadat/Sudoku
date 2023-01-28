// Header Files
#include <game_functions.h> // exists /include/game_functions.h
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <graphics.h>

// Standard Namespace
using namespace std;

// Main Driver Function
int main() {
	// Random Seed Generator
	srand((unsigned)time(NULL));
	
	// Initializing Graphics
	int gDriver = DETECT, gMode, errorCode;
	initgraph(&gDriver, &gMode, (char*)"");
	
	// Error Checking
	errorCode = graphresult();
	if (errorCode != grOk) {
		cout << "Graphics error occured " << grapherrormsg(errorCode) << endl;
		cout << "Press any key to terminate program..." << endl;
		getch();
		exit(1);
	}

	// Main Program
	bool program = true;
	while (program) {
		// Initialize Game
		bool game = false;
		int activex = 0, activey = 0;
		int tempx = -1, tempy = -1;
		int ans[9][9] = {0}; // Solution Matrix
		int board[9][9] = {0};  // Board Matrix
		int locked[9][9] = {0}; // Locked Matrix

		// Diplay Menue Screen
		char action = menueScreen();
		if ((int)action == 27) { // If ESC is Pressed
			game = false;
			program = false;
		} 
		// Load Game
		else if(action == 'l') {
			game = loadingScreen(ans, board, locked);
			if (game) displayGameScreen(board, locked, activex, activey);
		}
		// New Game
		else if(action == 'n') {
			initGame(ans);
			newGame(ans, board, locked);
			displayGameScreen(board, locked, activex, activey);
			game = true;
		}
	
		// Game Code
		while (game) {			
			// If Key Pressed
			if (kbhit()) {
				// Fetch The Key Pressed
				int keyPress = (int)getch();	
				
				// Press Esc To Exit
				if (int(keyPress) == 27) {
					game = false;
					program = false;
				}
				// For Cursor Movement When Arrow Keys Are Pressed
				else if (keyPress == 72 || keyPress == 80 || keyPress == 75 || keyPress == 77) {
					navigate(keyPress, activex, activey, tempx, tempy);
				}
				// For Data Entry When Digits 1 - 9 Are Pressed
				else if (keyPress >= 49 && keyPress <= 57) {
					// Denies Locked Position Editing
					if (locked[activey][activex] == 0) {
						int digit = keyPress - 48;
						board[activey][activex] = digit;
						displayGameScreen(board, locked, activex, activey);	// Update Screen
					}
				}
				// Save Game
				else if (keyPress == 's') {
					game = !savingScreen(ans, board, locked);
				}
				// Escape To Main Menue
				else if (keyPress == 'm') game = false;
				
				// If wins, display win page.
				if (isWin(ans, board)) {
					char msg[40];
					int midx = getmaxx()/2;
					int midy = getmaxy()/2;
 					
					// Display Winning Window
					cleardevice();
					setcolor(GREEN);
					settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
					sprintf(msg, "%s", "CONGRATS! YOU WON!");
					outtextxy(midx - textwidth(msg)/2, midy - textheight(msg)/2 - 3, msg);				
					setcolor(WHITE);
					settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
					sprintf(msg, "%s", "Press M to go back to Main Menue.");
					outtextxy(midx - textwidth(msg)/2, midy + textheight(msg)/2 + 3, msg);
					
					// Wait For Input
					char key = getch();
					while (!((int)key == 27) && !((key == 'm'))) {
						key = getch();
					}
					// If ESC is Pressed
					if ((int)key == 27) {
						program = false;
						game = false;
					}
					// Go Back To Menue
					else game = false;
				}
			}
		}
	}
	closegraph();
	return 0;
}