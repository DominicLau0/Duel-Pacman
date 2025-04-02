#ifndef PELLET_HH
#define PELLET_HH

#include "sprite.hh"

class Pellet : public Sprite
{
    public:

    private:
        int id;
        int x;
        int y;
        bool eaten;
};

#endif