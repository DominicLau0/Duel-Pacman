#include "game.hh"
#include <iostream>

Game::Game()
{
    map = {
        "111111111111111111111",
        "1 B       1         1",
        "1 111 111 1 111 111 1",
        "1       1 1 1       1",
        "111 111 1   1 111 111",
        "1     1 1 1 1 1     1",
        "1 111 1   1   1 111 1",
        "1   1 1 11111 1 1   1",
        "111 1           1 111",
        "1 1 1 1 11X11 1 1 1 1",
        "1     1 1OGP1 1     1",
        "111 111 11111 111 111",
        "1                   1",
        "1 111 1 11111 1 111 1",
        "1 1   1   1   1   1 1",
        "1 1 11111 1 11111 1 1",
        "1                   1",
        "11111 1 11111 1 11111",
        "1     1   1   1     1",
        "1 1111111 1 1111111 1",
        "1         1       R 1",
        "111111111111111111111"};

    // Initialize and create pacman objects.
    for (int i = 0; i < pacman_amount; i++)
    {
        pacmans.push_back(Pacman());
        pacmans[i].setColor(pacman_colors[i]);
    }

    create_map();

    // Set screen width and height.
    screenWidth = map[0].size() * block_size - block_size / 2;
    screenHeight = map.size() * block_size - block_size / 2 + 30;
}

Game::~Game()
{
}

