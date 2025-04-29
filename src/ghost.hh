#ifndef GHOST_HH
#define GHOST_HH

#include "../include/raylib.h"
#include "sprite.hh"
#include "string"

class Ghost : public Sprite
{
    public:
        Ghost();
        ~Ghost();
        Texture2D getGhost();
        float getX();
        float getY();
        void setX(float);
        void setY(float);
        void loadTexture(Image);
        void update();
        void draw();

    private:
        int id;
        float x;
        float y;
        float speed = 100;
        Texture2D ghost;
};

#endif