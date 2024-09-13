#include "tetrisGame.h"
#include "gameConfig.h"
#include "shape.h"
#include "general.h"
#include "computer.h"
#include "humanPlayer.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

// Display the menu options and handle user input
void TetrisGame::printMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Player* player1 = nullptr, * player2 = nullptr;
	hideCursor();
	int numRun=0;
	int currKeyPressed = 0;
	bool withColor = true;

	while (!stopGame) //if no player has yet lost
	{
		currKeyPressed = 0;
		system("cls");
		if (!isPaused)
			displayIntro();
		std::cout << " ** MENU ** " << std::endl;
		std::cout << "(1) Start a new game- Human vs Human" << std::endl;
		std::cout << "(2) Start a new game - Human vs Computer" << std::endl;
		std::cout << "(3) Start a new game - Computer vs Computer" << std::endl;
		if (isPaused && numRun!=1)
			std::cout << "(4) Continue a paused game" << std::endl;
		std::cout << "(8) Present instructions and keys" << std::endl;
		std::cout << "(9) EXIT" << std::endl;
		std::cout << "\nChoose an option: ";

		while (currKeyPressed == 0)
		{
			currKeyPressed = _getch();

			switch (currKeyPressed)
			{
			case '1':
				system("cls");
				withColor = ifColor();
				player1 = new HumanPlayer;
				player2 = new HumanPlayer;
				player1->init(GameConfig::OFFSET_0, withColor);
				player2->init(GameConfig::OFFSET, withColor);
				numRun = run(player1, player2, withColor); //starts a new game with initialized players
				break;
			case '2':
				system("cls");
				withColor = ifColor();
				player1 = new HumanPlayer;
				player2 = new Computer;
				chooseCompLevel(player2,2);
				player1->init(GameConfig::OFFSET_0, withColor);
				player2->init(GameConfig::OFFSET, withColor); 
				numRun = run(player1, player2, withColor); //starts a new game with initialized players
				break;
			case '3':
				system("cls");
				withColor = ifColor();
				player1 = new Computer;
				player2 = new Computer;
				chooseCompLevel(player1, 1);
				chooseCompLevel(player2, 2);
				player1->init(GameConfig::OFFSET_0, withColor);
				player2->init(GameConfig::OFFSET, withColor);
				numRun = run(player1, player2, withColor); //starts a new game with initialized players
				break;
			case '4':
				system("cls");
				numRun = run(player1, player2, withColor); //continue the previus game
				break;
			case '8':
				system("cls");
				printInstruction();
				currKeyPressed = _getch();  
				break;
			case '9':
				system("cls");
				std::cout << "Thank you for playing our game!\nHope to see you soon (:";
				stopGame = true;
				break;
			default:
				currKeyPressed = 0;
			}
		}
	}
	delete player1;
	delete player2;
}

//Prints instructions for playing Tetris, including game rules and controls
void TetrisGame::printInstruction() const
{
	std::cout << "Welcome to Tetris!\n\n";

	std::cout << "Tetris is a classic and iconic puzzle game that challenges players to manipulate falling "
		"tetrominoes (geometric shapes composed of four square blocks each) to create complete rows.\n\n";

	std::cout << "The goal of Tetris is to prevent the tetrominoes from stacking up to the top of the playfield. "
		"Players must strategically move, rotate, and drop tetrominoes to create horizontal lines, "
		"which will then disappear, earning points.\n\n";

	std::cout << "Controls:\n";
	std::cout << " - Move Left: 'a' or 'A' (Left Player), 'j' or 'J' (Right Player)\n";
	std::cout << " - Move Right: 'd' or 'D' (Left Player), 'l' (small L) or 'L' (Right Player)\n";
	std::cout << " - Rotate Clockwise: 's' or 'S' (Left Player), 'k' or 'K' (Right Player)\n";
	std::cout << " - Rotate Counterclockwise: 'w' or 'W' (Left Player), 'i' or 'I' (uppercase i) (Right Player)\n";
	std::cout << " - Drop: 'x' or 'X' (Left Player), 'm' or 'M' (Right Player)\n";
	std::cout << " - Pause: Press 'ESC'\n\n";

	std::cout << "The game continues until a player's tetromino reaches the top of the playfield. The winner is the "
		"player who avoids reaching the top for as long as possible.\n\n";

	std::cout << "Good luck and have fun playing Tetris!\n\n";

	std::cout << "Press enter to return to the menu.\n\n";
}

