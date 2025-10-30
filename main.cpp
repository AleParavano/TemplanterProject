#include "raylib.h"
#include "Scene.h"
#include "OutdoorScene.h"
#include "GreenHouseScene.h"
#include "StoreScene.h"
#include "WarehouseScene.h"
#include <stdlib.h>
#include <time.h>
#include <map>

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
        EndDrawing();
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