#include "board.h"
#include "general.h"
#include <windows.h>
#include  <iostream>

Board::Board()
{
	init();
}

bool Board::isEmpty(int x, int y) const
{
	if (Board::boardArr[y][x] == 0)
		return true;
	else
		return false;
}

void Board::putPointInBoard(int x, int y, int color)
{
	boardArr[y][x] = 1;
	colorBoard[y][x] = color;
}

void Board::deletePointInBoard(int x, int y)
{
	boardArr[y][x] = 0;
	colorBoard[y][x] = (int)FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
}

void Board::init()
{
	for (int i = 0; i < GameConfig::GAME_HEIGHT+2; ++i) {
		for (int j = 0; j < GameConfig::GAME_WIDTH+2; ++j) {
			if (i == 0 || i == GameConfig::GAME_HEIGHT + 1 || j == 0 || j == GameConfig::GAME_WIDTH + 1) {
				Board::boardArr[i][j] = 1;
				Board::colorBoard[i][j] = (int)FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
			}
			else {
				Board::boardArr[i][j] = 0;
				Board::colorBoard[i][j] = (int)FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

			}
		}
	}
}

void Board::deleteRow(int& rowInd)
{
	for (int row = rowInd; row > 1; row--)
	{
		for (int col = 1; col <= GameConfig::GAME_WIDTH; col++)
		{
			boardArr[row][col] = boardArr[row - 1][col];
			colorBoard[row][col] = colorBoard[row - 1][col];

		}
	}
	for (int col = 1; col < GameConfig::GAME_WIDTH + 1; col++)
	{
		boardArr[1][col] = 0;
		colorBoard[1][col] = (int)FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
}

bool Board::isRowFull(int& rowInd) const
{
	int counter;

	for (int row = 1; row <= GameConfig::GAME_HEIGHT; row++)
	{
		counter = 0;
		for (int col = 1; col <= GameConfig::GAME_WIDTH; col++)
		{
			if (Board::boardArr[row][col] == 1)
				counter++;
		}
		if (counter == GameConfig::GAME_WIDTH)
		{
			rowInd = row;
			return true;
		}
	}
	return false;
}

void Board::draw(int offset) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	for (int row = 1; row < GameConfig::GAME_HEIGHT + 1; row++)
	{
		for (int col = 1; col < GameConfig::GAME_WIDTH + 1; col++)
		{
			if (boardArr[row][col] == 1)
			{
				gotoxy(offset + col, row);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorBoard[row][col]);
				std::cout << '*';
			}
			else
			{
				gotoxy(offset + col, row);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				std::cout << ' ';
			}
		}
	}
}

bool Board::didIlose() const
{
	for (int col = 1; col < GameConfig::GAME_WIDTH + 1; col++)
	{
		if (Board::boardArr[1][col] == 1)
			return true;
	}
	return false;
}

const int Board::countFullRows() const
{
	int counter, countFullRows = 0;

	for (int row = 1; row <= GameConfig::GAME_HEIGHT; row++)
	{
		counter = 0;
		for (int col = 1; col <= GameConfig::GAME_WIDTH; col++)
		{
			if (Board::boardArr[row][col] == 1)
				counter++;
		}
		if (counter == GameConfig::GAME_WIDTH)
		{
			countFullRows++;
		}
	}
	return countFullRows;
}

void Board::findHighiestPoint (Point* pos) const
{
	for (int row = 1; row <= GameConfig::GAME_HEIGHT; row++)
	{
		for (int col = 1; col <= GameConfig::GAME_WIDTH; col++)
		{
			if (boardArr[row][col] == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					pos[i].init(col, row);
				}
				return;
			}
		}
	}
}