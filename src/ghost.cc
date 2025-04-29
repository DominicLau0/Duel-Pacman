#include "ghost.hh"

Ghost::Ghost(){

}

Ghost::~Ghost(){
    UnloadTexture(ghost);
}

void Ghost::loadTexture(Image img){
    ghost = LoadTextureFromImage(img);
}

Texture2D Ghost::getGhost(){
    return ghost;
}

void Ghost::update(){
    int dir = rand() % 4;
    switch(dir) {
        case 0: x += speed; break;
        case 1: x -= speed; break;
        case 2: y += speed; break;
        case 3: y -= speed; break;
    }
}
void Ghost::draw(){
    DrawTexture(ghost, x, y, WHITE);
}

float Ghost::getX(){
    return x;
}
float Ghost::getY(){
    return y;
}

void Ghost::setX(float x){
    this->x = x;
}

void Ghost::setY(float y){
    this->y = y;
}