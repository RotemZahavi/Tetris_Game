#include "computer.h"
#include <windows.h>
#include <iostream>

Computer::Computer()
{
	init(0, false);
}

Computer::~Computer() {}

//Finds the best move and update the move array
void Computer::movebyStep()
{
	int rotations=0;
	findBestMove(rotations);
	makeMoveArray(rotations);
}

//Finds the best move for the computer player's shape on the board
void Computer::findBestMove(int& rotations)
{
	shape.findBestMove(board, bestPos, rotations, computerLevel);
}

//Adjusts the shape position and populates the move array based on the best move
void Computer::makeMoveArray(int& rotations)
{
    Point tempShape[GameConfig::SHAPE_SIZE];
    shape.getArr(tempShape);
    int countRight, countLeft, countDown;
    countDown = countLeft = countRight = 0;
    while (tempShape[0].getX() > bestPos[0].getX())
    {
        for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
        {
            tempShape[i].init(tempShape[i].getX() - 1, tempShape[i].getY());
        }
        countLeft++;
    }

    while (tempShape[0].getX() < bestPos[0].getX())
    {
        for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
        {
            tempShape[i].init(tempShape[i].getX() + 1, tempShape[i].getY());
        }
        countRight++;
    }

    while (tempShape[0].getY() < bestPos[0].getY())
    {
        for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
        {
            tempShape[i].init(tempShape[i].getX(), tempShape[i].getY() + 1);
        }
        countDown++;
    }

    moveArray.clear();  // Clear the vector before updating
    moveArray.reserve(countLeft + rotations + countRight + countDown);

    int i = 0;
    int k = 0;

    for (; i < countLeft; i++, k++)
    {
        moveArray.push_back((int)'a');
    }
    for (i = 0; i < rotations; i++, k++)
    {
        moveArray.push_back((int)'s');
    }
    for (i = 0; i < countRight; i++, k++)
    {
        moveArray.push_back((int)'d');
    }
    countDown = countDown - countLeft - countRight;
    for (i = 0; i < countDown; i++, k++)
    {
        moveArray.push_back(0);
    }
}

//Performs the next move, updates position, and prints the score
void Computer::move(GameConfig::eKeys key, bool& isPointBlocked)
{
	shape.move((GameConfig::eKeys)moveArray[index], board, isPointBlocked, offset);
	if(moveArray.size() != index + 1)
        index++;
	printScore();
}

//Initializes the computer player with the specified offset, board, and shape
void Computer::init(int offset, bool color)
{
	// Initialize the player with the specified offset(the right or left board), shape, and board
	initBoard();
	this->offset = offset;
	initShape(color);

}

//Initializes the computer player's shape with a chance for a bomb shape and determines the initial move
void Computer::initShape(bool color)
{
	// Initialize the shape for the player with a random type

	if (rand() % 100 < 5)
	{
		shape.init(Shape::ShapeType::BOMB, color);
	}
	else
	{
		shape.init(static_cast<Shape::ShapeType>(rand() % 7), color);  // Adjusted to exclude BOMB
	}
	shape.init(static_cast<Shape::ShapeType>(rand() % 8), color);
    index = 0;
	movebyStep();
}

//Sets the difficulty level for the computer player
void Computer::setLevel(char level)
{
	computerLevel = level;
}
