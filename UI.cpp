#include "UI.h"
#include <iostream> // <--- REQUIRED for cout
#include <cstdlib>  // <--- REQUIRED for system()

using namespace std; // <--- REQUIRED to use string, cout, endl

UI::UI() {
    maxLogLines = 5; // Set the limit
    log("Welcome to the Dungeon.");
    log("Find the exit... if you can.");
}

void UI::clearScreen() {
    // Check if we are on Windows or Linux/Mac
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UI::drawHUD(const Player& player, int enemyCount) {
    cout << "\033[92m"; // Green
    cout << "========================================" << endl;
    cout << " HP: " << player.getHealth() << " / 100" 
         << "  |  Lvl: " << player.getLevel()
         << "  |  Enemies: " << enemyCount << endl;
    cout << "========================================" << endl;
    cout << "\033[0m"; // Reset
}

void UI::log(string message) {
    messageLog.push_back(message);
    if (messageLog.size() > maxLogLines) {
        messageLog.erase(messageLog.begin());
    }
}

void UI::drawLog() {
    cout << "\n--- Game Log ---------------------------" << endl;
    cout << "\033[90m"; // Gray
    for (const string& msg : messageLog) {
        cout << " > " << msg << endl;
    }
    cout << "\033[0m"; 
}

void UI::drawTitleScreen() {
    clearScreen();
    cout << "\033[93m"; // Yellow
    cout << "  ____                               on \n";
    cout << " |  _ \\ _   _ _ __   __ _  ___  ___  _ __ \n";
    cout << " | | | | | | | '_ \\ / _` |/ _ \\/ _ \\| '_ \\ \n";
    cout << " | |_| | |_| | | | | (_| |  __/ (_) | | | |\n";
    cout << " |____/ \\__,_|_| |_|\\__, |\\___|\\___/|_| |_|\n";
    cout << "                    |___/                  \n";
    cout << "\033[0m";
    cout << "\n      Press any key to start...";
}

void UI::drawGameOver() {
    clearScreen();
    cout << "\033[31m"; // Red
    cout << "\n\n      YOU HAVE DIED.\n\n";
    cout << "\033[0m";
}