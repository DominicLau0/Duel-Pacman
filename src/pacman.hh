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
        void update(float);
        Vector2 getStartPoint();
        void setStartPoint(Vector2);
        void setDirection(Vector2);
        void setColor(Color);
        Vector2 getCenter();
        float getRadius();

    private:
        static int id_counter;

        int id;
        Vector2 center = {50, 50};
        float x = 0;
        float y = 0;
        Vector2 start_point;
        float speed = 500;
        Vector2 direction;
        Color color;
        float radius = 10;
};

#endif