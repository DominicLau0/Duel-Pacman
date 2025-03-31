#include "../include/raylib.h"
#include "pacman.cc"
#include "pellet.cc"

int main(){
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
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("It works!", 20, 20, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}