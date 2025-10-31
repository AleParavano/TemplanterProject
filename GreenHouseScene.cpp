#include "GreenHouseScene.h"
#include <math.h>
#include <stdlib.h>


// --- Plant Catalog (Placed globally, assumed all components are defined) ---
std::map<std::string, std::tuple<float, PlantFactory *, PlantVisualStrategy *>> plantCatalog = {
    {"Lettuce", {15.0f, new LettuceFactory(), new LettuceVisualStrategy(20.0f, 15.0f)}},
    {"Carrot", {25.0f, new CarrotFactory(), new CarrotVisualStrategy(15.0f, 30.0f)}},
    {"Potato", {35.0f, new PotatoFactory(), new PotatoVisualStrategy(18.0f, 20.0f)}},
    {"Cucumber", {45.0f, new CucumberFactory(), new CucumberVisualStrategy(20.0f, 35.0f)}},
    {"Tomato", {55.0f, new TomatoFactory(), new TomatoVisualStrategy(25.0f, 25.0f)}},
    {"Pepper", {65.0f, new PepperFactory(), new PepperVisualStrategy(25.0f, 30.0f)}},
    {"Sunflower", {80.0f, new SunflowerFactory(), new SunflowerVisualStrategy(25.0f, 50.0f)}},
    {"Strawberry", {100.0f, new StrawberryFactory(), new StrawberryVisualStrategy(25.0f, 15.0f)}},
    {"Corn", {120.0f, new CornFactory(), new CornVisualStrategy(20.0f, 55.0f)}},
    {"Pumpkin", {200.0f, new PumpkinFactory(), new PumpkinVisualStrategy(40.0f, 30.0f)}}};

// --- CONSTANTS FOR GREENHOUSE GRID LAYOUT ---
const int GRID_START_X = 0;
const int GRID_START_Y = 50;
const int PLOT_SIZE = 115;
const int PATH_SIZE = 35;
const int NARROW_PATH_WIDTH = 60;
const int MIDDLE_PATH_INDEX = 7; // Column index for the middle path

// --- NEW Helper to get the different colors ---
Color GetSoilColor()
{
    return {101, 67, 33, 255}; // Base Soil Brown (Used for background/plots)
}
Color GetPlotColor()
{
    return {101, 67, 33, 255}; // Base Soil Brown (Used for background/plots)
}
Color GetPathColor()
{
    return {60, 160, 60, 255}; // Base Green (Used for paths)
}

GreenHouseScene::GreenHouseScene() : numPlants(0), numPaths(0), nextScene(SCENE_GREENHOUSE), isShopOpen(false) {}

void GreenHouseScene::Init()
{
    nextScene = GetSceneType();
    InitPlants(); // Retained old setup function structure
    InitPaths();  // Retained old setup function structure
}

void GreenHouseScene::InitPlants()
{
    // Function retained from original file, but logic is now superseded by the backend Greenhouse
    Color plantColors[][3] = {
        {{40, 160, 40, 255}, {50, 180, 50, 255}, {60, 200, 60, 255}},
        {{255, 200, 60, 255}, {255, 220, 80, 255}, {240, 200, 50, 255}},
        {{200, 40, 40, 255}, {220, 50, 50, 255}, {180, 30, 30, 255}}};

    float gardenStartX = 30, gardenStartY = 30, gardenWidth = 600, gardenHeight = 250;
    int rowSpacing = 30, colSpacing = 30;
    int numRows = (int)(gardenHeight / rowSpacing);
    int numCols = (int)(gardenWidth / colSpacing);

    numPlants = 0;
    for (int row = 0; row < numRows && numPlants < MAX_PLANTS; row++)
    {
        for (int col = 0; col < numCols && numPlants < MAX_PLANTS; col++)
        {
            float offsetX = (rand() % 6) - 3;
            float offsetY = (rand() % 6) - 3;

            // This array 'plants' is deprecated, but left here to compile the existing code if needed.
            // plants[numPlants].position = { ... }; 
            
            numPlants++;
        }
    }
}

