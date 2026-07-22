#include "pacman.hh"

#include <iostream>

int Pacman::id_counter = 0;

Pacman::Pacman()
{
    speed = 100;
    score = 0;
    direction = {0, 0};
}

Pacman::Pacman(Vector2 coordinate, float y) : id(id_counter++), coordinate(coordinate)
{
    radius = 10;
}

Pacman::~Pacman()
{
}

void Pacman::update_x(float dt)
{
    coordinate.x += (direction.x * speed * dt);
}

void Pacman::update_y(float dt)
{
    coordinate.y += (direction.y * speed * dt);
}

void Pacman::draw()
{
    DrawCircleSector(coordinate, radius, 0, 314, 100, color);
}

Vector2 Pacman::getCoordinate()
{
    return coordinate;
}

float Pacman::getRadius()
{
    return radius;
}

void Pacman::setCoordinate(Vector2 coordinate)
{
    this->coordinate = coordinate;
}

Vector2 Pacman::getDirection()
{
    return direction;
}

void Pacman::setDirection(Vector2 direction)
{
    this->direction = direction;
}

Color Pacman::getColor()
{
    return color;
}

void Pacman::setColor(Color color)
{
    this->color = color;
}

float Pacman::getSpeed()
{
    return speed;
}

int Pacman::getScore()
{
    return score;
}
void Pacman::setScore(int score)
{
    this->score = score;
}