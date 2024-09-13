#include "player.h"
#include <windows.h>
#include <iostream>

Player::Player()
{
	init(0, false);
}

 Player::~Player() {}

void Player::init(int offset, bool color)
{
	// Initialize the player with the specified offset(the right or left board), shape, and board
	this->offset = offset;
	initShape(color);
	initBoard();
	score = 0;
}

void Player::initShape(bool color)
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
}

void Player::initBoard()
{
	// Initialize the player's board
	board.init();
}

void Player::drawShape() const
{
	// Draw the player's shape on the screen
	shape.draw(offset);
}

void Player::drawBoard() const
{
	// Draw the player's board on the screen
	board.draw(offset);
}

bool Player::isMyKey(int& key) const
{
	// Check if the key corresponds to the player based on the offset
	changeToLower(key);

	if (offset == GameConfig::OFFSET_0)
	{
		if (key == (int)GameConfig::eKeys::RIGHT_A || key == (int)GameConfig::eKeys::LEFT_A || key == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_A
			|| key == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_A || key == (int)GameConfig::eKeys::DROP_A)
			return true;
	}
	if (offset == GameConfig::OFFSET)
	{
		if (key == (int)GameConfig::eKeys::RIGHT_B || key == (int)GameConfig::eKeys::LEFT_B || key == (int)GameConfig::eKeys::ROTATE_CLOCKWISE_B
			|| key == (int)GameConfig::eKeys::ROTATE_COUNTER_CLOCKWISE_B || key == (int)GameConfig::eKeys::DROP_B)
			return true;
	}
	return false;
}

void Player::changeToLower(int& key) const
{
	// Convert the key to lowercase if it's uppercase
	if ((key) >= 'A' && (key) <= 'Z')
		key += ('a' - 'A');
}

void Player::move(GameConfig::eKeys key, bool& isPointBlocked)
{
	// Move the player's shape based on the pressed key
	shape.move(key, board, isPointBlocked, offset);
	printScore();
}

bool Player::didIlose() const
{
	// Check if the player lost the game
	return board.didIlose();
}

void Player::printWinner() const
{
	// Print the winner message on the screen
	system("cls");
	if (offset == 0)
		std::cout << "\nPlayer 1 you are the winner!!!!!\n" << "\nYou scored "<< score << " points!";
	else
		std::cout << "\nPlayer 2 you are the winner!!!!!\n" << "\nYou scored " << score << " points!";
	std::cout << "\n\n\n\nPress any key to return to menu\n";
}

//Increases the player's score by the current shape's score
void Player::changeScore()
{
	score += shape.getScore();
}

//Prints the player's score on the console
void Player::printScore() const
{
	gotoxy(offset+2, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	std::cout << "SCORE: " << score;
}

int Player::getOffset() const
{
	return offset;
}