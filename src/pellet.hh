#ifndef PELLET_HH
#define PELLET_HH

#include "sprite.hh"

class Pellet
{
    public:
        Pellet();
        Pellet(int x, int y, bool eaten);
        ~Pellet();

        int getX();
        int getY();

    private:
        static int id_counter;

        int id;
        int x = 0;
        int y = 0;
        bool eaten = false;
};

#endif