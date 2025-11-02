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
    
    SceneManager manager;
    
    bool exitWindow = false;

    // Main game loop
    while (!exitWindow) {
        if (WindowShouldClose()) {
            exitWindow = true;
        }

        float dt = GetFrameTime();
        
        Game::getInstance(); 
        
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