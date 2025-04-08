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
        void update_x(float);
        void update_y(float);
        Vector2 getStartPoint();
        void setStartPoint(Vector2);
        Vector2 getDirection();
        void setDirection(Vector2);
        Color getColor();
        void setColor(Color);
        Vector2 getCenter();
        float getRadius();
        float getSpeed();

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