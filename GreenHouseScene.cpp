#include "GreenHouseScene.h"
#include <math.h>
#include <stdlib.h>

GreenHouseScene::GreenHouseScene() : numPlants(0), numPaths(0) {}



void GreenHouseScene::Init() {

    nextScene = GetSceneType(); 

    InitPlants();
    InitPaths();
}

void GreenHouseScene::InitPlants() {
    Color plantColors[][3] = {
        {{40, 160, 40, 255}, {50, 180, 50, 255}, {60, 200, 60, 255}},
        {{255, 200, 60, 255}, {255, 220, 80, 255}, {240, 200, 50, 255}},
        {{200, 40, 40, 255}, {220, 50, 50, 255}, {180, 30, 30, 255}}
    };

    float gardenStartX = 30, gardenStartY = 30, gardenWidth = 600, gardenHeight = 250;
    int rowSpacing = 30, colSpacing = 30;
    int numRows = (int)(gardenHeight / rowSpacing);
    int numCols = (int)(gardenWidth / colSpacing);

    numPlants = 0;
    for (int row = 0; row < numRows && numPlants < MAX_PLANTS; row++) {
        for (int col = 0; col < numCols && numPlants < MAX_PLANTS; col++) {
            float offsetX = (rand() % 6) - 3;
            float offsetY = (rand() % 6) - 3;
            
            plants[numPlants].position = {
                gardenStartX + 8 + col * colSpacing + offsetX,
                gardenStartY + 8 + row * rowSpacing + offsetY
            };
            
            int colorType = rand() % 3;
            int colorShade = rand() % 3;
            plants[numPlants].color = plantColors[colorType][colorShade];
            plants[numPlants].type = rand() % 3;
            plants[numPlants].size = 2.5f + (rand() % 3);
            plants[numPlants].growthStage = 0.7f + (rand() % 30) / 100.0f;
            numPlants++;
        }
    }
}

void GreenHouseScene::InitPaths() {
    numPaths = 0;
    paths[numPaths++] = {{700, 0}, {700, 900}, 120};
    paths[numPaths++] = {{700, 800}, {1400, 800}, 300};
    paths[numPaths++] = {{0, 300}, {700, 300}, 80};
    paths[numPaths++] = {{0, 600}, {700, 600}, 80};
    paths[numPaths++] = {{700, 300}, {1400, 300}, 80};
}

void GreenHouseScene::Update(float dt) {
    // Greenhouse is static, no update logic needed for now
}

void GreenHouseScene::HandleInput() {
    // if (IsKeyPressed(KEY_ESCAPE)) {
    //     nextScene = SCENE_OUTDOOR; 
    // }
}

SceneType GreenHouseScene::CheckExit() {
    SceneType result = nextScene;
    nextScene = GetSceneType(); 
    return result; 
}

void GreenHouseScene::Draw() {
    DrawGreenhouse();
}

void GreenHouseScene::DrawGreenhouse() {
    // Just draw the UI text - background is already drawn by SceneManager
    DrawText("GREENHOUSE INTERIOR", 440, 40, 40, WHITE);
    DrawText("Press [Escape] to return", 500, 90, 20, LIGHTGRAY);
}

void GreenHouseScene::DrawGate(Vector2 position, bool isVertical) {
    Color postColor = {101, 67, 33, 255};
    Color gateColor = {139, 69, 19, 255};

    if (isVertical) {
        DrawRectangleV({position.x - 5, position.y - 12}, {10, 8}, postColor);
        DrawRectangleV({position.x - 5, position.y + 4}, {10, 8}, postColor);
        DrawRectangleV({position.x - 3, position.y - 4}, {6, 8}, gateColor);
        DrawRectangleLines(position.x - 3, position.y - 4, 6, 8, postColor);
    } else {
        DrawRectangleV({position.x - 12, position.y - 5}, {8, 10}, postColor);
        DrawRectangleV({position.x + 4, position.y - 5}, {8, 10}, postColor);
        DrawRectangleV({position.x - 4, position.y - 3}, {8, 6}, gateColor);
        DrawRectangleLines(position.x - 4, position.y - 3, 8, 6, postColor);
    }
}

float GreenHouseScene::Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int GreenHouseScene::ClampValue(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}