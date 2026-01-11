#include "Map.h"

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height, string(width, '#'));
    visited.resize(height, vector<bool>(width, false));
}

void Map::generateProcedural() {
    // 1. Fill world with walls ('#')
    for (int y = 0; y < height; y++) {
        fill(grid[y].begin(), grid[y].end(), '#');
    }
    traps.clear();

    // 2. Dig Rooms
    int roomCount = 6 + (rand() % 5);
    for (int i = 0; i < roomCount; i++) {
        int rW = 4 + (rand() % 4);
        int rH = 3 + (rand() % 4);
        int rX = 1 + (rand() % (width - rW - 1));
        int rY = 1 + (rand() % (height - rH - 1));

        for (int y = rY; y < rY + rH; y++) {
            for (int x = rX; x < rX + rW; x++) {
                grid[y][x] = '_'; // <--- CHANGED TO UNDERSCORE
            }
        }
        
        // Add random traps
        if (rand() % 5 == 0) addTrap(rX + 1, rY + 1);
    }

    // 3. Dig Tunnels
    for (int i = 0; i < 15; i++) {
        int rX = 1 + (rand() % (width - 2));
        int rY = 1 + (rand() % (height - 2));
        
        // Horizontal tunnel
        if(rand() % 2 == 0) {
             for(int k=0; k<10 && rX+k < width-1; k++) {
                 grid[rY][rX+k] = '_'; // <--- CHANGED TO UNDERSCORE
             }
        }
        // Vertical tunnel
        else {
             for(int k=0; k<10 && rY+k < height-1; k++) {
                 grid[rY+k][rX] = '_'; // <--- CHANGED TO UNDERSCORE
             }
        }
    }
}

void Map::addTrap(int x, int y) {
    traps.push_back({x, y});
}

bool Map::isTrap(int x, int y) {
    for (auto& t : traps) {
        if (t.first == x && t.second == y) return true;
    }
    return false;
}

char Map::getTile(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height)
        return grid[y][x];
    return '#';
}

bool Map::isWalkable(int x, int y) {
    // We check if it is NOT a wall. 
    // Since floor is '_', this logic still works perfectly.
    return getTile(x, y) != '#';
}

bool Map::isVisible(int pX, int pY, int tX, int tY, int radius) {
    float distance = sqrt(pow(tX - pX, 2) + pow(tY - pY, 2));
    return distance <= radius;
}

void Map::draw(Player* player, vector<Enemy>& enemies) {
    int viewRadius = 6;
    int pX = player->getX();
    int pY = player->getY();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            bool visible = isVisible(pX, pY, x, y, viewRadius);
            
            if (visible) {
                visited[y][x] = true; // Mark as seen

                // Priority 1: Player
                if (x == pX && y == pY) {
                    cout << player->getColor() << player->getIcon() << C_RESET;
                }
                // Priority 2: Enemies
                else {
                    bool enemyDrawn = false;
                    for (auto& e : enemies) {
                        if (e.isAlive() && e.getX() == x && e.getY() == y) {
                            cout << e.getColor() << e.getIcon() << C_RESET;
                            enemyDrawn = true;
                            break;
                        }
                    }
                    // Priority 3: Map Features
                    if (!enemyDrawn) {
                        if (isTrap(x, y)) {
                            cout << C_TRAP << "^" << C_RESET;
                        } else {
                            // Draw '_' for floor, '#' for wall
                            if (grid[y][x] == '#') cout << C_WALL << "#" << C_RESET;
                            else cout << C_FLOOR << "_" << C_RESET;
                        }
                    }
                }
            } 
            else if (visited[y][x]) {
                // FOG MEMORY: We have seen this before, but can't see it now.
                // We draw it in dark gray.
                cout << C_WALL << grid[y][x] << C_RESET; 
            } 
            else {
                // TOTAL DARKNESS: Never seen.
                cout << " "; 
            }
        }
        cout << endl;
    }
}