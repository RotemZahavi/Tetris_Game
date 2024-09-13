#ifndef _TETRISGAME_H
#define _TETRISGAME_H
#include "player.h"
#include "computer.h"
#include "humanPlayer.h"

class TetrisGame
{
	bool isPaused;
	bool stopGame;
public:
	TetrisGame() : isPaused(false), stopGame(false) {} 
	void printMenu();
	int run(Player* player1, Player* player2, bool withColor);
	void printInstruction() const;
	void chooseCompLevel(Player* comp, int numPlayer) const;
	void setColor(int color) const;
	void resetColor() const;
	void displayIntro() const;
	bool ifColor() const;
};

#endif