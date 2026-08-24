#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>

#include "../include/raylib.h"
#include "pellet.hh"
#include "wall.hh"
#include "pacman.hh"
#include "ghost.hh"
#include "ClientNetwork.hh"

#define TEAL Color{ 53, 156, 156, 255 }
#define DARKGOLD Color{ 194, 184, 83, 255 }

#define TEXTURE_WIDTH 680
#define TEXTURE_HEIGHT 248 

class Game
{
    public:
        Game();
        ~Game();

        void run();
        void create_map();

        void draw_walls();
        void draw_pellets();
        void draw_scoreboard();

        bool wallCollisionDetected(Vector2, float);
        bool wallCollisionDetected(Rectangle pos);
        void checkPacmanPelletCollision();

        void initializeGhosts();

    private:
        int screenWidth = 640;
        int screenHeight = 480;

        int pacman_amount = 2;
        int ghost_amount = 4;

        Texture2D texture;
        float spriteSize = 14;
        float spriteSpace = 2;

        float spriteStartingX = 457;
        float spriteStartingY = 65;
        
        std::vector<Pacman> pacmans = {Pacman(), Pacman()};
        std::vector<Color> pacman_colors = {BLUE, RED};

        std::vector<Ghost> ghosts = {Ghost()};

        std::vector<Pellet> pellets;
        std::vector<std::string> map;
        std::vector<Wall> walls;

        float block_size = 20;
        float radius = 2;

        Client clientNetwork;
};

#endif