#ifndef GHOST_HH
#define GHOST_HH

#include "sprite.hh"

class Ghost : public Sprite
{
    public:
        Ghost();
        ~Ghost();
    private:
        int id;
};

#endif