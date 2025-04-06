#include "Wall.hh"

int Wall::id_counter = 0;

Wall::Wall(){
}

Wall::Wall(Vector2 startPosition, Vector2 endPosition, Color color):
    id(id_counter++), startPosition(startPosition), endPosition(endPosition), color(color){

}

Wall::~Wall(){
    
}

Vector2 Wall::getStartPosition(){
    return startPosition;
}
Vector2 Wall::getEndPosition(){
    return endPosition;
}
Color Wall::getColor(){
    return color;
}