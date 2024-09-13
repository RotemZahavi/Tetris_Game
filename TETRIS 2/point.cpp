#include "point.h"
#include "general.h"
#include <Windows.h>
#include <iostream>

void Point::init(int x, int y)
{
    // Initialize point coordinates and differences
    this->x = x;
    this->y = y;
    diff_x = 0;
    diff_y = 0;
}

void Point::draw(char ch, int offset, int backColor) const
{
    // Draw the point at the specified location on the screen
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backColor);
    gotoxy(x + GameConfig::MIN_X - 1 + offset, y + GameConfig::MIN_Y - 1);
    std::cout << ch;
}

void Point::move(GameConfig::eKeys key, bool& isPointBlocked)
{
    // Update point position based on the pressed key
    switch (key)
    {
    case GameConfig::eKeys::LEFT_A:
        diff_x = -1;
        diff_y = 1;
        break;

    case GameConfig::eKeys::RIGHT_A:
        diff_x = 1;
        diff_y = 1;
        break;

    case GameConfig::eKeys::LEFT_B:
        diff_x = -1;
        diff_y = 1;
        break;

    case GameConfig::eKeys::RIGHT_B:
        diff_x = 1;
        diff_y = 1;
        break;
    default:
        diff_x = 0;
        diff_y = 1;
        break;
    }

    // Check if the point is at the bottom
    if (y == GameConfig::GAME_HEIGHT)
        isPointBlocked = true;

    // Update point coordinates
    y += diff_y;
    x += diff_x;
}

int Point::getX() const
{
    // Return the x-coordinate of the point
    return x;
}

int Point::getY() const
{
    // Return the y-coordinate of the point
    return y;
}





