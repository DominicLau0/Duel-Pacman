#include "game.hh"
#include <iostream>

Game::Game(){
    map = {
        "2111111111111111112",
        "2020000000000000002",
        "2020000000001111112",
        "2000000000000000112",
        "2000000200000000012",
        "2000000000000100002",
        "2000000000000100002",
        "2002200000000100002",
        "2002200000000100002",
        "2002200000000100002",
        "2111111111111111111"
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

            if(tile == '0'){
                pellets.push_back(Pellet(x, y, false));

                pacman_last_position.first = x;
                pacman_last_position.second = y;
            }
            else if(tile == '1'){
                walls.push_back(Wall{x, y, block_size}); //TODO: Need to modify this to accept block size of certain length and width

            }else if(tile == '2'){
                walls.push_back(Wall{x, y, block_size});

            }else{
                std::cout << "Cannot be processed." << std::endl;
            }

            if(pacman_first_position.first == -1) {
                pacman_first_position.first = x;
                pacman_first_position.second = y;
            }
        }
    }
}

void Game::run(){
    // Initialize display
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        for(Wall& wall: walls){
            Rectangle rectangle = Rectangle{wall.getX(), wall.getY(), block_size, block_size};

            if(wall.getX() < (map.size()/2) * block_size){
                DrawRectangleRoundedLines(rectangle, 0.3, 2, BLUE);
            }else{
                DrawRectangleRoundedLines(rectangle, 0.3, 2, RED);
            }
        }

        for(Pellet& pellet: pellets){
            if(pacman_last_position == std::make_pair(pellet.getX() - (50/2), pellet.getY() - (50/2))){
                DrawRectangle(pellet.getX(), pellet.getY(), block_size, block_size, RED);
            }else{
                DrawCircle(pellet.getX(), pellet.getY(), radius, YELLOW);
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
}