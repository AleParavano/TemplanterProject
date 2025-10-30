#include "raylib.h"
#include "StoreScene.h"
#include "../Backend/Player.h"
#include "../Backend/Inventory.h"

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

    // Main game loop
    while (!WindowShouldClose())
    {
        // ===== UPDATE PHASE =====
        store.update();
        
        // ===== RENDER PHASE =====
        BeginDrawing();
        
        // Render order matters - background to foreground
        store.render();          // Draw store environment first
        store.renderModal(width, height);  // Draw modal on top of everything
        
        if (IsKeyPressed(KEY_E)){
            player.openInventory();
        }

        player.renderInventory();
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    
    return 0;
}