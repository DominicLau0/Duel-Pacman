#ifndef WALL_HH
#define WALL_HH

#include "sprite.hh"
#include "../include/raylib.h"

class Wall
{
    public:
        Wall();
        Wall(float, float, float, float, Color);
        ~Wall();
        
        Rectangle getWall();
        Color getColor();

    private:
        static int id_counter;

        int id;

        Vector2 coordinate = {0, 0};
        Color color = BLUE;
        Rectangle wall;
};

#endif