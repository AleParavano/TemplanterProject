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

    // Add some test plants to player inventory
    Plant *plant = new Plant("Pumpkin", 2, 2);
    bool result1 = player.getInventory()->add(plant);
    Plant *plant2 = new Plant("Carrot", 2, 2);
    bool result2 = player.getInventory()->add(plant2);
    Plant *plant3 = new Plant("Pumpkin", 2, 2);
    bool result3 = player.getInventory()->add(plant3);

    // Add various plants to storage
    for (int i = 0; i < 3; i++)
    {
        store.getStorage()->add(new Plant("Carrot", 2, 2));
        store.getStorage()->add(new Plant("Tomato", 2, 2));
        store.getStorage()->add(new Plant("Lettuce", 2, 2));
        store.getStorage()->add(new Plant("Potato", 2, 2));
    }

    std::cout << "\n=== CONTROLS ===" << std::endl;
    std::cout << "E - Open/Close Inventory" << std::endl;
    std::cout << "Click 'Open/Closed' button - Toggle store (enables customer spawning)" << std::endl;
    std::cout << "Click 'Manage Plants' - Open storage modal" << std::endl;
    std::cout << "Click customer with selected plant - Serve customer" << std::endl;
    std::cout << "Click customer with no selection - Dismiss customer" << std::endl;
    std::cout << "ESC - Close modals\n" << std::endl;

    while (!WindowShouldClose())
    {
        // Update store (handles modal toggle and customer spawning)
        store.update(&player);

        // E key only works when storage isn't open
        if (IsKeyPressed(KEY_E) && !store.getShowModal())
        {
            player.openInventory();
        }

        // CRITICAL: Update storage BEFORE player inventory
        if (store.getShowModal())
        {
            store.updateStorage(&player);
        }

        // Update player inventory with storage interaction
        player.updateInventory(store.getStorage(), store.getSelectedStorageSlot());

        BeginDrawing();
        ClearBackground(RAYWHITE);

        store.render();
        store.renderModal(width, height);
        player.renderInventory();

        // Display instructions
        int customerCount = store.getCustomerManager()->getCustomerCount();
        DrawText(TextFormat("Customers: %d/5", customerCount), 10, 10, 15, DARKGRAY);
        DrawText("E - Inventory | Select plant & click customer to serve", 10, height - 25, 15, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}