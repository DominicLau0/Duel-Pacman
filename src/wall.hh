#ifndef WALL_HH
#define WALL_HH

#include "sprite.hh"
#include "../include/raylib.h"

class Wall
{
    public:
        Wall();
        Wall(Vector2, Vector2, Color);
        ~Wall();

        Vector2 getStartPosition();
        Vector2 getEndPosition();
        Color getColor();

    private:
        static int id_counter;

        int id;

        Vector2 startPosition = {0, 0};
        Vector2 endPosition = {0, 0};
        Color color = BLUE;
};

#endif