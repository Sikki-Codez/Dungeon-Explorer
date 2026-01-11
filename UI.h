#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include <string>
#include "Player.h" // Needed to recognize 'Player' object

using namespace std;

class UI {
private:
    vector<string> messageLog;
    // We can't initialize constants inside class bodies in older C++ versions easily
    // so we will just use a hardcoded check in the .cpp file or a simple int
    int maxLogLines; 

public:
    UI(); // Constructor

    void clearScreen();
    void drawHUD(const Player& player, int enemyCount);
    void log(string message);
    void drawLog();
    void drawTitleScreen();
    void drawGameOver();
};

#endif