#include "Wall.hh"

int Wall::id_counter = 0;

Wall::Wall(){
}

Wall::Wall(float x, float y, float width, float height, Color color):
    wall({x, y, width, height}), color(color){
}

Wall::~Wall(){
    
}

Color Wall::getColor(){
    return color;
}

Rectangle Wall::getWall(){
    return wall;
}