#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm> // For std::fill

// Forward declarations to avoid circular dependency issues
// (We include the headers in the .cpp file usually, or here if needed for pointers)
#include "Player.h" 
#include "Enemy.h"  

using namespace std;

// Color Constants
const string C_RESET  = "\033[0m";
const string C_WALL   = "\033[90m"; // Dark Gray
const string C_TRAP   = "\033[31m"; // Red
const string C_FLOOR  = "\033[37m"; // White/Light Gray 

class Map {
private:
    vector<string> grid;            // Stores '#' or '_'
    vector<vector<bool>> visited;   // Fog of War memory
    vector<pair<int, int>> traps;   
    
    int width;
    int height;

public:
    Map(int w, int h);
    
    // Core Generation
    void generateProcedural(); 
    
    // Helpers
    bool isTrap(int x, int y); 
    void addTrap(int x, int y);
    char getTile(int x, int y);
    bool isWalkable(int x, int y);
    bool isVisible(int pX, int pY, int tX, int tY, int radius);

    // The Render Function
    void draw(Player* player, vector<Enemy>& enemies);
};

#endif