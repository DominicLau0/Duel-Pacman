#include "../include/raylib.h"

int main(){
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "Hello Raylib");
    
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