#include "shape.h"
#include "general.h"
#include "board.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <algorithm>


void Shape::init(Shape::ShapeType type, bool isColor)
{
	// Initialize the coordinates of the shape's points for each shape
	switch (type)
	{
	case(ShapeType::SQUARE):
		this->type = (int)ShapeType::SQUARE;
		color = 176;
		shapeArr[0].init(6, 1);
		shapeArr[1].init(7, 1);
		shapeArr[2].init(6, 2);
		shapeArr[3].init(7, 2);
		break;
	case(ShapeType::T):
		this->type = (int)ShapeType::T;
		color = BACKGROUND_BLUE;
		shapeArr[0].init(6, 1);
		shapeArr[1].init(5, 1);
		shapeArr[2].init(7, 1);
		shapeArr[3].init(6, 2);
		break;
	case(ShapeType::LR):
		this->type = (int)ShapeType::LR;
		color = BACKGROUND_RED | BACKGROUND_GREEN;
		shapeArr[0].init(5, 2);
		shapeArr[1].init(5, 1);
		shapeArr[2].init(5, 3);
		shapeArr[3].init(6, 3);
		break;
	case(ShapeType::LL):
		this->type = (int)ShapeType::LL;
		color = 224;
		shapeArr[0].init(6, 2);
		shapeArr[1].init(6, 1);
		shapeArr[2].init(5, 3);
		shapeArr[3].init(6, 3);
		break;
	case(ShapeType::RECTANGLE):
		this->type = (int)ShapeType::RECTANGLE;
		color = BACKGROUND_GREEN;
		shapeArr[0].init(6, 2);
		shapeArr[1].init(6, 1);
		shapeArr[2].init(6, 3);
		shapeArr[3].init(6, 4);
		break;
	case(ShapeType::Z):
		this->type = (int)ShapeType::Z;
		color = BACKGROUND_RED | BACKGROUND_BLUE;
		shapeArr[0].init(6, 1);
		shapeArr[1].init(5, 1);
		shapeArr[2].init(6, 2);
		shapeArr[3].init(7, 2);
		break;
	case(ShapeType::S):
		this->type = (int)ShapeType::S;
		color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
		shapeArr[0].init(6, 1);
		shapeArr[1].init(7, 1);
		shapeArr[2].init(5, 2);
		shapeArr[3].init(6, 2);
		break;
	case(ShapeType::BOMB):
		this->type = (int)ShapeType::BOMB;
		color = BACKGROUND_RED;
		shapeArr[0].init(6, 1);
		shapeArr[1].init(6, 1);
		shapeArr[2].init(6, 1);
		shapeArr[3].init(6, 1);
	}
	this->isColor = isColor;
	if (isColor == false)
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	score = 0;
}

void Shape::draw(int offset) const
{
	// Draw the shape on the screen
	if (type == (int)ShapeType::BOMB)
	{
		shapeArr[0].draw('@', offset, color);
	}
	else
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
			shapeArr[i].draw('*', offset, color);
	}
}

