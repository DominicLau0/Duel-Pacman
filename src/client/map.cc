#include "map.hh"
#include <iostream>

Map::Map(){
    layout = {
        "11111111111111111111111111111",
        "1                           1",
        "1   111111111         11  111",
        "1   1                 1     1",
        "1   1     1   2       1     1",
        "1         111  111          1",
        "1   1            1    1111  1",
        "1   1      1                1",
        "1   11111111    1111     1  1",
        "1               1        1  1",
        "11111111111111111111111111111"
    };

    create_map();
}

void Map::create_map(){
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

    for (int row = 0; row < layout.size(); row++){
        for(int column = 0; column < layout[row].size(); column++){
            int tile = layout[row][column];

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
                if(layout[row][column] != ' '){
                    float x = column * block_size;
                    float y = row * block_size;
    
                    // Choose a color based on horizontal position.
                    Color color = (x < ((int)layout[row].size()/2 * block_size)) ? BLUE : RED;
    
                    // For each side, check if the neighboring cell is not a wall.
                    // Left side: if at left edge or left neighbor is empty.
                    if(column == 0 || layout[row][column-1] == ' '){
                        walls.push_back(Wall(Vector2 {x, y}, Vector2 {x, y + block_size}, color));
                    }
                    // Right side: if at right edge or right neighbor is empty.
                    if(column == layout[row].size()-1 || layout[row][column+1] == ' '){
                        walls.push_back(Wall(Vector2 {x + block_size, y}, Vector2 {x + block_size, y + block_size}, color));
                    }
                    // Top side: if at top edge or the above neighbor is empty.
                    if(row == 0 || layout[row-1][column] == ' '){
                        walls.push_back(Wall(Vector2 {x, y}, Vector2 {x + block_size, y}, color));
                    }
                    // Bottom side: if at bottom edge or the below neighbor is empty.
                    if(row == layout.size()-1 || layout[row+1][column] == ' '){
                        walls.push_back(Wall(Vector2 {x, y + block_size}, Vector2 {x + block_size, y + block_size}, color));
                    }
                }
            }else if(tile == '2'){
                ghost.setX(x);
                ghost.setY(y);
            }else{
                std::cout << "Cannot be processed." << std::endl;
            }
        }
    }
}

void Map::draw(){
    
}