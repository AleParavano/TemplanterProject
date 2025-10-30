#include "raylib.h"
#include "StoreScene.h"

int main()
{
    // Window configuration
    const int width = 800;
    const int height = 500;

    // Initialize window
    InitWindow(width, height, "Plant Store Game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    // Create game objects
    StoreScene store;

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
        
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    
    return 0;
}