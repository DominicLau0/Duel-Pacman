#include "gamestate.hh"

GameState::GameState(){
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
}

bool GameState::wallCollisionDetected(Vector2 pos, float radius)
{
    // Check pacman collision with wall
    for (auto &wall : walls)
    {
        if (CheckCollisionCircleRec(pos, radius, wall.getWall()))
        {
            return true;
        }
    }

    // Check pacman collision with 
    return false;
}

void GameState::checkPacmanPelletCollision(){
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

void GameState::processInput(){
    
}

void GameState::update(float dt){
    
}