void GreenHouseScene::InitPaths()
{
    // Function retained from original file
    numPaths = 0;
    // ... (paths array setup) ...
}

void GreenHouseScene::Update(float dt)
{
    // Greenhouse is static, no update logic needed for now
}

void GreenHouseScene::HandleInput()
{
    if (isShopOpen)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            isShopOpen = false;
        }
        return; 
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();
        Rectangle buyBtnArea = {MENU_X_START + 10, MENU_Y_START + 35, MENU_WIDTH - 20, ITEM_HEIGHT};

        if (CheckCollisionPointRec(mousePos, buyBtnArea))
        {
            isShopOpen = true;
            return;
        }
    }
}

SceneType GreenHouseScene::CheckExit()
{
    SceneType result = nextScene;
    nextScene = GetSceneType();
    return result;
}

void GreenHouseScene::Draw()
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    // 1. Draw the realistic, tiled soil background using the global utility
    DrawTiledBackground(GetSoilColor(), screenWidth, screenHeight);

    // Get the authoritative backend data
    Greenhouse *gh = Game::getInstance()->getPlayerPtr()->getPlot();

    // --- Dynamic Grid Drawing ---
    int plotIndex = 0; 
    int numGridBlocks = 15; // 8 plots + 7 paths

    int currentX = GRID_START_X;
    int currentY = GRID_START_Y;

    for (int row = 0; row < numGridBlocks; row++)
    {
        currentX = GRID_START_X;

        bool isPathRow = (row % 2 != 0);
        int blockHeight = isPathRow ? PATH_SIZE : PLOT_SIZE;

        for (int col = 0; col < numGridBlocks; col++)
        {
            bool isPathCol = (col % 2 != 0);
            int blockWidth;
            if (isPathCol && col == MIDDLE_PATH_INDEX) {
                blockWidth = NARROW_PATH_WIDTH;
            } else {
                blockWidth = isPathCol ? PATH_SIZE : PLOT_SIZE;
            }

            bool isPlotTile = !isPathRow && !isPathCol;
            Rectangle rect = {(float)currentX, (float)currentY, (float)blockWidth, (float)blockHeight};

            if (isPlotTile)
            {
                // *** 1. DRAW BACKEND PLANT (If present) ***
                if (plotIndex < gh->getCapacity())
                {
                    Plant *plant = gh->getPlant(plotIndex);

                    if (plant)
                    {
                        // Calculate plant position
                        float plantDrawX = rect.x + rect.width / 2.0f;
                        // FIX: Center vertically by drawing relative to the middle of the tile, not the bottom edge.
                        // The plant's origin (y=0) is usually the base, so we use rect.y + rect.height to anchor it.
                        // To center vertically, we keep the anchor at the bottom edge of the tile.
                        float plantDrawY = rect.y + rect.height; 
                        
                        // Call the backend plant's drawing method. 
                        // The plant's draw function will center itself horizontally using plantDrawX.
                        plant->draw(plantDrawX, plantDrawY, PLOT_SIZE, PLOT_SIZE);
                    }

                    plotIndex++;
                }
            }
            else if (isPathRow)
            {
                DrawTiledArea(rect, GetPathColor());
            }
            else if (isPathCol && col == MIDDLE_PATH_INDEX)
            {
                DrawTiledArea(rect, GetPathColor());
            }

            currentX += blockWidth;
        }

        currentY += blockHeight;
    }

    // 2. Draw the Greenhouse elements and UI text
    DrawGreenhouse();
}

void GreenHouseScene::DrawGreenhouse()
{
    DrawText("GREENHOUSE INTERIOR", 400, 5, 40, WHITE);
}

