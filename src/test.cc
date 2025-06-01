#include "../include/raylib.h"

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Smooth 90° Thick Line Example");

    // Define your three key points:
    //   p1 = start of the vertical segment
    //   p2 = corner (joint) point
    //   p3 = end   of the horizontal segment1
    Vector2 p1 = { 200, 350 };  // for example: start at (200,350)
    Vector2 p2 = { 200, 150 };  // go straight up to (200,150)
    Vector2 p3 = { 500, 150 };  // then go right to (500,50)

    float thickness = 20.0f;    // “thick” line width in pixels

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 1) Draw vertical segment (from p1 up to p2)
        DrawLineEx(p1, p2, thickness, RED);

        // 2) Draw horizontal segment (from p2 to p3)
        DrawLineEx(p2, p3, thickness, RED);

        // 3) Draw a filled circle at the corner to smooth it
        //    Radius should be exactly half the thickness
        DrawCircleV(p2, thickness/2.0f, RED);

        DrawText("Thick L-shaped line with smooth corner", 20, 20, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
