#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#define NOMINMAX
#include <enet/enet.h>
#include <cstdint>
#include <algorithm>

// Game Object
struct Vector2
{
    float x;
    float y;
};

struct Rectangle
{
    Vector2 coordinate = {0.0f, 0.0f};
    float width;
    float height;
};


// Game data
struct Pacman
{
    uint32_t id=0;
    ENetPeer* peer = nullptr;

    Vector2 coordinate = {0.0f, 0.0f};
    Vector2 direction = {0.0f, 0.0f};

    float speed = 100;
    float radius = 10;

    int score = 0;
};

struct Ghost
{
    Vector2 coordinate = {0.0f, 0.0f};
    Vector2 direction = {0.0f, 0.0f};

    float speed = 100;
};

struct Pellet
{
    Vector2 coordinate = {0.0f, 0.0f};
    bool eaten;
};

struct Wall
{
    float x;
    float y;
    float width;
    float height;
};

#endif