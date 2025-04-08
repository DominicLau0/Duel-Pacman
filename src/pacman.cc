#include "pacman.hh"

#include <iostream>

int Pacman::id_counter = 0;

Pacman::Pacman(){
    speed = 200;
    center = start_point;
}

Pacman::Pacman(float x, float y):
    id(id_counter++), x(x), y(y){
    center = start_point;
}

Pacman::~Pacman(){
}

void Pacman::input(){
}

void Pacman::update_x(float dt){
    start_point.x += (direction.x * speed * dt);
}

void Pacman::update_y(float dt){
    start_point.y += (direction.y * speed * dt);
}

void Pacman::draw(){
    DrawCircleSector(start_point, radius, 0, 314, 100, color);
}

Vector2 Pacman::getStartPoint(){
    return start_point;
}

Vector2 Pacman::getCenter(){
    return center;
}

float Pacman::getRadius(){
    return radius;
}

void Pacman::setStartPoint(Vector2 start_point){
    float adjusted_x = 25/2;
    float adjusted_y = 25/2;

    this->start_point = start_point;
    this->start_point.x += adjusted_x;
    this->start_point.y += adjusted_y;
}

Vector2 Pacman::getDirection(){
    return direction;
}


void Pacman::setDirection(Vector2 direction){
    this->direction = direction;
}

Color Pacman::getColor(){
    return color;
}

void Pacman::setColor(Color color){
    this->color = color;
}

float Pacman::getSpeed(){
    return speed;
}