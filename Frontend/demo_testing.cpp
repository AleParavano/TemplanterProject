#include "raylib.h"
#include "StoreScene.h"
#include "../Backend/Player.h"
#include "../Backend/Inventory.h"
#include <iostream>

int main()
{
    std::cout << "=== STARTING GAME ===" << std::endl;

    const int width = 1400;
    const int height = 900;

    std::cout << "Initializing window..." << std::endl;
    InitWindow(width, height, "Plant Store Game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    std::cout << "Window initialized!" << std::endl;

    std::cout << "Creating StoreScene..." << std::endl;
    StoreScene store;
    std::cout << "StoreScene created!" << std::endl;

    std::cout << "Creating Player..." << std::endl;
    Player player;
    std::cout << "Player created!" << std::endl;

    Plant *plant = new Plant("Test", 2, 2);
    bool result1 = player.getInventory()->add(plant);
    Plant *plant2 = new Plant("Test", 2, 2);
    bool result2 = player.getInventory()->add(plant2);
    Plant *plant3 = new Plant("Test2", 2, 2);
    bool result3 = player.getInventory()->add(plant3);

    Plant *storePlant = new Plant("StorePlant", 2, 2);
    Plant *storePlant2 = new Plant("StorePlant", 2, 2);
    Plant *storePlant3 = new Plant("StorePlant2", 2, 2);

    
    store.getStorage()->add(storePlant);
    store.getStorage()->add(storePlant2);
    store.getStorage()->add(storePlant3);
    Plant *storeToPlayerplant = new Plant("Test2", 2, 2);
    bool result4 = store.getStorage()->add(storeToPlayerplant);

    while (!WindowShouldClose())
    {
        // Update store (handles modal toggle)
        store.update();

        // Toggle player inventory
        if (IsKeyPressed(KEY_E))
        {
            player.openInventory();
        }

        // CRITICAL: Update storage BEFORE player inventory
        // This allows storage to handle its own slot selection
        if (store.getShowModal())
        {
            store.updateStorage(&player);
        }

        // Update player inventory with storage interaction
        // Pass storage info so player can handle cross-inventory swaps
        player.updateInventory(store.getStorage(), store.getSelectedStorageSlot());

        BeginDrawing();
        ClearBackground(RAYWHITE);

        store.render();
        store.renderModal(width, height);
        player.renderInventory();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}