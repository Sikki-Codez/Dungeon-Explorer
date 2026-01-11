#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

using namespace std;

class Entity {
protected:
    // "protected" means only this class and classes that inherit from it (Player/Enemy) can access these
    string name;
    int x, y;
    char icon;
    string color; // ANSI color code
    
    int health;
    int maxHealth;
    int attackPower;

public:
    // Constructor
    Entity(string n, int startX, int startY, char symbol, string c, int hp, int atk);

    // Core Actions
    // "dx" means "change in x". So dx=1 moves right, dx=-1 moves left.
    void move(int dx, int dy);
    void takeDamage(int dmg);
    void heal(int amount);
    bool isAlive();

    // Combat
    // We use a pointer (Entity*) so we can attack ANY entity (Player or Enemy)
    void attack(Entity* target);

    // Getters (Allow other files to READ data but not change it directly)
    int getX() const { return x; }
    int getY() const { return y; }
    char getIcon() const { return icon; }
    string getColor() const { return color; }
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getAttackPower() const { return attackPower; }
    
    // Setters (For teleporting or forcing position)
    void setPosition(int newX, int newY) { x = newX; y = newY; }
};

#endif