void Shape::deleteShape(int offset)
{
	// Remove the shape from the screen
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		shapeArr[i].draw(' ', offset, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Shape::move(GameConfig::eKeys key, Board& bd, bool& isPointBlocked, int offset)
{
	// Move the shape based on the pressed key
	int rowInd = 0, countFullRows = 0;
	Shape::deleteShape(offset);


	if (key == GameConfig::eKeys::ROTATE_CLOCKWISE_A || key == GameConfig::eKeys::ROTATE_CLOCKWISE_B)
	{
		Shape::rotateClockWise(bd);
	}
	else if (key == GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_A || key == GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_B)
	{
		Shape::rotateCounterClockwise(bd);
	}
	else if (key == GameConfig::eKeys::DROP_A || key == GameConfig::eKeys::DROP_B)
	{
		Shape::drop(bd);
		if (type == (int)ShapeType::BOMB)
			isPointBlocked = true;
	}
	else
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			shapeArr[i].move(key, isPointBlocked);
		}

		if (isPointBlocked) //if the point hit the border of the board from the bottom
		{
			for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
			{
				switch (key)
				{
				case GameConfig::eKeys::RIGHT_A:
				case GameConfig::eKeys::RIGHT_B:
					shapeArr[i].init(shapeArr[i].getX() - 1, shapeArr[i].getY()-1);
					bd.putPointInBoard(shapeArr[i].getX(), shapeArr[i].getY(), color);
					break;

				case GameConfig::eKeys::LEFT_A:
				case GameConfig::eKeys::LEFT_B:
					shapeArr[i].init(shapeArr[i].getX() + 1, shapeArr[i].getY()-1);
					bd.putPointInBoard(shapeArr[i].getX(), shapeArr[i].getY(), color);
					break;
				default:
					shapeArr[i].init(shapeArr[i].getX(), shapeArr[i].getY() - 1);
					bd.putPointInBoard(shapeArr[i].getX(), shapeArr[i].getY(), color);
					break;
				}
			}     
			score += 10;
		}
		else //check if there is another shape in the board that prevents the current move of the shape 
		{
			if (!(bd.isEmpty(shapeArr[0].getX(), shapeArr[0].getY()) && (bd.isEmpty(shapeArr[1].getX(), shapeArr[1].getY())) &&
				bd.isEmpty(shapeArr[2].getX(), shapeArr[2].getY()) && (bd.isEmpty(shapeArr[3].getX(), shapeArr[3].getY()))))
			{
				for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
				{
					switch (key)
					{
					case GameConfig::eKeys::RIGHT_A:
					case GameConfig::eKeys::RIGHT_B:
						shapeArr[i].init(shapeArr[i].getX() - 1, shapeArr[i].getY()-1);
						break;
					case GameConfig::eKeys::LEFT_A:
					case GameConfig::eKeys::LEFT_B:
						shapeArr[i].init(shapeArr[i].getX() + 1, shapeArr[i].getY()-1);
						break;
					default:
						shapeArr[i].init(shapeArr[i].getX(), shapeArr[i].getY() - 1);
						bd.putPointInBoard(shapeArr[i].getX(), shapeArr[i].getY(), color);
						isPointBlocked = true;
						score += 2;
						break;
					}
				}
			}
		}
	}
	Shape::draw(offset);
	if (type == (int)ShapeType::BOMB && isPointBlocked)
	{
		explode(bd, offset);
		score += 50;
	}
	while (bd.isRowFull(rowInd)) //if there is a full row, delete it and move down the remainings
	{ 
		bd.deleteRow(rowInd);
		score += 100;
	}
}

void Shape::rotateClockWise(Board& bd)
{
	if (type == (int)ShapeType::SQUARE)
		return;
	// Store the current state of the shape
	Point tempShape[GameConfig::SHAPE_SIZE];
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++) {
		tempShape[i] = shapeArr[i];
	}

	// Perform the rotation (clockwise)
	for (int i = 1; i < GameConfig::SHAPE_SIZE; i++) {
		int relativeX = shapeArr[i].getX() - shapeArr[0].getX();
		int relativeY = shapeArr[i].getY() - shapeArr[0].getY();
		shapeArr[i].init(shapeArr[0].getX() + relativeY, shapeArr[0].getY() - relativeX);
	}

	moveDown();

	// Check if the new position is valid, if not, revert to the previous state
	if (isInvalidPosition(bd))
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++) {
			shapeArr[i] = tempShape[i];
		}
	}
}

void Shape::rotate(Board& bd)
{
	// Perform the rotation (clockwise)
	if (type == (int)ShapeType::SQUARE)
		return;

	for (int i = 1; i < GameConfig::SHAPE_SIZE; i++) {
		int relativeX = shapeArr[i].getX() - shapeArr[0].getX();
		int relativeY = shapeArr[i].getY() - shapeArr[0].getY();
		shapeArr[i].init(shapeArr[0].getX() + relativeY, shapeArr[0].getY() - relativeX);
	}
}

void Shape::rotateCounterClockwise(Board& bd)
{
	// Store the current state of the shape
	Point tempShape[GameConfig::SHAPE_SIZE];
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++) {
		tempShape[i] = shapeArr[i];
	}

	// Perform the rotation (counter-clockwise)
	for (int i = 1; i < GameConfig::SHAPE_SIZE; i++) {
		int relativeX = shapeArr[i].getX() - shapeArr[0].getX();
		int relativeY = shapeArr[i].getY() - shapeArr[0].getY();

		shapeArr[i].init(shapeArr[0].getX() - relativeY, shapeArr[0].getY() + relativeX);
	}

	moveDown();

	// Check if the new position is valid, if not, revert to the previous state
	if (isInvalidPosition(bd))
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
			shapeArr[i] = tempShape[i];
	}
}

bool Shape::isInvalidPosition(Board& bd) const
{
	// Check if the new position after rotation is valid (within the board boundaries and not overlapping with other shapes)
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (shapeArr[i].getX() < 1 || shapeArr[i].getX() > GameConfig::GAME_WIDTH ||
			shapeArr[i].getY() < 1 || shapeArr[i].getY() > GameConfig::GAME_HEIGHT ||
			!(bd.isEmpty(shapeArr[i].getX(), shapeArr[i].getY())))
		{
			return true;  // Invalid position
		}
	}
	return false;  // Valid position
}

void Shape::drop(Board& bd)
{
	//check how far the shape can drop down, and move it there
	while (canIdrop(bd))
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			shapeArr[i].init(shapeArr[i].getX(), shapeArr[i].getY() + 1);
		}
	}
}

bool Shape::canIdrop(Board& bd) const
{
	//check how far the shape can drop down
	if ((bd.isEmpty(shapeArr[0].getX(), shapeArr[0].getY() + 1)) && (bd.isEmpty(shapeArr[1].getX(), shapeArr[1].getY() + 1)) &&
		(bd.isEmpty(shapeArr[2].getX(), shapeArr[2].getY() + 1)) && (bd.isEmpty(shapeArr[3].getX(), shapeArr[3].getY() + 1)))
		return true;
	else
		return false;
}

void Shape::explode(Board& bd, int offset) const
{
	//Explodes the bomb on the board, deleting points within a specified range and bringing down leftover shapes, adjusting for board boundaries

	int left = -4;
	int right = 4;
	int up = -4;
	int down = 4;
	int x = shapeArr[0].getX();
	int y = shapeArr[0].getY();

	while (y + up < 1)
		up++;
	while (y + down > GameConfig::GAME_HEIGHT)
		down--;
	while (x + left < 1)
		left++;
	while (x + right > GameConfig::GAME_WIDTH)
		right--;

	for (int i = y + up; i <= y + down; i++)
	{
		for (int j = x + left; j <= x + right; j++)
		{
			bd.deletePointInBoard(j, i);
		}
	}

	for (int i = y + up - 1; i >= 1; i--) //bring down the leftover shapes
	{
		for (int j = x + left - 1; j <= x + right + 1; j++)
		{
			if (!bd.isEmpty(j, i))
			{
				int k = i;
				while (bd.isEmpty(j, k + 1))
				{
					bd.deletePointInBoard(j, k);
					bd.putPointInBoard(j, k + 1, color);
					k++;
				}
			}
		}
	}
}

void Shape::getArr(Point* arr) const
{
	//Copies the current shape's points into the provided array
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		arr[i].init(shapeArr[i].getX(), shapeArr[i].getY());
	}
}

void Shape::findPathScore(Board& bd, int& score, Point* currPos)
{
	//Evaluates the score of a potential move by simulating its path and considering factors like descent, height, and completed rows
	int countDown = 0;
	int countFullRows = 0;
	while ((bd.isEmpty(shapeArr[0].getX(), shapeArr[0].getY() + 1)) && (bd.isEmpty(shapeArr[1].getX(), shapeArr[1].getY() + 1)) &&
		(bd.isEmpty(shapeArr[2].getX(), shapeArr[2].getY() + 1)) && (bd.isEmpty(shapeArr[3].getX(), shapeArr[3].getY() + 1)))
	{
		moveDown();
		countDown++;
	}

	int maxY = shapeArr[0].getY();
	int sum = sumY();
	score += sum;

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if(maxY < shapeArr[i].getY())
			maxY = shapeArr[i].getY();
	}
	score += 3 * maxY;

	countFullRows = bd.countFullRows();
	score += 1000 * countFullRows;

	getArr(currPos);
	moveUp(countDown);

}

void Shape::findBestMove(Board& bd, Point* maxPos, int& rotations, char computerLevel)
{
	//Determines the best move, considering various computer player levels, by evaluating scores for different rotations and positions.
	int currScore, maxScore;
	currScore = maxScore = 0;
	Point currPos[GameConfig::SHAPE_SIZE];

	if (type == (int)Shape::ShapeType::BOMB && computerLevel == 'a')
	{
		bd.findHighiestPoint(maxPos);
		return;
	}
	
	while (shapeArr[0].getX() > 1 && shapeArr[1].getX() > 1 && shapeArr[2].getX() > 1 && shapeArr[3].getX() > 1)
	{
		moveLeft();
	}

	for (int j = 0; j < GameConfig::SHAPE_SIZE; j++)
	{
		while (shapeArr[0].getX() <= GameConfig::GAME_WIDTH && shapeArr[1].getX() <= GameConfig::GAME_WIDTH &&
			shapeArr[2].getX() <= GameConfig::GAME_WIDTH && shapeArr[3].getX() <= GameConfig::GAME_WIDTH)
		{
			currScore = 0;
			findPathScore(bd, currScore, currPos);
			if (computerLevel == 'b' && rand() % 40 == 0) // GOOD level (1 miss in ~40 moves)
			{
				maxScore = 0;  // Reset score to simulate a miss
			}
			else if (computerLevel == 'c' && rand() % 10 == 0) // NOVICE level (1 miss in ~10 moves)
			{
				maxScore = 0;  // Reset score to simulate a miss
			}
			if (currScore > maxScore)
			{
				rotations=j;
				maxScore = currScore;
				for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
					maxPos[i] = currPos[i];
			}
			moveRight();
		}
		rotate(bd);
		
		while (shapeArr[0].getX() >= 1 && shapeArr[1].getX() >= 1 && shapeArr[2].getX() >= 1 && shapeArr[3].getX() >= 1)
		{
			moveLeft();
		}
	}
	init((ShapeType)type, isColor);
}

void Shape::moveDown()
{
	//Moves the shape points down by one unit
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		shapeArr[i].init(shapeArr[i].getX(), shapeArr[i].getY() + 1);
}

void Shape::moveUp(int num)
{
	//Moves the shape points up by a specified number of units
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		shapeArr[i].init(shapeArr[i].getX(), shapeArr[i].getY() - num);
}

void Shape::moveLeft()
{
	//Moves the shape points left by one unit
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		shapeArr[i].init(shapeArr[i].getX()-1, shapeArr[i].getY());
}

void Shape::moveRight()
{
	//Moves the shape points right by one unit.
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		shapeArr[i].init(shapeArr[i].getX()+1, shapeArr[i].getY());
}

int Shape::sumY() const
{
	//Calculates the sum of the Y-coordinates of the shape's points
	int sum = 0;
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		sum += shapeArr[i].getY();
	return sum;
}

int Shape::getScore() const
{
	//Retrieves the score associated with the shape
	return score;
}