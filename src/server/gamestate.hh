#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "./shared/protocol.hh"
#include <vector>

class GameState{
    public:
        GameState();
        ~GameState();

        bool wallCollisionDetected();
        void checkPacmanPelletCollision();

        void update(float dt);
        void processInput(int32_t playerId, const PlayerInput& input);

    private:
        std::vector<Pellet> pellets;
        std::vector<std::string> map;
        std::vector<Wall> walls;
}

#endif