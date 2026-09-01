#include "pellet.hh"

int Pellet::id_counter = 0;

Pellet::Pellet(){
}

Pellet::Pellet(Vector2 coordinate, bool eaten):
    id(id_counter++), coordinate(coordinate), eaten(eaten){
        
    }

Vector2 Pellet::getCoordinate(){
    return coordinate;
}