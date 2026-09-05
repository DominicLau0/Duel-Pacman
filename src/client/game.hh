#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <string>

// Certain functions in raylib and enet collides (enet due to Win32 API function).
// Need to disable these from Win32 API to allow us to use these functions for Raylib.
#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #define NOGDI   // Prevents wingdi.h from defining Rectangle()
    #define NOUSER  // Prevents winuser.h from defining CloseWindow(), ShowCursor(), etc.
#endif

#include "../../include/raylib.h"
#include "pellet.hh"
#include "wall.hh"
#include "pacman.hh"
#include "ghost.hh"
#include "client.hh"
#include "protocol.hh"

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