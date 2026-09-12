#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <enet/enet.h>
#include <cstdint>
#include <algorithm>

// Game Object
struct Vector2
{
    float x;
    float y;
};

struct Rect
{
    Vector2 coordinate = {0.0f, 0.0f};
    float width;
    float height;
};


// Game data
struct Pacman
{
    uint8_t id = 0;
    ENetPeer* peer = nullptr;

    Vector2 coordinate = {0.0f, 0.0f};
    Vector2 direction = {0.0f, 0.0f};

    float speed = 100;
    float radius = 10;

    int score = 0;
};

struct Ghost
{
    Rect hitbox = {{0.0f, 0.0f}, 14, 14};
    Vector2 direction = {0.0f, 0.0f};

    float speed = 100;
};

struct Pellet
{
    Vector2 coordinate = {0.0f, 0.0f};
    float radius = 2;
    
    bool eaten = false;
};

#endif