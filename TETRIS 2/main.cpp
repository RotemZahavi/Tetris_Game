#include <windows.h> 
#include <conio.h>
#include "gameConfig.h"
#include "general.h"
#include "tetrisGame.h"
#include "player.h"
#include "computer.h"
#include "humanPlayer.h"


void main()
{
	TetrisGame game;
	game.printMenu();
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
}


