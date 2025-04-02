#include "game.hh"
#include <iostream>
#include "pacman.cc"
#include "pellet.cc"

Game::Game(){
    map = {
        "1111111111111111111",
        "1010000000000000001",
        "1010000000001111111",
        "1000000000000000111",
        "1000000200000000011",
        "1000000000000100001",
        "1000000000000100001",
        "1001100000000100001",
        "1001100000000100001",
        "1001100000000100001",
        "1111111111111111111"
    };

    block_size = 100;
}

Game::~Game(){

}

void Game::create_map(){
    /**
     * Creates the layout of the pacman game.
     * 
     * '0' represents no wall.
     * '1' represents a horizontal wall
     * '2' represents a vertical wall
     * 
     * Stores the created walls in the vector wall.
     * 
     * @param values None
     * @return None
     */

    for (int row = 0; row < map.size(); row++){
        for(int column = 0; column < map[row].size(); column++){
            int tile = map[row][column];

            float x = column * block_size;
            float y = row * block_size;

            if(tile == '1'){
                wall.push_back(Rectangle(x, y, block_size, block_size));

            }else if(tile == '2'){
                wall.push_back(Rectangle(x, y, block_size, block_size));

            }else if(tile != '0'){
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

void Game::run(){
    // Initialize display
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    // Initialize objects
    Pacman pacman = Pacman();
    Pellet pallets = Pellet();

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("It works!", 20, 20, 20, BLACK);
        
        EndDrawing();
    }

    CloseWindow();
}