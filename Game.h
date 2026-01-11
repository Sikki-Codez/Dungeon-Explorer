#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"    // <--- INCLUDE THIS
#include <vector>
#include <conio.h> 

using namespace std;

class Game {
private:
    Map map;
    Player player;
    vector<Enemy> enemies;
    UI ui;         // <--- ADD THIS OBJECT
    bool isRunning;

public:
    Game(); 
    void run();
    void handleInput(); 
    void update();
    void spawnEnemies();
};

#endif