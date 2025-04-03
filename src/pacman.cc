#include "pacman.hh"

#include <iostream>

int Pacman::id_counter = 0;

Pacman::Pacman(){
}

Pacman::Pacman(float x, float y):
    id(id_counter++), x(x), y(y){

    DrawCircleSector(start_point, 10, 0, 314, 100, RED);
}

Pacman::~Pacman(){
}

void Pacman::input(){
}

void Pacman::draw(){

}

Vector2 Pacman::getStartPoint(){
    return start_point;
}

void Pacman::setStartPoint(Vector2 start_point){
    this->start_point = start_point;
}