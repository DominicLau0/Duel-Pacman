#include "pellet.hh"

int Pellet::id_counter = 0;

Pellet::Pellet(){
}

Pellet::Pellet(float x, float y, bool eaten):
    id(id_counter++), x(x), y(y), eaten(eaten){
        
    }
Pellet::~Pellet(){
    
}

float Pellet::getX(){
    return x + (25/2);
}

float Pellet::getY(){
    return y + (25/2);
}