#include "raylib.h"
#include "StoreScene.h"
#include "../Backend/Player.h"
#include "../Backend/Inventory.h"
#include <iostream>

int main()
{
    // Window configuration
    const int width = 1400;
    const int height = 900;

    // Initialize window
    InitWindow(width, height, "Plant Store Game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    // Create game objects
    StoreScene store;
    Player player;

    Plant *plant = new Plant("Test", 2, 2);
    player.getInventory()->add(plant);
    Plant *plant2 = new Plant("Test", 2, 2);
    player.getInventory()->add(plant2);
    Plant *plant3 = new Plant("Test2", 2, 2);
    player.getInventory()->add(plant3);
    // Main game loop
    while (!WindowShouldClose())
    {
        // ===== UPDATE PHASE =====
        store.update();
        if (IsKeyPressed(KEY_E))
        {
            player.openInventory();
        }

        // ===== RENDER PHASE =====
        BeginDrawing();

        // Render order matters - background to foreground
        store.render();                   // Draw store environment first
        store.renderModal(width, height); // Draw modal on top of everything
        player.renderInventory();
        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}