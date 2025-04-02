#include "Wall.hh"

int Wall::id_counter = 0;

Wall::Wall(){
}

Wall::Wall(float x, float y, float block_size):
    id(id_counter++), x(x), y(y), block_size(block_size){
        
}

Wall::~Wall(){
    
}

float Wall::getX(){
    return x;
}

float Wall::getY(){
    return y;
}

float Wall::getBlockSize(){
    return block_size;
}