#ifndef WALL_HH
#define WALL_HH

#include "sprite.hh"

class Wall
{
    public:
        Wall();
        Wall(float x, float y, float block_size);
        ~Wall();

        float getX();
        float getY();
        float getBlockSize();

    private:
        static int id_counter;

        int id;
        float x = 0;
        float y = 0;
        float block_size = 50;
};

#endif