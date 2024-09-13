#ifndef __PLAYER_H
#define __PLAYER_H

#include "shape.h"
#include "board.h"
#include "general.h"

class Player
{
protected:
	Shape shape;
	Board board;
	int offset;
	int score;

public:
	Player();
	virtual ~Player();
	virtual void init(int offset, bool color);
	virtual void initShape(bool color);
	void initBoard();
	void drawShape() const;
	void drawBoard() const;
	bool isMyKey(int& key) const;
	void changeToLower(int& key) const;
	virtual void move(GameConfig::eKeys key, bool& isPointBlocked);
	bool didIlose() const;
	void printWinner() const;
	void changeScore();
	void printScore() const;
	int getOffset() const;
};
#endif 