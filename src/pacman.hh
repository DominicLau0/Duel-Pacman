#ifndef PACMAN_HH
#define PACMAN_HH

#include "sprite.hh"

class Pacman : public Sprite
{
    public:
        Pacman();
        ~Pacman();
        void input();
        int getStartPoint();

    private:
        int id;
        int start_point;
};

#endif