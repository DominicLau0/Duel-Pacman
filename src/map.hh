#ifndef MAP_HH
#define MAP_HH

#include <vector>
#include <string>

#include "./wall.hh"
#include "./pellet.hh"

class Map
{
    public:
        Map();
        void draw();
        void create_map();

    private:
        std::vector<Wall> walls;
        std::vector<std::string> layout;
        std::vector<Pellet> pellets;
};

#endif