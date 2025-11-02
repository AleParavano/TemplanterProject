#include "raylib.h"
#include "SceneManager.h" 
#include "../Backend/Game.h"
#include "../Backend/Player.h" 
#include "UI.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


int main(void) {
    const int screenWidth = SCREEN_WIDTH; 
    const int screenHeight = SCREEN_HEIGHT; 

    InitWindow(screenWidth, screenHeight, "TEMPLANTER - Top-Down Simulation");
    
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

    Game::getInstance(); 
    Game::getInstance()->getPlayer().addMoney(10000000000);
    
    SceneManager manager;
    
    bool exitWindow = false;

    // Main game loop
    while (!exitWindow) {
        if (WindowShouldClose()) {
            exitWindow = true;
        }

        float dt = GetFrameTime();
        
        Game::getInstance()->getPlayer().UpdateGameTime(dt); 
        
        manager.Update(dt);
        manager.HandleInput();

        if (manager.IsDone()) {
            exitWindow = true;
        }
        manager.Draw();
    }

    CloseWindow();
    return 0;
}