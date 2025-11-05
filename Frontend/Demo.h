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