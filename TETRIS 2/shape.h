#ifndef _SHAPE_H
#define _SHAPE_H
#include "point.h"
#include "gameConfig.h"

class Shape
{
	Point shapeArr[GameConfig::SHAPE_SIZE];
	int type;
	int score;
	int color;
	bool isColor;

public:
	enum class ShapeType { SQUARE = 0, T, LR, LL, RECTANGLE, Z, S, BOMB };
	void init(Shape::ShapeType type, bool isColor);
	void draw(int offset) const;
	void move(GameConfig::eKeys key, Board& bd, bool& isPointBlocked, int offset);
	void rotateClockWise(Board& bd);
	void rotateCounterClockwise(Board& bd);
	void deleteShape(int offset);
	bool isInvalidPosition(Board& bd) const;
	void drop(Board& bd);
	bool canIdrop(Board& bd) const;
	void explode(Board& bd, int offset) const;
	void getArr(Point* arr) const;
	void findPathScore(Board& bd, int& score, Point* currPos);
	void findBestMove(Board& bd, Point* currPos, int& rotations, char computerLevel);
	void moveDown();
	void moveUp(int num);
	void moveLeft();
	void moveRight();
	void rotate(Board& bd);
	int sumY() const;
	int getScore() const;
};

#endif