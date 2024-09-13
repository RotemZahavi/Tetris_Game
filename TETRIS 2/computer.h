#ifndef _COMPUTER_H
#define _COMPUTER_H

#include "player.h"
#include <vector>

class Computer : public Player
{
	int index = 0;
	std::vector<int> moveArray;
	Point bestPos[GameConfig::SHAPE_SIZE];
	char computerLevel = 'a';

public:
	Computer();
	~Computer() override;
	void move(GameConfig::eKeys key, bool& isPointBlocked);
	void findBestMove(int& rotations);
	void movebyStep();
	void makeMoveArray(int& rotations);
	void init(int offset, bool color);
	void initShape(bool color);
	void setLevel(char level);
};

#endif