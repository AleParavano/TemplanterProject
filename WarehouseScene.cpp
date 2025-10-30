// ===== WarehouseScene.cpp =====
#include "WarehouseScene.h"

void WarehouseScene::Init() {
    // Initialize warehouse resources here
}

void WarehouseScene::Update(float dt) {
    // Update warehouse logic here
}

void WarehouseScene::HandleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        // Return to outdoor scene
    }
}

void WarehouseScene::Draw() {
    DrawRectangle(0, 0, 1400, 900, Fade(RAYWHITE, 0.8f));
    DrawText("WELCOME TO THE WAREHOUSE", 380, 400, 40, DARKGRAY);
    DrawText("Press [Escape] to return", 500, 460, 20, GRAY);
}