void Game::create_map()
{
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

    for (int row = 0; row < map.size(); row++)
    {
        for (int column = 0; column < map[row].size(); column++)
        {
            int tile = map[row][column];

            float x = column * block_size;
            float y = row * block_size;

            if (tile == ' ')
            {
                // Draw the pellets
                pellets.push_back(Pellet({x, y}, false));
            }
            else if (tile == '1')
            {
                // Draw the walls
                if (map[row][column] != ' ')
                {
                    Color color = (x < ((int)map[row].size() / 2 * block_size)) ? TEAL : DARKGOLD;

                    if (column + 1 < map[row].size() && map[row][column + 1] == '1')
                    {
                        // Check if there's a wall to the right of the wall
                        walls.push_back(Wall(x,
                                             y,
                                             block_size,
                                             block_size / 2,
                                             color));
                    }

                    if (row + 1 < map.size() && map[row + 1][column] == '1')
                    {
                        // Check if there's a wall to the bottom of the wall
                        walls.push_back(Wall(x,
                                             y,
                                             block_size / 2,
                                             block_size,
                                             color));
                    }

                    walls.push_back(Wall(x,
                                         y,
                                         block_size / 2,
                                         block_size / 2,
                                         color));
                }
            }
            else if (tile == 'X')
            {
                // Set the location of the ghosts
                ghosts[0].setCoordinate({x, y});
            }
            else if (tile == 'O')
            {
                // Set the location of the ghosts
                ghosts[1].setCoordinate({x, y});
            }
            else if (tile == 'G')
            {
                // Set the location of the ghosts
                ghosts[2].setCoordinate({x, y});
            }
            else if (tile == 'P')
            {
                // Set the location of the ghosts
                ghosts[3].setCoordinate({x, y});
            }
            else if (tile == 'B')
            {
                pacmans[0].setCoordinate({x, y});
            }
            else if (tile == 'R')
            {
                pacmans[1].setCoordinate({x, y});
            }
            else
            {
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

void Game::draw_walls()
{
    /**
     * Draw the walls of the game
     *
     * '0' represents no wall.
     * '1' represents a wall.
     *
     * Stores the created walls in the vector wall.
     *
     * @param values None
     * @return None
     */

    // Iterate through each cell in the map
    for (auto &wall : walls)
    {
        DrawRectangleRec(wall.getWall(), wall.getColor());
    }
}

void Game::draw_pellets()
{
    for (auto &pellet : pellets)
    {
        DrawCircle(pellet.getCoordinate().x + block_size / 2, pellet.getCoordinate().y + block_size / 2, radius, BEIGE);
    }
}

bool Game::wallCollisionDetected(Vector2 pos, float radius)
{
    for (auto &wall : walls)
    {
        if (CheckCollisionCircleRec(pos, radius, wall.getWall()))
        {
            return true;
        }
    }
    return false;
}

bool Game::wallCollisionDetected(Rectangle pos)
{
    for (auto &wall : walls)
    {
        if (CheckCollisionRecs(pos, wall.getWall()))
        {
            return true;
        }
    }
    return false;
}

void Game::checkPacmanPelletCollision()
{
    /**
     * Check if there's a collision between any of the pellets.
     * Remove pellets if the pacman collides with the pellets.
     *
     * @param values None
     * @return None
     */

    for (Pacman &pacman : pacmans)
    {
        // For each Pacman, check if there's a collision between any of the pellets
        for (auto it = pellets.begin(); it != pellets.end();)
        {
            bool collision = CheckCollisionCircles(
                pacman.getCoordinate(),
                pacman.getRadius(),
                Vector2{
                    it->getCoordinate().x + block_size / 2,
                    it->getCoordinate().y + block_size / 2},
                radius);

            // Remove pellets if the pacman collides with the pellets.
            if (collision == true)
            {
                it = pellets.erase(it);
                pacman.setScore(pacman.getScore() + 1);
            }
            else
            {
                ++it;
            }
        }
    }
}

void Game::draw_scoreboard(){
    DrawRectangle(0,
        map.size() * block_size - block_size / 2,
        map[0].size() * block_size - block_size / 2,
        30,
        DARKBROWN);

    DrawText(TextFormat("Score: "),
        0,
        map.size() * block_size - block_size / 2,
        25,
        BEIGE);
    DrawText(TextFormat("%03i", pacmans[0].getScore()),
        (map[0].size() * block_size) / 4,
        map.size() * block_size - block_size / 2,
        30,
        BLUE);
    DrawText(TextFormat("%03i", pacmans[1].getScore()),
        (map[0].size() * block_size) * 0.60,
        map.size() * block_size - block_size / 2,
        30,
        RED);
}

void Game::initializeGhosts(){
    for (int i = 0; i < ghost_amount; i++)
    {
        Rectangle source = Rectangle{spriteStartingX, spriteStartingY + ((spriteSize + 2) * i), spriteSize, spriteSize};
        Rectangle dest = Rectangle{ghosts[i].getCoordinate().x, ghosts[i].getCoordinate().y, spriteSize, spriteSize};
        
        ghosts.push_back(Ghost(texture, source, dest));
    }
}

void Game::run()
{
    /**
     * Run the program
     * Return true if the colors are the same
     *
     * c1 represents the first color
     * c2 represents the second color
     *
     * Stores the created walls in the vector wall.
     *
     * @param none
     * @return True if the colors are the same, else False.
     */

    if(!clientNetwork.connect("127.0.0.1", 3000)){
        return;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Duel Pacman");

    texture = LoadTexture("sprites/sprites.png");
    initializeGhosts();

    while (!WindowShouldClose())
    {
        // Send data to server
        PlayerInput input;

        if (IsKeyPressed(KEY_W))
        {
            input.dx = 0;
            input.dy = -1;
        }
        else if (IsKeyPressed(KEY_S))
        {
            input.dx = 0;
            input.dy = 1;
        }
        else if (IsKeyPressed(KEY_A))
        {
            input.dx = -1;
            input.dy = 0;
        }
        else if (IsKeyPressed(KEY_D))
        {
            input.dx = 1;
            input.dy = 0;
        }

        input.id = CLIENT_ID;

        clientNetwork.sendInputPacket(input);

        // Poll data from server
        clientNetwork.poll();

        for(){
            
        }

        // Update
        

        // Render

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the walls and pellets
        draw_walls();
        checkPacmanPelletCollision();
        draw_pellets();

        float dt = GetFrameTime();

        if (dt > 0.1f)
        {
            dt = 0.1f;
        }

        // Draw and update pacmans
        for (int i = 0; i < pacmans.size(); i++)
        {
            // Update the x position if no collision detected.
            Vector2 testPosition = pacmans[i].getCoordinate();
            testPosition.x += pacmans[i].getDirection().x * pacmans[i].getSpeed() * dt;

            if (!wallCollisionDetected(testPosition, pacmans[i].getRadius()))
            {
                pacmans[i].update_x(dt);
            }

            // Update the y position if no collision detected.
            testPosition = pacmans[i].getCoordinate();
            testPosition.y += pacmans[i].getDirection().y * pacmans[i].getSpeed() * dt;

            if (!wallCollisionDetected(testPosition, pacmans[i].getRadius()))
            {
                pacmans[i].update_y(dt);
            }

            pacmans[i].draw();
        }

        // Draw and update ghosts;
        for (int i = 0; i < ghosts.size(); i++)
        {
            // Update the x position if no collision detected.
            Rectangle testPosition = ghosts[i].getCoordinate();
            testPosition.x += ghosts[i].generateDirection().x * ghosts[i].getSpeed() * dt;

            if (!wallCollisionDetected(testPosition))
            {
                ghosts[i].update_x(dt);
            }

            // Update the y position if no collision detected.
            testPosition = ghosts[i].getCoordinate();
            testPosition.y += ghosts[i].generateDirection().y * ghosts[i].getSpeed() * dt;

            if (!wallCollisionDetected(testPosition))
            {
                ghosts[i].update_y(dt);
            }

            ghosts[i].draw();
        }

        // Draw scoreboard
        draw_scoreboard();

        EndDrawing();
    }

    CloseWindow();
}