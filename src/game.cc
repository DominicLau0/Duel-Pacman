#include "game.hh"
#include <iostream>

Game::Game(){
    map = {
        "11111111111111111111111111111",
        "1                           1",
        "1   111111111         11  111",
        "1   1                 1     1",
        "1   1     1           1     1",
        "1         111  111          1",
        "1   1            1    1111  1",
        "1   1      1                1",
        "1   11111111    1111     1  1",
        "1               1        1  1",
        "11111111111111111111111111111"
    };

    block_size = 25;
    radius = 2;

    create_map();

    pacmans[0].setStartPoint(pacman_first_position);
    pacmans[1].setStartPoint(pacman_last_position);

    pacmans[0].setColor(BLUE);
    pacmans[1].setColor(RED);
}

Game::~Game(){

}

void Game::create_map(){
    /**
     * Creates the layout of the pacman game.
     * 
     * '0' represents no wall.
     * '1' represents a wall.
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

                pacman_last_position.x = x;
                pacman_last_position.y = y;

                if(pacman_first_position.x == -1) {
                    pacman_first_position.x = x;
                    pacman_first_position.y = y;
                }
            }
            else if(tile == '1'){
                if(map[row][column] != ' '){
                    float x = column * block_size;
                    float y = row * block_size;
    
                    // Choose a color based on horizontal position.
                    Color color = (x < ((int)map[row].size()/2 * block_size)) ? BLUE : RED;
    
                    // For each side, check if the neighboring cell is not a wall.
                    // Left side: if at left edge or left neighbor is empty.
                    if(column == 0 || map[row][column-1] == ' '){
                        walls.push_back(Wall(Vector2 {x, y}, Vector2 {x, y + block_size}, color));
                    }
                    // Right side: if at right edge or right neighbor is empty.
                    if(column == map[row].size()-1 || map[row][column+1] == ' '){
                        walls.push_back(Wall(Vector2 {x + block_size, y}, Vector2 {x + block_size, y + block_size}, color));
                    }
                    // Top side: if at top edge or the above neighbor is empty.
                    if(row == 0 || map[row-1][column] == ' '){
                        walls.push_back(Wall(Vector2 {x, y}, Vector2 {x + block_size, y}, color));
                    }
                    // Bottom side: if at bottom edge or the below neighbor is empty.
                    if(row == map.size()-1 || map[row+1][column] == ' '){
                        walls.push_back(Wall(Vector2 {x, y + block_size}, Vector2 {x + block_size, y + block_size}, color));
                    }
                }

            }else{
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

void Game::draw_walls(){
    // Iterate through each cell in the map
    for(auto& wall: walls){
        DrawLineEx(wall.getStartPosition(), wall.getEndPosition(), 2, wall.getColor());
    }
}

void Game::draw_pellets(){
    for(auto& pellet: pellets){
        DrawCircle(pellet.getX(), pellet.getY(), radius, YELLOW);
    }
}

bool Game::wallCollisionDetected(Vector2 pos, float radius){
    for(auto & wall: walls){
        if (CheckCollisionCircleLine(pos, radius, wall.getStartPosition(), wall.getEndPosition())){
            return true;
        }
    }
    return false;
}


bool Game::pelletCollisionDetected(Pacman pacman, Pellet pellet){
    return CheckCollisionCircles(pacman.getStartPoint(), pacman.getRadius(), Vector2{pellet.getX(), pellet.getY()}, radius);  
}

bool Game::colorsEqual(Color c1, Color c2){
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b &&c1.a == c2.a;
}

void Game::run(){
    // Initialize display
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Dual Pacman");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the walls and pellets
        draw_walls();
        draw_pellets();

        // Check for pacman collision on pellets.
        for(Pacman& pacman: pacmans){
            for(auto it = pellets.begin(); it != pellets.end();){
                if(pelletCollisionDetected(pacman, *it)==true){
                    it = pellets.erase(it);
                }else{
                    ++it;
                }
            }
        }

        Vector2 blue_pacman_direction = Vector2{float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A)),
                                                float(IsKeyDown(KEY_S)) - float(IsKeyDown(KEY_W))};
        Vector2 red_pacman_direction = Vector2{float(IsKeyDown(KEY_RIGHT)) - float(IsKeyDown(KEY_LEFT)),
                                                float(IsKeyDown(KEY_DOWN)) - float(IsKeyDown(KEY_UP))};

        //Draw pacman
        float dt = GetFrameTime();

        for(Pacman& pacman: pacmans){
            // Determine the correct direction based on color or input.
            Vector2 direction = (colorsEqual(pacman.getColor(), RED)) ? red_pacman_direction : blue_pacman_direction;

            pacman.setDirection(direction);
            
            // Compute a candidate new position for, say, the x-axis.
            Vector2 candidatePosition = pacman.getStartPoint();
            candidatePosition.x += direction.x * pacman.getSpeed() * dt;
            
            // If there's no collision predicted, update the x position.
            if(!wallCollisionDetected(candidatePosition, pacman.getRadius())){
                pacman.update_x(dt);
            }
            
            // Repeat the process for the y-axis independently if desired.
            candidatePosition = pacman.getStartPoint();
            candidatePosition.y += direction.y * pacman.getSpeed() * dt;
            if(!wallCollisionDetected(candidatePosition, pacman.getRadius())){
                pacman.update_y(dt);
            }
            
            pacman.draw();
        }
        
        
        EndDrawing();
    }

    CloseWindow();
}