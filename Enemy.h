#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <cmath> // For distance calculation

class Enemy : public Entity {
public:
    // Constructor allows us to create different types of enemies easily
    Enemy(string name, int x, int y, char icon, int hp, int atk) 
        : Entity(name, x, y, icon, "\033[31m", hp, atk) {} // Red color for enemies

    // Feature 5: Simple AI
    // Moves the enemy one step closer to the player
    // Note: We need the map to check for walls! 
    // For simplicity here, we just calculate the INTENT. 
    // The Game loop will check collisions.
    void getNextMove(int playerX, int playerY, int& dx, int& dy) {
        dx = 0;
        dy = 0;
        
        // Simple logic: If player is to the right, move right.
        if (x < playerX) dx = 1;
        else if (x > playerX) dx = -1;
        
        // If player is below, move down
        if (y < playerY) dy = 1;
        else if (y > playerY) dy = -1;
    }
};

#endif