#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>

#include "../include/raylib.h"
#include "pellet.hh"
#include "wall.hh"
#include "pacman.hh"

class Game
{
    public:
        Game();
        ~Game();
        void run();
        void create_map();

    private:
        Pacman pacmans[2];

        std::vector<Pellet> pellets;
        std::vector<std::string> map;
        std::vector<Wall> walls;

        float block_size = 0;
        float radius = 5;

        std::pair<int, int> pacman_first_position{-1, -1};
        std::pair<int, int> pacman_last_position{-1, -1};
};

#endif