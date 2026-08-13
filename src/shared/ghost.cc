#include "ghost.hh"

Ghost::Ghost()
{
}

Ghost::Ghost(Texture2D texture, Rectangle source, Rectangle dest)
{
    ghost = texture;
    spriteCoordinate = source;
    coordinate = dest;
}

Ghost::~Ghost()
{
}

void Ghost::setTexture(Texture2D texture)
{
    ghost = texture;
    spriteCoordinate = Rectangle{0, 0, };
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
    DrawTexturePro(ghost, spriteCoordinate, coordinate, Vector2{0,0}, 0, WHITE);
}

Rectangle Ghost::getCoordinate()
{
    return coordinate;
}

void Ghost::setCoordinate(Rectangle coordinate)
{
    this->coordinate = coordinate;
}

float Ghost::getSpeed(){
    return speed;
}
