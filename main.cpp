#include "raylib.h"
#include "Scene.h"
#include "OutdoorScene.h"
#include "GreenHouseScene.h"
#include "StoreScene.h"
#include "WarehouseScene.h"
#include "Backend/Game.h" 
#include "Backend/Player.h" 
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream> // For save/load confirmation

// --- Defines for Global Menu ---
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900
#define MENU_WIDTH 250 

// Forward declaration for the global drawing function
void DrawGlobalMenuTop(float screenWidth, float screenHeight); 

// --- Scene Manager Class ---
class SceneManager {
private:
    std::map<SceneType, Scene*> scenes;
    SceneType currentScene;
    SceneType nextScene;
    bool shouldExit;

public:
    SceneManager() : currentScene(SCENE_OUTDOOR), nextScene(SCENE_OUTDOOR), shouldExit(false) {
        // Create all scenes
        scenes[SCENE_OUTDOOR] = new OutdoorScene();
        scenes[SCENE_GREENHOUSE] = new GreenHouseScene();
        scenes[SCENE_STORE] = new StoreScene();
        scenes[SCENE_WAREHOUSE] = new WarehouseScene();

        // Initialize the starting scene
        scenes[currentScene]->Init();
    }

    ~SceneManager() {
        for (auto& pair : scenes) {
            delete pair.second;
        }
        scenes.clear();
    }

    void Update(float dt) {
        // The global time is updated in main(), so we only update the scene here.
        scenes[currentScene]->Update(dt);
    }

    void HandleInput() {
        scenes[currentScene]->HandleInput();
        
        // Check if scene wants to change
        nextScene = scenes[currentScene]->CheckExit();
        
        // If scene is changing, handle transition
        if (nextScene != currentScene) {
            currentScene = nextScene;
            scenes[currentScene]->Init(); // Re-initialize new scene
        }
        
        // --- Handle Global Menu Input (Save/Load) ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            float menuX = SCREEN_WIDTH - MENU_WIDTH;
            
            // Defined positions for Save/Load buttons (must match DrawGlobalMenuTop)
            Rectangle saveBtn = {menuX + 10, 200.0f, MENU_WIDTH - 20, 30};
            Rectangle loadBtn = {menuX + 10, 240.0f, MENU_WIDTH - 20, 30};

            if (CheckCollisionPointRec(mousePos, saveBtn)) {
                // Memento Save Logic
                Game::getInstance()->saveGame(); 
            }
            if (CheckCollisionPointRec(mousePos, loadBtn)) {
                // Memento Load Logic
                Game::getInstance()->loadGame();
            }
        }

        // Check for quit (Escape from outdoor scene only)
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (currentScene == SCENE_OUTDOOR) {
                shouldExit = true;
            } else {
                // Go back to outdoor scene
                currentScene = SCENE_OUTDOOR;
                scenes[currentScene]->Init();
            }
        }
    }

    void Draw() {
        BeginDrawing();
        
        // Clear background based on scene
        if (currentScene == SCENE_OUTDOOR) {
            ClearBackground({135, 206, 250, 255}); // Sky blue for outdoor
        } else if (currentScene == SCENE_GREENHOUSE) {
            ClearBackground({101, 67, 33, 255}); // Brown soil for greenhouse
        } else {
            ClearBackground({200, 200, 200, 255}); // Light gray for other scenes
        }
        
        // Draw the currently active scene
        scenes[currentScene]->Draw();
        
        // *** Draw the persistent Global Menu over the scene ***
        DrawGlobalMenuTop(SCREEN_WIDTH, SCREEN_HEIGHT);

        EndDrawing();
    }

    bool IsDone() const {
        return shouldExit;
    }
};

// --- Global Drawing Function for Persistent Menu ---
void DrawGlobalMenuTop(float screenWidth, float screenHeight) {
    //  Draw Menu Background (Translucent Black)
    float menuX = screenWidth - MENU_WIDTH;
    Color translucentBlack = {0, 0, 0, 180}; 
    
    DrawRectangle(menuX, 0, MENU_WIDTH, screenHeight, translucentBlack);
    DrawRectangleLinesEx({menuX, 0, MENU_WIDTH, screenHeight}, 3, LIGHTGRAY);
    
    // Get Global Data
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    if (player) {
        // --- CLOCK (Day, Hour, Minute) ---
        int clockY = 20;
        
        // Day
        DrawText(TextFormat("DAY: %d", player->getDay()), menuX + 10, clockY, 20, RAYWHITE);
        // Time
        DrawText(player->getTimeString().c_str(), menuX + 10, clockY + 25, 30, YELLOW);
        
        
        // --- PLAYER STATES (Money, Rating, Protection) ---
        int statsY = 90;
        
        // Money
        DrawText(TextFormat("Money: $%.2f", player->getMoney()), menuX + 10, statsY, 20, LIME);
        
        // Rating
        std::string ratingStr = TextFormat("Rating: %d", player->getRating());
        std::string starStr = std::string(player->getRating(), '*'); 
        DrawText((ratingStr + " " + starStr).c_str(), menuX + 10, statsY + 30, 20, GOLD);

        // Protection Status (Patrol Command integration)
        std::string protectionStr = player->isProtected() ? "🛡️ SAFE" : "⚠️ VULNERABLE";
        Color protectionColor = player->isProtected() ? GREEN : RED;
        DrawText(protectionStr.c_str(), menuX + 10, statsY + 60, 20, protectionColor);
        
        
        // --- SAVE/LOAD BUTTONS ---
        int buttonY = 200;
        Rectangle saveBtn = {menuX + 10, (float)buttonY, MENU_WIDTH - 20, 30};
        Rectangle loadBtn = {menuX + 10, (float)buttonY + 40, MENU_WIDTH - 20, 30};
        
        // Draw Save Button
        DrawRectangleRec(saveBtn, DARKGREEN);
        DrawText("SAVE GAME", saveBtn.x + (saveBtn.width - MeasureText("SAVE GAME", 20))/2, saveBtn.y + 5, 20, WHITE);
        
        // Draw Load Button
        DrawRectangleRec(loadBtn, MAROON);
        DrawText("LOAD GAME", loadBtn.x + (loadBtn.width - MeasureText("LOAD GAME", 20))/2, loadBtn.y + 45, 20, WHITE);
        
        // --- SEPARATOR LINE (Static position for scene-specific content) ---
        int separatorY = 300;
        DrawLine(menuX + 5, separatorY, menuX + MENU_WIDTH - 5, separatorY, LIGHTGRAY);
        
        // ---  (For the bottom half) ---
        DrawText("SCENE-SPECIFIC MENU BELOW", menuX + 10, separatorY + 10, 15, RAYWHITE);
    }
}


// --- Main Entry Point ---
int main(void) {
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "TEMPLANTER - Top-Down Simulation");
    
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

    // Initialize the Game Singleton early (sets initial time 07:00)
    Game::getInstance(); 
    
    SceneManager manager;
    
    bool exitWindow = false;

    // Main game loop
    while (!exitWindow) {
        // Check if window should close
        if (WindowShouldClose()) {
            exitWindow = true;
        }

        // Update
        float dt = GetFrameTime();
        
        // *** GLOBAL CLOCK TICK ***
        // Time updates here continuously, globally, and respects the night acceleration.
        Game::getInstance()->UpdateGameTime(dt); 
        
        manager.Update(dt);
        manager.HandleInput();

        // Check if we should exit the program
        if (manager.IsDone()) {
            exitWindow = true;
        }

        // Draw
        manager.Draw();
    }

    CloseWindow();
    return 0;
}