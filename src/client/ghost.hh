#ifndef GHOST_HH
#define GHOST_HH

#include "../include/raylib.h"
#include "sprite.hh"
#include "string"

class Ghost : public Sprite
{
    public:
        Ghost();
        Ghost(Texture2D, Rectangle, Rectangle);
        ~Ghost();

        Texture2D getGhost();
        void draw();
        void update_x(float);
        void update_y(float);

        Vector2 generateDirection();

        Rectangle getCoordinate();
        void setCoordinate(Rectangle);
        Vector2 getDirection();
        void setDirection(Vector2);

        void loadTexture(Image);
        void setTexture(Texture2D);
        float getSpeed();

    private:
        int id;

        Rectangle spriteCoordinate;
        
        Rectangle coordinate;
        Vector2 direction = {0, 0};
        float speed = 100;

        Texture2D ghost;
};

#endif