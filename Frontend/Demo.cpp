#include "Demo.h"
#include "OutdoorScene.h" 
#include "../Backend/PlantFactory.h"
#include "CustomerFlyweight.h"
#include "InventoryUI.h"
#include <stdlib.h>
#include <time.h>


Demo::Demo() 
    : player(Game::getInstance()->getPlayerPtr()), manager() 
{
    
    // Add cheat money for testing
    player->addMoney(10000); 
}

Demo::~Demo() {
    // Cleanup Customer Flyweight textures 
    CustomerImageFactory::getInstance().cleanup(); 
}

void Demo::initializeWindow() {
    InitWindow(width, height, "TEMPLANTER - Plant Store Simulation");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));
}

void Demo::setupTestInventory() {
    
}

void Demo::displayControls() {
    std::cout << "\n=== CONTROLS ===" << std::endl;
    std::cout << "ESC - Exit from non-Outdoor scenes" << std::endl;
    std::cout << "Mouse Click - Enter Buildings / Interact" << std::endl;
    std::cout << "Global Save/Load buttons available on the side menu." << std::endl;
    std::cout << "---" << std::endl;
}


void Demo::run() {    
    // 1. Setup
    initializeWindow();
    
    // --- FIX: Use friend access and dynamic_cast for derived scene setup ---
    Scene* storeSceneBase = manager.scenes[SCENE_STORE]; 
    
    if (storeSceneBase) {
        StoreScene* storeScene = dynamic_cast<StoreScene*>(storeSceneBase);

        if (storeScene) {
            storeScene->SetPlayer(player); // Assign player to StoreScene
            storeScene->Init(); // Initialize store
        } else {
            std::cerr << "ERROR: Failed to cast StoreScene during initialization!" << std::endl;
        }
    }
    // ------------------------------------------------------------------------

    displayControls();
    player->setMoney(10000.0f);
    player->getInventoryUI()->toggle();
    
    bool exitWindow = false;

    // 2. Main game loop
    while (!exitWindow) {
        if (WindowShouldClose()) {
            exitWindow = true;
        }

        float dt = GetFrameTime();
        
        // Time Update: Managed by Player
        Game::getInstance()->getPlayer().UpdateGameTime(dt); 
        
        // Scene Management
        manager.Update(dt);
        manager.HandleInput();

        if (manager.IsDone()) {
            exitWindow = true;
        }
        manager.Draw();
    }
    
    // 3. Cleanup
    CloseWindow();
}