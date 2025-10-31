#ifndef GREENHOUSESCENE_H
#define GREENHOUSESCENE_H

#include "Scene.h"
#include "Types.h"
#include "Backend/Game.h"
#include "Backend/Player.h"
#include "Backend/Plant.h"
#include "Backend/PlantFactory.h" 
#include "Backend/Inventory.h" 
#include "PlantVisualStrategy.h"
#include "UI.h" 
#include <map>
#include <vector>
#include <iostream>

#define MAX_PLANTS 250
// Constants for menu layout
#define MENU_WIDTH 250
#define MENU_X_START 1400 - MENU_WIDTH
#define MENU_Y_START 320
#define ITEM_HEIGHT 45
#define BUTTON_SIZE 30
#define BUTTON_WIDTH 30
#define PADDING 10

// --- Shop Modal Constants ---
#define SHOP_WIDTH 700
#define SHOP_HEIGHT 700
#define SHOP_X ((SCREEN_WIDTH - SHOP_WIDTH) / 2)
#define SHOP_Y ((SCREEN_HEIGHT - SHOP_HEIGHT) / 2)
#define ITEM_ROW_HEIGHT 60

class GreenHouseScene : public Scene {
private:
    PlantVisual plants[MAX_PLANTS];
    Road paths[10];
    int numPlants;
    int numPaths;
    bool isShopOpen;

    SceneType nextScene; 
    
    
    void InitPlants();
    void InitPaths();
    void DrawPlantDetailed(PlantVisual p);
    void DrawSeedShop();
    void DrawGate(Vector2 position, bool isVertical);
    void DrawGreenhouse();
    float Distance(Vector2 a, Vector2 b);
    int ClampValue(int value, int min, int max);

public:
    GreenHouseScene();
    ~GreenHouseScene() = default;
    SceneType CheckExit() override;

    
    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    void DrawMenu() override;
    SceneType GetSceneType() const override { return SCENE_GREENHOUSE; }
};

#endif // GREENHOUSESCENE_H