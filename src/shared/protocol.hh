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
    MessageType PlayerInput;

    bool up;
    bool down;
    bool left;
    bool right;

    int score;
};


// Server -> Client packet
struct PlayerState
{
    int id;

    float x;
    float y;
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