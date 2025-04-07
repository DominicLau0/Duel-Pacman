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
        void draw_walls();
        void draw_pellets();

        bool wallCollisionDetected(Pacman, char);
        bool pelletCollisionDetected(Pacman, Pellet);

    private:
        Pacman pacmans[2];

        std::vector<Pellet> pellets;
        std::vector<std::string> map;
        std::vector<Wall> walls;

        float block_size = 0;
        float radius = 5;

        Vector2 pacman_first_position{-1, -1};
        Vector2 pacman_last_position{-1, -1};
};

#endif