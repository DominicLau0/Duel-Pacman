#ifndef PACMAN_HH
#define PACMAN_HH

#include "sprite.hh"
#include "../include/raylib.h"

#include <vector>

class Pacman
{
    public:
        Pacman();
        Pacman(float, float);
        ~Pacman();
        void input();
        void draw();
        Vector2 getStartPoint();
        void setStartPoint(Vector2);

    private:
        static int id_counter;

        int id;
        Vector2 center = {50, 50};
        float x = 0;
        float y = 0;
        Vector2 start_point;
};

#endif