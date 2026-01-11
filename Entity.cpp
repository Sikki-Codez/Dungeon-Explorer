#include "Entity.h"

// Constructor implementation
Entity::Entity(string n, int startX, int startY, char symbol, string c, int hp, int atk) {
    name = n;
    x = startX;
    y = startY;
    icon = symbol;
    color = c;
    maxHealth = hp;
    health = hp;
    attackPower = atk;
}

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Entity::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Entity::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

bool Entity::isAlive() {
    return health > 0;
}

void Entity::attack(Entity* target) {
    if (target->isAlive()) {
        // Simple combat logic
        target->takeDamage(this->attackPower);
        // We could add a cout log here, but usually UI handles printing
    }
}