#include "ghost.hh"

Ghost::Ghost()
{
}

Ghost::~Ghost()
{
    UnloadTexture(ghost);
}

void Ghost::loadTexture(Image img)
{
    ghost = LoadTextureFromImage(img);
}

Texture2D Ghost::getGhost()
{
    return ghost;
}

void Ghost::update_x(float dt)
{
    coordinate.x += (direction.x * speed * dt);
}

void Ghost::update_y(float dt)
{
    coordinate.y += (direction.y * speed * dt);
}

Vector2 Ghost::generateDirection()
{
    int dir = rand() % 4;

    if (dir == 0)
    {
        direction = {0, -1};
    }
    else if (dir == 1)
    {
        direction = {0, 1};
    }
    else if (dir == 2)
    {
        direction = {-1, 0};
    }
    else
    {
        direction = {1, 0};
    }

    return direction;
}

void Ghost::draw()
{
    DrawTextureV(ghost, coordinate, WHITE);
    collisionBox = {coordinate.x, coordinate.y, 20, 20};
}

Vector2 Ghost::getCoordinate()
{
    return coordinate;
}

void Ghost::setCoordinate(Vector2 coordinate)
{
    this->coordinate = coordinate;
}

float Ghost::getSpeed(){
    return speed;
}
