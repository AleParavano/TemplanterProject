#include "SceneManager.h"

#include <iostream>

SceneManager::SceneManager() : currentScene(SCENE_OUTDOOR), nextScene(SCENE_OUTDOOR), shouldExit(false) {
    // Create all scenes
    scenes[SCENE_OUTDOOR] = new OutdoorScene();
    scenes[SCENE_GREENHOUSE] = new GreenHouseScene();
    scenes[SCENE_STORE] = new StoreScene();
    scenes[SCENE_WAREHOUSE] = new WarehouseScene();

    // Initialize the starting scene
    scenes[currentScene]->Init();
}

SceneManager::~SceneManager() {
    for (auto& pair : scenes) {
        delete pair.second;
    }
    scenes.clear();
}

void SceneManager::Update(float dt) {
    scenes[currentScene]->Update(dt);
}

void SceneManager::HandleInput() {
    
    // --- 1. IMMEDIATE/FORCED TRANSITION CHECK (Back Button) ---
    // If we detect the back button click, we swap the scene and STOP processing input
    
    if (currentScene != SCENE_OUTDOOR && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        Rectangle backBtnArea = {BACK_BUTTON_MARGIN, BACK_BUTTON_MARGIN, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT};
        
        if (CheckCollisionPointRec(mousePos, backBtnArea)) {
            // Transition to OUTDOOR scene
            currentScene = SCENE_OUTDOOR;
            nextScene = SCENE_OUTDOOR;
            scenes[currentScene]->Init();
            
            // Return immediately to skip all other input/transition logic
            return; 
        }
    }

    // SCENE INPUT (Only runs if the Back Button wasn't clicked) 
    scenes[currentScene]->HandleInput();
    
    // NATURAL TRANSITION CHECK (Internal scene logic) 
    nextScene = scenes[currentScene]->CheckExit();
    
    if (nextScene != currentScene) {
        currentScene = nextScene;
        scenes[currentScene]->Init(); 
    }
    
    // GLOBAL UI INPUT (Save/Load) ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        float menuX = SCREEN_WIDTH - MENU_WIDTH;
        Rectangle saveBtn = {menuX + 10, 225.0f, MENU_WIDTH - 20, 30};
        Rectangle loadBtn = {menuX + 10, 265.0f, MENU_WIDTH - 20, 30};

        if (CheckCollisionPointRec(mousePos, saveBtn)) {
            Game::getInstance()->saveGame(); 
        } else if (CheckCollisionPointRec(mousePos, loadBtn)) {
            Game::getInstance()->loadGame();
        }
    }

    // GLOBAL QUIT CHECK 
    if (IsKeyPressed(KEY_ESCAPE) && currentScene == SCENE_OUTDOOR) {
        shouldExit = true;
    }
}

void SceneManager::Draw() {
    BeginDrawing();
    
    // Clear background based on scene
    if (currentScene == SCENE_OUTDOOR) {
        ClearBackground({135, 206, 250, 255});
    } else if (currentScene == SCENE_GREENHOUSE) {
        ClearBackground({101, 67, 33, 255});
    } else {
        ClearBackground({200, 200, 200, 255});
    }
    
    //Drawing the scene
    scenes[currentScene]->Draw();
    
    // Call the dedicated global UI function 
    DrawGlobalMenu();
    
    // Drawing the actually Scene's Menu
    scenes[currentScene]->DrawMenu();

    //Draw the Back Button (top left)
    DrawBackButton(currentScene);

    EndDrawing();
}

bool SceneManager::IsDone() const {
    return shouldExit;
}

