#include "game.hh"

constexpr int TICK_RATE = 60;
constexpr double TICK_TIME = 1.0 / TICK_RATE;

constexpr double SNAPSHOT_RATE = 20.0;
constexpr double SNAPSHOT_DT = 1.0 / SNAPSHOT_RATE;

Game::Game(){
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
        "111111111111111111111"
    };

    create_map();
}

void Game::create_map()
{
    // Creates the layout of the pacman game.
    // '1' represents a wall.

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
                pellets.push_back(Pellet{x, y, false});
            }
            else if (tile == '1')
            {
                // Draw the walls
                if (column + 1 < map[row].size() && map[row][column + 1] == '1')
                {
                    // Check if there's a wall to the right of the wall
                    walls.push_back(Wall{x, y, block_size, block_size/2});
                }

                if (row + 1 < map.size() && map[row + 1][column] == '1')
                {
                    // Check if there's a wall to the bottom of the wall
                    walls.push_back(Wall{x, y, block_size/2, block_size});
                }

                walls.push_back(Wall{x, y, block_size / 2, block_size / 2});
            }
            else if (tile == 'X' || tile == 'O' || tile == 'G' || tile == 'P'){
                // Set the location of the ghosts
                ghosts.push_back(Ghost{x, y});
            }
            else if (tile == 'B' || tile == 'R'){
                // Set location of the pacman
                pacmans.push_back(Pacman{x, y});
            }
            else{
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

bool checkCollisionCircleRec(Vector2 circle, float radius, struct Rectangle rect){
    float closestX = std::max(rect.x, std::min(circle.x, rect.x + rect.width));
    float closestY = std::max(rect.y, std::min(circle.y, rect.y + rect.height));

    float dx = circle.x - closestX;
    float dy = circle.y - closestY;

    return (dx * dx + dy * dy) <= (radius * radius);
};

bool checkCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2){
    float dx = center1.x - center2.x;
    float dy = center1.y - center2.y;

    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = radius1 + radius2;

    return distanceSquared <= radiusSum * radiusSum;
};

bool Game::wallCollisionDetected(Vector2 pos, float radius)
{
    // Check pacman collision with wall
    for (auto &wall : walls){
        if (checkCollisionCircleRec(pos, radius, wall)){
            return true;
        }
    }

    // Check pacman collision with 
    return false;
}

void Game::checkPacmanPelletCollision(){
        /**
     * Check if there's a collision between any of the pellets.
     * Remove pellets if the pacman collides with the pellets.
     *
     * @param values None
     * @return None
     */

    for (Pacman &pacman : pacmans){
        // For each Pacman, check if there's a collision between any of the pellets
        for (auto it = pellets.begin(); it != pellets.end();){
            Vector2 pelletCenter{it->coordinate.x + block_size / 2, it->coordinate.y + block_size / 2};

            bool collision = checkCollisionCircles(
                pacman.coordinate,
                pacman.radius,
                pelletCenter,
                radius
            );

            // Remove pellets if the pacman collides with the pellets.
            if (collision == true)
            {
                it = pellets.erase(it);
                pacman.score = pacman.score + 1;
            }
            else
            {
                ++it;
            }
        }
    }
}

void Game::simulateGame(float dt){
    checkPacmanPelletCollision();

    if (dt > 0.1f)
    {
        dt = 0.1f;
    }

    // Draw and update pacmans
    for (int i = 0; i < pacmans.size(); i++)
    {
        // Update the x position if no collision detected.
        Vector2 testPosition = pacmans[i].coordinate;
        testPosition.x += pacmans[i].direction.x * pacmans[i].speed * dt;

        if (!wallCollisionDetected(testPosition, pacmans[i].radius))
        {
            pacmans[i].coordinate.x += testPosition.x;
        }

        // Update the y position if no collision detected.
        testPosition = pacmans[i].coordinate;
        testPosition.y += pacmans[i].direction.y * pacmans[i].speed * dt;

        if (!wallCollisionDetected(testPosition, pacmans[i].radius))
        {
            pacmans[i].coordinate.y += testPosition.y;
        }
    }

    // Draw and update ghosts;
    for (int i = 0; i < ghosts.size(); i++)
    {
        // Update the x position if no collision detected.
        Rectangle testPosition = ghosts[i].coordinate;
        testPosition.x += generateDirection().x * ghosts[i].speed * dt;

        if (!wallCollisionDetected(testPosition, pacmans[i].radius))
        {
            ghosts[i].coordinate.x += testPosition.x;
        }

        // Update the y position if no collision detected.
        testPosition = ghosts[i].coordinate;
        testPosition.y += generateDirection().y * ghosts[i].speed * dt;

        if (!wallCollisionDetected(testPosition, pacmans[i].radius))
        {
            ghosts[i].coordinate.y += testPosition.y;
        }
    }
}

Vector2 Game::generateDirection()
{
    int dir = rand() % 4;

    if (dir == 0)
    {
        return {0, -1};
    }
    else if (dir == 1)
    {
        return {0, 1};
    }
    else if (dir == 2)
    {
        return {-1, 0};
    }
    else
    {
        return {1, 0};
    }
};

void Game::run(){
    bool running = true;

    // Start
    start(uint16_t port, size_t maxClients, size_t channels)

    // Set time
    using clock = std::chrono::steady_clock;

    auto previousTime = clock::now();
    double accumulator = 0.0;

    while(running){
        auto currentTime = clock::now();

        double frameTime = std::chrono::duration<double>(currentTime - previousTime).count();

        previousTime = currentTime;

        // If there's a massive lag spike, reduce the frame time
        if(frameTime > 0.25){
            frameTime = 0.25;
        }

        accumulator += frameTime; // We want to accumulate the frametime until it hits the tick time.

        // Extract the data from 
        receivePackets(players);        

        // Simulate the tick
        while(accumulator >= TICK_TIME){
            simulateGame(static_cast<float>(TICK_TIME));
            accumulator -= TICK_TIME;
        }
    }
}