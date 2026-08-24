#ifndef PROTOCOL_HH
#define PROTOCOL_HH

#include <cstdint>

// Message Type
enum class MessageType : uint8_t{
    PlayerInput = 1,
    WorldState = 2,
    PlayerJoined = 3,
    PlayerLeft = 4
};

// Client -> Server packet
struct PlayerInput
{
    int32_t id;

    bool up;
    bool down;
    bool left;
    bool right;
};


// Server -> Client packet
struct PlayerState
{
    int id;

    float x;
    float y;
    
    int score;
};

struct PelletState
{
    int id;

    float x;
    float y;
};

struct GhostState
{
    int id;

    float x;
    float y;
};

#endif