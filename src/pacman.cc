#include "pacman.hh"

#include <iostream>

int Pacman::id_counter = 0;

Pacman::Pacman(){
}

Pacman::Pacman(float x, float y):
    id(id_counter++), x(x), y(y){
}

Pacman::~Pacman(){
}

void Pacman::input(){
}

void Pacman::update(float dt){
    start_point.x += direction.x * speed * dt;
    start_point.y += direction.y * speed * dt;
}

void Pacman::draw(){
    DrawCircleSector(start_point, 10, 0, 314, 100, color);
}

Vector2 Pacman::getStartPoint(){
    return start_point;
}

void Pacman::setStartPoint(Vector2 start_point){
    float adjusted_x = 25/2;
    float adjusted_y = 25/2;

    this->start_point = start_point;
    this->start_point.x += adjusted_x;
    this->start_point.y += adjusted_y;
}

void Pacman::setDirection(Vector2 direction){
    this->direction = direction;
}

void Pacman::setColor(Color color){
    this->color = color;
}