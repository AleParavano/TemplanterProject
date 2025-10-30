#include "raylib.h"
#include "Scene.h"
#include "OutdoorScene.h"
#include "GreenHouseScene.h"
#include "StoreScene.h"
#include "WarehouseScene.h"
#include <stdlib.h>
#include <time.h>
#include <map>
#include <cstdio>

// Scene manager class
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
        
        // Use different background colors based on scene
        if (currentScene == SCENE_OUTDOOR) {
            ClearBackground({135, 206, 250, 255}); // Sky blue for outdoor
        } else if (currentScene == SCENE_GREENHOUSE) {
            ClearBackground({101, 67, 33, 255}); // Brown soil for greenhouse
        } else {
            ClearBackground({200, 200, 200, 255}); // Light gray for other scenes
        }
        
        scenes[currentScene]->Draw();
        
        // Draw UI panel on the right
        DrawUIPanel();
        
        EndDrawing();
    }

    void DrawUIPanel() {
        int panelWidth = 200;
        int panelX = 1400 - panelWidth;
        int panelY = 0;
        
        // Draw semi-transparent background panel
        DrawRectangle(panelX, panelY, panelWidth, 900, Fade(BLACK, 0.6f));
        DrawRectangleLinesEx({(float)panelX, (float)panelY, (float)panelWidth, 900.0f}, 2, {100, 100, 100, 255});
        
        // Title
        DrawText("GAME INFO", panelX + 20, panelY + 20, 16, WHITE);
        
        // Time of day section
        DrawText("Time of Day", panelX + 20, panelY + 60, 12, LIGHTGRAY);
        
        // Get time percentage for display (0-100)
        float timePercent = 50.0f;
        OutdoorScene* outdoorScene = dynamic_cast<OutdoorScene*>(scenes[SCENE_OUTDOOR]);
        if (outdoorScene) {
            timePercent = outdoorScene->GetTimeOfDay() * 100.0f;
        }
        
        // Draw time bar
        DrawRectangle(panelX + 20, panelY + 80, 160, 20, Fade(DARKGRAY, 0.5f));
        DrawRectangle(panelX + 20, panelY + 80, (int)(160 * timePercent / 100.0f), 20, {255, 200, 100, 255});
        DrawRectangleLinesEx({(float)(panelX + 20), (float)(panelY + 80), 160.0f, 20.0f}, 1, LIGHTGRAY);
        
        // Time text
        char timeText[32];
        snprintf(timeText, sizeof(timeText), "%.1f%%", timePercent);
        DrawText(timeText, panelX + 70, panelY + 85, 10, WHITE);
        
        // Save button
        int buttonY = panelY + 150;
        int buttonWidth = 160;
        int buttonHeight = 30;
        bool mouseOverSave = CheckCollisionPointRec(GetMousePosition(), {(float)(panelX + 20), (float)buttonY, (float)buttonWidth, (float)buttonHeight});
        
        Color buttonColor = mouseOverSave ? RED : MAROON;
        DrawRectangle(panelX + 20, buttonY, buttonWidth, buttonHeight, buttonColor);
        DrawRectangleLinesEx({(float)(panelX + 20), (float)buttonY, (float)buttonWidth, (float)buttonHeight}, 2, WHITE);
        
        DrawText("SAVE GAME", panelX + 35, buttonY + 7, 14, WHITE);
        
        // Handle save button click
        if (mouseOverSave && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Save functionality would go here
        }
        
        // Additional info
        DrawText("Status: Running", panelX + 20, panelY + 250, 10, LIME);
        DrawText("FPS: ", panelX + 20, panelY + 280, 10, LIGHTGRAY);
        char fpsText[16];
        snprintf(fpsText, sizeof(fpsText), "%d", GetFPS());
        DrawText(fpsText, panelX + 60, panelY + 280, 10, WHITE);
    }

    bool IsDone() const {
        return shouldExit;
    }
};

int main(void) {
    const int screenWidth = 1400;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "TEMPLANTER - Top-Down Simulation");
    
    SetExitKey(KEY_NULL); // Handle window closing ourselves
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

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