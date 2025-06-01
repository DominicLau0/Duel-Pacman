#ifndef PACMAN_HH
#define PACMAN_HH

#include "sprite.hh"
#include "../include/raylib.h"

#include <vector>

class Pacman
{
    public:
        Pacman();
        Pacman(Vector2, float);
        ~Pacman();

        void draw();
        void update_x(float);
        void update_y(float);

        Vector2 getCoordinate();
        void setCoordinate(Vector2);
        Vector2 getDirection();
        void setDirection(Vector2);
        
        Color getColor();
        void setColor(Color);
        float getRadius();
        float getSpeed();

        int getScore();
        void setScore(int);

    private:
        static int id_counter;

        int id;

        Vector2 coordinate;
        float speed = 300;
        Vector2 direction = {0, 0};

        Color color;
        float radius = 8;
        int score = 0;
};

#endif