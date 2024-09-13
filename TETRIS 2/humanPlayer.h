#ifndef __HUMAN_PLAYER_H
#define __HUMAN_PLAYER_H
#include "player.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

class HumanPlayer : public Player
{
public:
	~HumanPlayer() override;
};

#endif