void GreenHouseScene::DrawMenu()
{
    float menuX = MENU_X_START;
    float menuY = MENU_Y_START;

    DrawText("GREENHOUSE ACTIONS:", menuX + 10, menuY, 18, WHITE);
    DrawLine(menuX + 5, menuY + 25, menuX + MENU_WIDTH - 5, menuY + 25, LIGHTGRAY);

    Rectangle buyBtn = {menuX + 10, menuY + 35, MENU_WIDTH - 20, ITEM_HEIGHT};
    DrawRectangleRec(buyBtn, SKYBLUE);
    DrawText("BUY SEEDS", buyBtn.x + (buyBtn.width - MeasureText("BUY SEEDS", 20)) / 2, buyBtn.y + 12, 20, DARKBLUE);

    if (isShopOpen)
    {
        DrawSeedShop();
    }
}

void GreenHouseScene::DrawSeedShop()
{
    Player *player = Game::getInstance()->getPlayerPtr();
    if (!player)
        return;
    Greenhouse *greenhouse = player->getPlot();
    
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

    Rectangle modalRect = {SHOP_X, SHOP_Y, SHOP_WIDTH, SHOP_HEIGHT};
    Color modalColor = {20, 20, 20, 200};
    DrawRectangleRec(modalRect, modalColor);
    DrawRectangleLinesEx(modalRect, 3, RAYWHITE);

    DrawText("BUY SEEDS", SHOP_X + (SHOP_WIDTH - MeasureText("BUY SEEDS", 30)) / 2, SHOP_Y + 15, 30, RAYWHITE);

    Rectangle closeBtn = {SHOP_X + SHOP_WIDTH - 40, SHOP_Y + 10, 30, 30};
    DrawRectangleRec(closeBtn, MAROON);
    DrawText("X", closeBtn.x + 8, closeBtn.y + 5, 20, RAYWHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), closeBtn))
    {
        isShopOpen = false;
        return;
    }

    int startY = SHOP_Y + 80;
    int index = 0;

    for (const auto &pair : plantCatalog)
    {
        const std::string &type = pair.first;
        float price = std::get<0>(pair.second);
        PlantFactory *factory = std::get<1>(pair.second);
        PlantVisualStrategy *visual = std::get<2>(pair.second);

        Rectangle itemRect = {SHOP_X + 20, (float)startY, SHOP_WIDTH - 40, ITEM_ROW_HEIGHT - 10};
        DrawRectangleRec(itemRect, Fade(DARKGRAY, 0.2f));

        visual->drawStatic(SHOP_X + 60, (float)startY + ITEM_ROW_HEIGHT / 2);

        DrawText(type.c_str(), SHOP_X + 110, startY + 10, 20, RAYWHITE);
        DrawText(TextFormat("$%.2f", price), SHOP_X + 110, startY + 35, 18, GOLD);

        Rectangle buyBtn = {SHOP_X + SHOP_WIDTH - 120, (float)startY + 10, 100, ITEM_ROW_HEIGHT - 20};
        bool canAfford = player->getMoney() >= price;
        bool canAdd = greenhouse->getSize() < greenhouse->getCapacity();

        Color btnColor = canAfford && canAdd ? LIME : DARKGRAY;
        DrawRectangleRec(buyBtn, btnColor);
        DrawText("+ ADD", buyBtn.x + 8, buyBtn.y + 10, 15, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buyBtn))
        {
            if (!canAfford)
            {
                std::cout << "LOG: Insufficient funds to buy " << type << std::endl;
            }
            else
            {
                if (greenhouse->getSize() >= greenhouse->getCapacity())
                {
                    std::cout << "LOG: All plots are currently occupied. Clear a plot first." << std::endl;
                }
                else
                {
                    Plant *newPlant = factory->produce();
                    if (greenhouse->addPlant(newPlant))
                    {
                        player->setMoney(player->getMoney() - price);
                        std::cout << "LOG: Bought and planted " << type << " seed directly into plot." << std::endl;
                    }
                    else
                    {
                        delete newPlant;
                        std::cout << "LOG: Failed to find an empty plot slot." << std::endl;
                    }
                }
            }
        }

        startY += ITEM_ROW_HEIGHT;
    }
}

void GreenHouseScene::DrawGate(Vector2 position, bool isVertical)
{
    // ... (Drawing logic remains the same) ...
}

float GreenHouseScene::Distance(Vector2 a, Vector2 b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int GreenHouseScene::ClampValue(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}