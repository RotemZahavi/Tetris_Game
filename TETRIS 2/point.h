#ifndef _POINT_H
#define _POINT_H
#include "gameConfig.h"
#include "board.h"

class Board;

class Point
{
	int x;
	int y;
	int diff_x;
	int diff_y;

public:
	void init(int x, int y);
	void draw(char ch, int offset, int backColor) const;
	void move(GameConfig::eKeys key, bool& isPointBlocked);
	int getX() const;
	int getY() const;

};

#endif