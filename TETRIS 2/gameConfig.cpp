#include "gameConfig.h"
#include "general.h"
#include <iostream>
#include <Windows.h>

void GameConfig::drawBoards() const
{
    // Draw the first board
    for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
    {
        gotoxy(col, GameConfig::MIN_Y - 1);
        std::cout << "-";

        gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
        std::cout << "-";
    }

    for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
    {
        gotoxy(GameConfig::MIN_X - 1, row);
        std::cout << "|";

        gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
        std::cout << "|";
    }

    // Draw the second board with an offset
    for (int col = GameConfig::MIN_X + GameConfig::OFFSET; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X + GameConfig::OFFSET; col++)
    {
        gotoxy(col, GameConfig::MIN_Y - 1);
        std::cout << "-";

        gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
        std::cout << "-";
    }

    for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
    {
        gotoxy(GameConfig::MIN_X - 1 + GameConfig::OFFSET, row);
        std::cout << "|";

        gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X + GameConfig::OFFSET, row);
        std::cout << "|";
    }
}
