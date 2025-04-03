#include "game.hh"
#include <iostream>

Game::Game(){
    map = {
        "11111111111111111111111111111",
        "2                           1",
        "2   111111111         11  111",
        "2   1                 1     1",
        "2   1     1           1     1",
        "2         111  111          1",
        "2   1            1          1",
        "2   1      1                1",
        "2   11111111    1111        1",
        "2               1           2",
        "211111111111111111111111111111"
    };

    block_size = 50;
    radius = 5;

    create_map();
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

            if(tile == ' '){
                pellets.push_back(Pellet(x, y, false));

                pacman_last_position.first = x;
                pacman_last_position.second = y;

                if(pacman_first_position.first == -1) {
                    pacman_first_position.first = x;
                    pacman_first_position.second = y;
                }
            }
            else if(tile == '1'){
                walls.push_back(Wall{x, y, block_size}); //TODO: Need to modify this to accept block size of certain length and width

            }else if(tile == '2'){
                walls.push_back(Wall{x, y, block_size});

            }else{
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

void Game::draw_walls(){
    // Iterate through each cell in the map
    for (int row = 0; row < map.size(); row++){
        for (int col = 0; col < map[row].size(); col++){
            // Check if the cell represents a wall (any non-space character)
            if(map[row][col] != ' '){
                float x = col * block_size;
                float y = row * block_size;

                // Choose a color based on horizontal position.
                // (You can adjust this logic if needed.)
                Color color = (x < ((int)map[row].size()/2 * block_size)) ? BLUE : RED;

                // For each side, check if the neighboring cell is not a wall.
                // Left side: if at left edge or left neighbor is empty.
                if(col == 0 || map[row][col-1] == ' '){
                    DrawLineEx(Vector2 {x, y}, Vector2 {x, y + block_size}, 2, color);
                }
                // Right side: if at right edge or right neighbor is empty.
                if(col == map[row].size()-1 || map[row][col+1] == ' '){
                    DrawLineEx(Vector2 {x + block_size, y}, Vector2 {x + block_size, y + block_size}, 2, color);
                }
                // Top side: if at top edge or the above neighbor is empty.
                if(row == 0 || map[row-1][col] == ' '){
                    DrawLineEx(Vector2 {x, y}, Vector2 {x + block_size, y}, 2, color);
                }
                // Bottom side: if at bottom edge or the below neighbor is empty.
                if(row == map.size()-1 || map[row+1][col] == ' '){
                    DrawLineEx(Vector2 {x, y + block_size}, Vector2 {x + block_size, y + block_size}, 2, color);
                }
            }
        }
    }

}

void Game::draw_pellets(){
    for(Pellet& pellet: pellets){
        DrawCircle(pellet.getX(), pellet.getY(), radius, YELLOW);
    }
}

void Game::run(){
    // Initialize display
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the walls and pellets
        draw_walls();
        draw_pellets();

        Vector2 blue_pacman_direction = Vector2();
        Vector2 red_pacman_direction = Vector2();

        blue_pacman_direction.x = int(IsKeyDown(KEY_RIGHT)) - int(IsKeyDown(KEY_LEFT));
        blue_pacman_direction.y = int(IsKeyDown(KEY_DOWN)) - int(IsKeyDown(KEY_UP));

        red_pacman_direction.x = int(IsKeyDown(KEY_D)) - int(IsKeyDown(KEY_A));
        red_pacman_direction.y = int(IsKeyDown(KEY_S)) - int(IsKeyDown(KEY_W));

        //Draw pacman
        for(Pacman& pacman: pacmans){
            pacman.draw();
        }
        
        EndDrawing();
    }

    CloseWindow();
}