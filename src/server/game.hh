#ifndef GAMESTATE_HH
#define GAMESTATE_HH

// Certain functions like Rectangle in our protocol file and enet collides (enet due to Win32 API function).
// Need to disable these from Win32 API to allow us to use these functions for Raylib.
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #define NOGDI   // Prevents wingdi.h from defining Rectangle()
#endif

#define NOMINMAX

#include "../shared/protocol.hh"
#include "gameobject.hh"
#include "server.hh"
#include <vector>
#include <iostream>
#include <chrono>

class Game{
    public:
        Game();
        ~Game();

        void run();

    private:
        Server server;

        std::vector<Pacman> pacmans;
        std::vector<Pellet> pellets;
        std::vector<Ghost> ghosts;
        std::vector<Rect> walls;

        std::vector<std::string> map;

        void create_map();

        bool wallCollisionDetected(Vector2 pos, float radius);
        bool wallCollisionDetected(Rect pos);
        void checkPacmanPelletCollision();

        bool checkCollisionCircleRec(Vector2 circle, float radius, Rect rect);
        bool checkCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);

        void update(float dt);
        void processInput(int32_t playerId, const PlayerInput& input);

        void simulateGame(float dt);

        Vector2 generateDirection();

        float block_size = 20.0f;
        float spriteSize = 14;
};

#endif