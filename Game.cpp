#include "Game.h"

Game::Game() : map(40, 20), player(5, 5) {
    isRunning = true;
    map.generateProcedural();
    spawnEnemies();
    
    // Optional: Show title screen before starting
    ui.drawTitleScreen();
    _getch(); // Wait for key press
}

void Game::spawnEnemies() {
    enemies.clear();
    for(int i=0; i<3; i++) {
        int ex = 10 + (rand() % 20);
        int ey = 5 + (rand() % 10);
        if(map.isWalkable(ex, ey)) {
            enemies.push_back(Enemy("Goblin", ex, ey, 'G', 30, 5));
        }
    }
}

void Game::run() {
    while (isRunning && player.isAlive()) {
        
        // 1. UI: Clear Screen
        ui.clearScreen(); 

        // 2. UI: Draw Top HUD
        ui.drawHUD(player, enemies.size());

        // 3. MAP: Draw the world
        map.draw(&player, enemies);

        // 4. UI: Draw Bottom Log
        ui.drawLog();

        handleInput();
        update();
    }
    
    // End Game Screen
    ui.drawGameOver();
    _getch();
}

void Game::handleInput() {
    // No need to cout instructions here, the HUD/Log covers it
    // But you can add a prompt if you want
    char input = _getch();
    
    if (tolower(input) == 'q') { isRunning = false; return; }

    int dx = 0, dy = 0;
    switch (tolower(input)) {
        case 'w': dy = -1; break;
        case 's': dy = 1; break;
        case 'a': dx = -1; break;
        case 'd': dx = 1; break;
        case ' ': 
             // LOGGING ATTACK
             ui.log("You swing your weapon!"); // <--- LOGGING
             for(auto& e : enemies) {
                 if(abs(e.getX() - player.getX()) <= 1 && abs(e.getY() - player.getY()) <= 1) {
                     player.attack(&e);
                     ui.log("You hit the Goblin!"); // <--- LOGGING
                 }
             }
             return; 
    }

    int nextX = player.getX() + dx;
    int nextY = player.getY() + dy;

    if (map.isWalkable(nextX, nextY)) {
        bool blocked = false;
        for(auto& e : enemies) {
            if(e.isAlive() && e.getX() == nextX && e.getY() == nextY) {
                blocked = true;
                player.attack(&e);
                ui.log("You bump into a Goblin and attack!"); // <--- LOGGING
            }
        }
        
        if (!blocked) {
            player.move(dx, dy);
        }
    } else {
        ui.log("You walked into a wall."); // <--- LOGGING
    }
}

void Game::update() {
    for (auto& e : enemies) {
        if (!e.isAlive()) continue;

        int dx, dy;
        e.getNextMove(player.getX(), player.getY(), dx, dy);
        
        int nextX = e.getX() + dx;
        int nextY = e.getY() + dy;

        if (map.isWalkable(nextX, nextY)) {
            if (nextX == player.getX() && nextY == player.getY()) {
                e.attack(&player);
                ui.log("The Goblin hits you!"); // <--- LOGGING
            } else {
                bool occupied = false;
                for(auto& other : enemies) {
                    if(&other != &e && other.getX() == nextX && other.getY() == nextY) occupied = true;
                }
                if(!occupied) e.move(dx, dy);
            }
        }
    }

    // Clean up dead enemies
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!it->isAlive()) {
            player.gainXP(20); 
            ui.log("Enemy died! You gained 20 XP."); // <--- LOGGING
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }

    if (map.isTrap(player.getX(), player.getY())) {
        player.takeDamage(10);
        ui.log("IT'S A TRAP! Took 10 damage."); // <--- LOGGING
    }
}