//Manages the gameplay loop, handles player movements, and checks for game over conditions
int TetrisGame::run(Player* player1, Player* player2, bool withColor)
{
	GameConfig game;
	game.drawBoards();
	player1->drawBoard();
	player2->drawBoard();

	player1->drawShape();
	player2->drawShape();
	

	while (!stopGame) //if no player has yet lost
	{
		int keyPressed[2] = { 0, 0 };

		for (int i = 0; i < GameConfig::KBHIT_ROUNDS && stopGame == false; i++)
		{
			if (_kbhit())
			{
				int currKeyPressed = _getch();
				if (currKeyPressed == (int)GameConfig::eKeys::ESC)
				{
					isPaused = true;
					system("cls");
					return 0;
				}
				if (player1->isMyKey(currKeyPressed))
					keyPressed[0] = currKeyPressed;
				if (player2->isMyKey(currKeyPressed))
					keyPressed[1] = currKeyPressed;
			}
			Sleep(30);
		}
	
		bool isPoint1Blocked = false;
		bool isPoint2Blocked = false;

		if (!stopGame) //if no player has yet lost
		{	
			player1->move((GameConfig::eKeys)keyPressed[0], isPoint1Blocked);
			player2->move((GameConfig::eKeys)keyPressed[1], isPoint2Blocked);
		}
		if (isPoint1Blocked)
		{
			player1->changeScore();
			player1->drawBoard();
			player1->initShape(withColor);
			
			if (player1->didIlose()) //if the top shape of player 1 has hit the upper border
			{
				player2->printWinner();
				while (true)
				{
					if (_kbhit())
					{
						system("cls");
						return 1;
					}
				}
			}
		}

		if (isPoint2Blocked) //if the top shape of player 2 has hit the upper border
		{
			player2->changeScore();
			player2->drawBoard();
			player2->initShape(withColor);

			if (player2->didIlose())
			{
				player1->printWinner();
				while (true)
				{
					if (_kbhit())
					{
						system("cls");
						return 1;
					}
				}
			}
		}
	}
}

//Prompts the user to select the difficulty level for a computer player
void TetrisGame::chooseCompLevel(Player* comp, int numPlayer) const
{
	if(numPlayer==1)
		std::cout << "Player 1- ";
	else
		std::cout << "Player 2- ";

	std::cout << "Please select the game level of the computer for: " << std::endl;
	std::cout << "(a) Best " << std::endl;
	std::cout << "(b) Good " << std::endl;
	std::cout << "(c) Novice " << std::endl;

	char levelKey = _getch();
	system("cls");
	Computer* computer = dynamic_cast<Computer*>(comp);
	if (computer)
		computer->setLevel(levelKey);
}

// Function to set console text color
void TetrisGame::setColor(int color) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to clear console text color
void TetrisGame::resetColor() const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//Displays an introduction to the Tetris game with a countdown and a colorful animation
void TetrisGame::displayIntro() const
{

	std::cout << "=========================================================================\n";
	std::cout << "|           *** WELCOME TO ROMI'S AND ROTEM'S TETRIS GAME! ***          |\n";
	std::cout << "=========================================================================\n\n";

	// Countdown
	for (int i = 3; i > 0; --i) {
		std::cout << "Starting in " << i << "...\n";
		this_thread::sleep_for(chrono::seconds(1));
	}

	system("CLS");

	// Tetris animation with blinking colors
	for (int i = 0; i < 10; ++i)
	{
		system("CLS");

		// Get console width for centering
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		int columns;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

		// Calculate center position
		int centerPosition = (columns - 50) / 2;

		// Blinking effect for each letter
		if (i % 2 == 0) {
			setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set text color to bright green
		}
		else {
			resetColor(); // Reset text color to default
		}
		cout << string(centerPosition, ' ') << "TTTTTT  EEEEE    TTTTTTT  RRRRR    III   SSSSS\n";
		resetColor(); // Reset text color to default

		if (i % 2 == 0) {
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Set text color to bright red
		}
		else {
			resetColor(); // Reset text color to default
		}
		cout << string(centerPosition, ' ') << "  T     E           T     R    R    I    S     \n";
		resetColor(); // Reset text color to default

		if (i % 2 == 0) {
			setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Set text color to bright blue
		}
		else {
			resetColor(); // Reset text color to default
		}
		cout << string(centerPosition, ' ') << "  T     EEEE        T     RRRRR     I     SSS  \n";
		resetColor(); // Reset text color to default

		if (i % 2 == 0) {
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Set text color to bright red
		}
		else {
			resetColor(); // Reset text color to default
		}
		cout << string(centerPosition, ' ') << "  T     E           T     R R       I         S \n";
		resetColor(); // Reset text color to default

		if (i % 2 == 0) {
			setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set text color to bright green
		}
		else {
			resetColor(); // Reset text color to default
		}
		cout << string(centerPosition, ' ') << "  T     EEEE        T     R  RR    III    SSSSS \n";
		resetColor(); // Reset text color to default

		this_thread::sleep_for(chrono::milliseconds(300));
	}

	// Clear screen
	system("CLS");
}

//Asks the player if they want to play with colors and returns the corresponding choice
bool TetrisGame::ifColor() const
{
	char key;
	std::cout << "Do you want to play with colors? " << endl;
	std::cout << "1. YES" << endl << "2. NO" << endl;
	key = _getch();
	if (key == '1')
	{
		system("cls");
		return true;
	}
	else if (key == '2')
	{
		system("cls");
		return false;
	}
}