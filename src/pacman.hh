#ifndef PACMAN_HH
#define PACMAN_HH

#include "sprite.hh"

class Pacman : public Sprite
{
    public:
        void input();

    private:
        int id;
};

#endif