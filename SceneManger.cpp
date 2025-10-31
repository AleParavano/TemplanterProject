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
            // Step A: FORCE THE TRANSITION
            currentScene = SCENE_OUTDOOR;
            scenes[currentScene]->Init(); 
            
            std::cout << "DEBUG: Back button clicked. Transitioning." << std::endl;
            
            // Step B: CRITICAL - Return immediately to skip all other input/transition logic
            return; 
        }
    }

    // --- 2. SCENE INPUT (Only runs if the Back Button wasn't clicked) ---
    scenes[currentScene]->HandleInput();
    
    // --- 3. NATURAL TRANSITION CHECK (Internal scene logic) ---
    nextScene = scenes[currentScene]->CheckExit();
    
    if (nextScene != currentScene) {
        currentScene = nextScene;
        scenes[currentScene]->Init(); 
    }
    
    // --- 4. GLOBAL UI INPUT (Save/Load) ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        float menuX = SCREEN_WIDTH - MENU_WIDTH;
        Rectangle saveBtn = {menuX + 10, 200.0f, MENU_WIDTH - 20, 30};
        Rectangle loadBtn = {menuX + 10, 240.0f, MENU_WIDTH - 20, 30};

        if (CheckCollisionPointRec(mousePos, saveBtn)) {
            Game::getInstance()->saveGame(); 
        } else if (CheckCollisionPointRec(mousePos, loadBtn)) {
            Game::getInstance()->loadGame();
        }
    }

    // --- 5. GLOBAL QUIT CHECK ---
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
    
    scenes[currentScene]->Draw();
    
    // Call the dedicated global UI function 
    DrawGlobalMenu();

    //Draw the Back Button (top left)

    DrawBackButton(currentScene);

    EndDrawing();
}

bool SceneManager::IsDone() const {
    return shouldExit;
}