#ifndef PELLET_HH
#define PELLET_HH

#include "../include/raylib.h"
#include "sprite.hh"

class Pellet
{
    public:
        Pellet();
        Pellet(Vector2, bool);
        
        Vector2 getCoordinate();

    private:
        static int id_counter;

        int id;
        Vector2 coordinate;
        bool eaten = false;
};

#endif