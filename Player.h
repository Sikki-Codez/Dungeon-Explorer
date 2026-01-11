#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    int level;
    int xp;
    int xpToNextLevel;

public:
    // Constructor: We pass specific values up to the Entity constructor
    // Player is always '@', White/Green color, starts with 100 HP
    Player(int startX, int startY) 
        : Entity("Hero", startX, startY, '@', "\033[92m", 100, 10) 
    {
        level = 1;
        xp = 0;
        xpToNextLevel = 50;
    }

    void gainXP(int amount) {
        xp += amount;
        if (xp >= xpToNextLevel) {
            levelUp();
        }
    }

    void levelUp() {
        level++;
        xp = 0;
        xpToNextLevel *= 1.5; // Harder to get next level
        maxHealth += 20;
        health = maxHealth;   // Full heal on level up
        attackPower += 2;
        // You could print a "Level Up!" message here
    }

    int getLevel() const { return level; }
};

#endif