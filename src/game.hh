#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>

#include "../include/raylib.h"

class Game
{
    public:
        void run();
        void create_map();

    private:
        std::vector<std::string> map;
        float block_size = 0;
        std::vector<Rectangle> wall;

};

#endif