#include "pellet.hh"

int Pellet::id_counter = 0;

Pellet::Pellet(){
}

Pellet::Pellet(int x, int y, bool eaten):
    id(id_counter++), x(x), y(y), eaten(eaten){
        
    }
Pellet::~Pellet(){
    
}

int Pellet::getX(){
    return x + (25/2);
}

int Pellet::getY(){
    return y + (25/2);
}