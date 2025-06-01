#include "game.hh"
#include <iostream>

Game::Game()
{
    map = {
        "11111111111111111111111",
        "1B         1          1",
        "1 111 1111 1 1111 111 1",
        "1        1 1 1        1",
        "1111 111 1   1 111 1111",
        "1      1 1 1 1 1      1",
        "1  111 1   1   1 111  1",
        "1    1 1 11111 1 1    1",
        "1    1           1    1",
        "1    1 11      1 1    1",
        "1                    R1",
        "11111111111111111111111"};

    // Initialize and create pacman objects.
    for (int i = 0; i < pacman_amount; i++)
    {
        pacmans.push_back(Pacman());
        pacmans[i].setColor(pacman_colors[i]);
    }

    create_map();
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
            else if (tile == '2')
            {
                // Set the location of the ghosts
                ghost.setX(x);
                ghost.setY(y);
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

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Dual Pacman");

    Image img = LoadImage("sprites/PinkGhost_Down.png");
    ImageResize(&img, 20, 20);
    ghost.loadTexture(img);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the walls and pellets
        draw_walls();
        checkPacmanPelletCollision();
        draw_pellets();

        Vector2 blue_pacman_direction = Vector2{float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A)),
                                                float(IsKeyDown(KEY_S)) - float(IsKeyDown(KEY_W))};
        Vector2 red_pacman_direction = Vector2{float(IsKeyDown(KEY_RIGHT)) - float(IsKeyDown(KEY_LEFT)),
                                               float(IsKeyDown(KEY_DOWN)) - float(IsKeyDown(KEY_UP))};

        // Only update direction if a movement key is pressed
        // Blue Pacman
        if (IsKeyPressed(KEY_W))
        {
            pacmans[0].setDirection({0, -1});
        }
        else if (IsKeyPressed(KEY_S))
        {
            pacmans[0].setDirection(Vector2{0, 1});
        }
        else if (IsKeyPressed(KEY_A))
        {
            pacmans[0].setDirection(Vector2{-1, 0});
        }
        else if (IsKeyPressed(KEY_D))
        {
            pacmans[0].setDirection(Vector2{1, 0});
        }

        // Red Pacman
        if (IsKeyPressed(KEY_UP))
        {
            pacmans[1].setDirection(Vector2{0, -1});
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            pacmans[1].setDirection(Vector2{0, 1});
        }
        else if (IsKeyPressed(KEY_LEFT))
        {
            pacmans[1].setDirection(Vector2{-1, 0});
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            pacmans[1].setDirection(Vector2{1, 0});
        }

        float dt = GetFrameTime();

        // Draw the pacmans
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

        // Update ghost movement;
        ghost.update();
        ghost.draw();

        // Update the pacmans score.
        DrawText(TextFormat("%i", pacmans[0].getScore()), map[0].size() * block_size, map.size() * block_size, 30, BLUE);
        DrawText(TextFormat("%i", pacmans[1].getScore()), map[0].size() * block_size + 30, map.size() * block_size, 30, RED);

        EndDrawing();
    }

    CloseWindow();
}