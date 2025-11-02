// #ifndef DEMO_H
// #define DEMO_H

// #include "raylib.h"
// #include "StoreScene.h"
// #include "../Backend/Player.h"
// #include "../Backend/Game.h"
// #include <iostream>

// class Demo {
// private:
//     // Subsystems
//     Game game;
//     StoreScene store;
//     Player* player;
    
//     // Window configuration
//     const int width = 1400;
//     const int height = 900;
    
//     // Private helper methods - hide implementation details
//     void initializeWindow();
//     void setupTestInventory();
//     void displayControls();
//     void handleInput();
//     void update();
//     void render();
    
// public:
//     Demo();
//     ~Demo();
    
//     // Main facade interface - simplified single method
//     void run();
    
//     // Optional: Getters if needed
//     Player* getPlayer() const { return player; }
//     StoreScene* getStore() { return &store; }
//     int getWidth() const { return width; }
//     int getHeight() const { return height; }
// };

// #endif

#ifndef DEMO_H
#define DEMO_H

#include "raylib.h"
#include "StoreScene.h"
#include "SceneManager.h" 
#include "../Backend/Player.h"
#include "../Backend/Game.h"
#include <iostream>

class Demo {
private:
    // Subsystems
    Game game;
    StoreScene store; 
    Player* player;
    SceneManager manager; 
    
    // Window configuration
    const int width = 1400;
    const int height = 900;
    
    // Private helper methods
    void initializeWindow();
    void setupTestInventory();
    void displayControls();
    
public:
    Demo();
    ~Demo();
    
    // Main facade interface
    void run();
    
    // Optional: Getters if needed
    Player* getPlayer() const { return player; }
    StoreScene* getStore() { return &store; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif