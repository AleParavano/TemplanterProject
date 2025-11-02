// #include "Demo.h"

// Demo::Demo() {
//     std::cout << "=== INITIALIZING GAME FACADE ===" << std::endl;
    
//     // Initialize player from game backend
//     player = &game.getPlayer();
    
//     std::cout << "Creating StoreScene..." << std::endl;
//     std::cout << "StoreScene created!" << std::endl;
//     std::cout << "Creating Player..." << std::endl;
//     std::cout << "Player created!" << std::endl;
// }

// Demo::~Demo() {
//     // Cleanup is handled automatically by member destructors
//     std::cout << "Game facade destroyed!" << std::endl;
// }

// void Demo::initializeWindow() {
//     std::cout << "Initializing window..." << std::endl;
//     InitWindow(width, height, "Plant Store Game");
//     SetExitKey(KEY_NULL);
//     SetTargetFPS(60);
//     std::cout << "Window initialized!" << std::endl;
// }

// void Demo::setupTestInventory() {
//     std::cout << "Setting up test inventory..." << std::endl;
    
//     // Add various test plants to player inventory (now 25 slots)
//     for (int i = 0; i < 3; i++) {
//         player->getInventory()->add(new Plant("Pumpkin", 2, 2));
//         player->getInventory()->add(new Plant("Carrot", 2, 2));
//         player->getInventory()->add(new Plant("Tomato", 2, 2));
//         player->getInventory()->add(new Plant("Lettuce", 2, 2));
//         player->getInventory()->add(new Plant("Potato", 2, 2));
//     }
    
//     std::cout << "Test inventory created!" << std::endl;
// }

// void Demo::displayControls() {
//     std::cout << "\n=== CONTROLS ===" << std::endl;
//     std::cout << "E - Open/Close Inventory" << std::endl;
//     std::cout << "Click 'Open/Closed' button - Toggle store (enables customer spawning)" << std::endl;
//     std::cout << "Click 'Manage Plants' - Open/Close inventory" << std::endl;
//     std::cout << "Click customer with selected plant - Serve customer" << std::endl;
//     std::cout << "Click customer with no selection - Dismiss customer" << std::endl;
//     std::cout << "ESC - Close inventory\n" << std::endl;
// }

// void Demo::handleInput() {
//     // E key to toggle inventory (works unless modal is blocking)
//     if (IsKeyPressed(KEY_E) && !store.getShowModal()) {
//         player->getInventoryUI()->toggle();
//     }
// }

// void Demo::update() {
//     // Update store (handles modal toggle and customer spawning)
//     store.update(player);
    
//     // Update player inventory UI
//     player->getInventoryUI()->update();
// }

// void Demo::render() {
//     BeginDrawing();
//     ClearBackground(RAYWHITE);
    
//     // Render game components
//     store.render();
//     player->getInventoryUI()->render();
    
//     // Display HUD information
//     int customerCount = store.getCustomerManager()->getCustomerCount();
//     DrawText(TextFormat("Customers: %d/5", customerCount), 10, 10, 15, DARKGRAY);
//     DrawText("E - Inventory | Select plant & click customer to serve", 
//              10, height - 25, 15, DARKGRAY);
    
//     EndDrawing();
// }

// void Demo::run() {
//     std::cout << "=== STARTING GAME ===" << std::endl;
    
//     // Initialize all subsystems through facade
//     initializeWindow();
//     setupTestInventory();
//     displayControls();
    
//     // Main game loop - clean and simple
//     while (!WindowShouldClose()) {
//         handleInput();
//         update();
//         render();
//     }
    
//     // Cleanup
//     CloseWindow();
//     std::cout << "Game ended!" << std::endl;
// }
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
    std::cout << "=== INITIALIZING GAME FACADE hey I'm the demom ===" << std::endl;
    
    std::cout << player->getMoney() << std::endl;
    // Add cheat money for testing
    player->addMoney(10000); 
    std::cout << player->getMoney() << std::endl;
}

Demo::~Demo() {
    // Cleanup Customer Flyweight textures 
    CustomerImageFactory::getInstance().cleanup(); 
    std::cout << "Game facade destroyed!" << std::endl;
}

void Demo::initializeWindow() {
    InitWindow(width, height, "TEMPLANTER - Plant Store Simulation");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));
    std::cout << "Window initialized!" << std::endl;
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
    std::cout << "=== STARTING GAME LOOP ===" << std::endl;
    
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
    std::cout << "DEBUG: Final money set to : " << player->getMoney() << std::endl;
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
    std::cout << "Game ended!" << std::endl;
}