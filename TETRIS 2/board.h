#ifndef _BOARD
#define _BOARD
#include "gameConfig.h"
#include "point.h"

class Point;

class Board
{
    int boardArr[GameConfig::GAME_HEIGHT + 2][GameConfig::GAME_WIDTH + 2];
    int colorBoard[GameConfig::GAME_HEIGHT + 2][GameConfig::GAME_WIDTH + 2];

public:
    Board();

    // Check if a specific point on the board is empty
    bool isEmpty(int x, int y) const;

    // Put a point on the board
    void putPointInBoard(int x, int y, int color);

    void deletePointInBoard(int x, int y);

    // Initialize the board with borders and empty cells
    void init();

    // Delete a full row and move the upper rows down
    void deleteRow(int& rowInd);

    // Check if a row is full
    bool isRowFull(int& rowInd) const;

    // Draw the board with a given offset
    void draw(int offset) const;

    // Check if the player has lost (top row is filled)
    bool didIlose() const;

    //Count how many rows are full in the board
    const int countFullRows() const;

    //Find the highest shape in the board
    void findHighiestPoint(Point* pos) const;
};

#endif