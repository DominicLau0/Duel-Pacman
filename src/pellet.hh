#ifndef PELLET_HH
#define PELLET_HH

#include "sprite.hh"

class Pellet
{
    public:
        Pellet();
        Pellet(float x, float y, bool eaten);
        ~Pellet();

        float getX();
        float getY();

    private:
        static int id_counter;

        int id;
        float x = 0;
        float y = 0;
        bool eaten = false;
};

#endif