#include "StoreScene.h"

void StoreScene::Init() {
    // Initialize store resources here
}

void StoreScene::Update(float dt) {
    // Update store logic here
}

void StoreScene::HandleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
    }
}

void StoreScene::Draw() {
    DrawRectangle(0, 0, 1400, 900, Fade(RAYWHITE, 0.8f));
    DrawText("WELCOME TO THE MEGA STORE", 380, 400, 40, DARKBLUE);
    DrawText("Press [Escape] to return", 500, 460, 20, GRAY);
}