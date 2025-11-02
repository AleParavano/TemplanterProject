#include "raylib.h"
#include "StoreScene.h"
#include "../Backend/Player.h"
#include "../Backend/Inventory.h"
#include "../Frontend/InventoryUI.h" // Add this includeb
#include "../Backend/Game.h"

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
    Game game;
    std::cout << "Player created!" << std::endl;

    Player &player = game.getPlayer();

    // Add various test plants to player inventory (now 25 slots)
    for (int i = 0; i < 3; i++)
    {
        player.getInventory()->add(new Plant("Pumpkin", 2, 2));
        player.getInventory()->add(new Plant("Carrot", 2, 2));
        player.getInventory()->add(new Plant("Tomato", 2, 2));
        player.getInventory()->add(new Plant("Lettuce", 2, 2));
        player.getInventory()->add(new Plant("Potato", 2, 2));
    }

    std::cout << "\n=== CONTROLS ===" << std::endl;
    std::cout << "E - Open/Close Inventory" << std::endl;
    std::cout << "Click 'Open/Closed' button - Toggle store (enables customer spawning)" << std::endl;
    std::cout << "Click 'Manage Plants' - Open/Close inventory" << std::endl;
    std::cout << "Click customer with selected plant - Serve customer" << std::endl;
    std::cout << "Click customer with no selection - Dismiss customer" << std::endl;
    std::cout << "ESC - Close inventory\n"
              << std::endl;

    while (!WindowShouldClose())
    {
        // Update store (handles modal toggle and customer spawning)
        store.update(&player);

        // E key to toggle inventory (works unless modal is blocking)
        if (IsKeyPressed(KEY_E) && !store.getShowModal())
        {
            player.getInventoryUI()->toggle();
        }

        // Update player inventory
        player.getInventoryUI()->update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        store.render();
        player.getInventoryUI()->render();

        // Display instructions
        int customerCount = store.getCustomerManager()->getCustomerCount();
        DrawText(TextFormat("Customers: %d/5", customerCount), 10, 10, 15, DARKGRAY);
        DrawText("E - Inventory | Select plant & click customer to serve", 10, height - 25, 15, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}