#include "GreenHouseScene.h"
#include <math.h>
#include <stdlib.h>

std::map<std::string, std::tuple<float, PlantFactory *, PlantVisualStrategy *>> plantCatalog = {
    // { Plant Name, { Price, Factory Instance, Visual Strategy Instance (W, H) } }

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

// --- CONSTANTS FOR GREENHOUSE GRID LAYOUT (In GreenHouseScene.cpp) ---
const int GRID_START_X = 0;
const int GRID_START_Y = 50;
const int PLOT_SIZE = 115;
const int PATH_SIZE = 35;
const int NARROW_PATH_WIDTH = 60 ;
const int MIDDLE_PATH_INDEX = 7;

GreenHouseScene::GreenHouseScene() : numPlants(0), numPaths(0), nextScene(SCENE_GREENHOUSE), isShopOpen(false) {}

void GreenHouseScene::Init()
{

    nextScene = GetSceneType();

    InitPlants();
    InitPaths();
}

void GreenHouseScene::InitPlants()
{
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

            plants[numPlants].position = {
                gardenStartX + 8 + col * colSpacing + offsetX,
                gardenStartY + 8 + row * rowSpacing + offsetY};

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

void GreenHouseScene::InitPaths()
{
    numPaths = 0;
    paths[numPaths++] = {{700, 0}, {700, 900}, 120};
    paths[numPaths++] = {{700, 800}, {1400, 800}, 300};
    paths[numPaths++] = {{0, 300}, {700, 300}, 80};
    paths[numPaths++] = {{0, 600}, {700, 600}, 80};
    paths[numPaths++] = {{700, 300}, {1400, 300}, 80};
}

void GreenHouseScene::Update(float dt)
{
    // Greenhouse is static, no update logic needed for now
}

void GreenHouseScene::HandleInput()
{
    // 1. If the shop is open, only check for ESCAPE to close it.
    if (isShopOpen)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            isShopOpen = false;
        }
        // Note: The close button click check is handled in DrawSeedShop.
        return; // Stop processing all other input in this scene.
    }

    // 2. Shop is CLOSED: Check for the "BUY SEEDS" button click.
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        // Define the EXACT area for the 'BUY SEEDS' button:
        // Position: 10 pixels from menuX, 35 pixels below menuY_START
        Rectangle buyBtnArea = {
            MENU_X_START + 10,
            MENU_Y_START + 35,
            MENU_WIDTH - 20,
            ITEM_HEIGHT // The full height of the button background
        };

        if (CheckCollisionPointRec(mousePos, buyBtnArea))
        {
            isShopOpen = true; // *** FIX: Open the shop ***
            return;            // Stop processing other input for this frame.
        }

        // 3. (Optional) Any other standard scene click logic (e.g., planting plots)
        // would go here if the click wasn't on the buy button.
    }

    // 4. Base scene logic (usually empty for Greenhouse)
    // No explicit call to scenes[currentScene]->HandleInput() is needed here,
    // as this file IS the current scene's HandleInput
}

SceneType GreenHouseScene::CheckExit()
{
    SceneType result = nextScene;
    nextScene = GetSceneType();
    return result;
}
// NEW Helper to get the different colors ---
Color GetSoilColor()
{
    // Base brown color for soil
    Color baseSoil = {101, 67, 33, 255};
    return baseSoil;
}
Color GetPlotColor() {
    return {101, 67, 33, 255}; // Base Soil Brown
}

Color GetPathColor() {
    return {34, 139, 34, 255}; 
}

void GreenHouseScene::Draw()
{
    const int screenWidth = 1400;
    const int screenHeight = 900;

    // Draw the realistic, tiled soil background using the global utility
    DrawTiledBackground(GetSoilColor(), screenWidth, screenHeight);
    
    // --- Dynamic Grid Drawing ---

    int plotIndex = 0; 
    int numPlotRows = 8; // NEW: 8 plot rows
    int numPlotCols = 77; // NEW: 8 plot columns
    int numGridBlocks = numPlotRows + (numPlotRows - 1); // 8 plots + 7 paths = 15 blocks
    

    // Current screen position offset from the start
    int currentX = GRID_START_X;
    int currentY = GRID_START_Y;

    for (int row = 0; row < numGridBlocks; row++) {
        currentX = GRID_START_X; 
        
        // Determine if the current row is a Path row (odd index 1, 3, 5)
        bool isPathRow = (row % 2 != 0);
        int blockHeight = isPathRow ? PATH_SIZE : PLOT_SIZE;
        
        // CRITICAL CHECK: Determine if the current row is a horizontal path that should be colored.
        bool shouldColorRow = isPathRow;

        for (int col = 0; col < numGridBlocks; col++) {
            
            // Determine if the current column is a Path column (odd index 1, 3, 5)
            bool isPathCol = (col % 2 != 0);

            // 1. Calculate blockWidth dynamically based on column type
            int blockWidth;
            if (isPathCol && col == MIDDLE_PATH_INDEX) {
                // Central vertical path is narrow
                blockWidth = NARROW_PATH_WIDTH;
            } else {
                // All other path columns use PATH_SIZE, plot columns use PLOT_SIZE
                blockWidth = isPathCol ? PATH_SIZE : PLOT_SIZE;
            }
            
            // Check if this is a PLOT TILE (Both row and column must be even)
            bool isPlotTile = !isPathRow && !isPathCol; 
            
            Rectangle rect = {(float)currentX, (float)currentY, (float)blockWidth, (float)blockHeight};
            
            if (isPlotTile) {
                plotIndex++;
                
            }else if (isPathRow) {
                // All horizontal paths are colored green.
                DrawTiledArea(rect, GetPathColor());
                
            } else if (isPathCol && col == MIDDLE_PATH_INDEX) {
                // Only color the single middle vertical path (index 7).
                DrawTiledArea(rect, GetPathColor());
            }

            // Move X position to the start of the next block
            currentX += blockWidth;
        }

        // Move Y position to the start of the next row
        currentY += blockHeight;
    }

    // Draw the Greenhouse elements
    DrawGreenhouse();
}

void GreenHouseScene::DrawGreenhouse()
{
    // Just draw the UI text - background is already drawn by SceneManager
    DrawText("GREENHOUSE INTERIOR", 400, 5, 40, WHITE);
}

void GreenHouseScene::DrawMenu()
{

    // Get required constants/positions from global defines
    float menuX = MENU_X_START;
    float menuY = MENU_Y_START;

    DrawText("GREENHOUSE ACTIONS:", menuX + 10, menuY, 18, WHITE);
    DrawLine(menuX + 5, menuY + 25, menuX + MENU_WIDTH - 5, menuY + 25, LIGHTGRAY);

    // Button: BUY SEEDS
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

    // Draw a dark transparent background over the whole scene
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));

    // Modal Window (Translucent) ---
    Rectangle modalRect = {SHOP_X, SHOP_Y, SHOP_WIDTH, SHOP_HEIGHT};
    Color modalColor = {20, 20, 20, 200}; // Dark, translucent background for the modal
    DrawRectangleRec(modalRect, modalColor);
    DrawRectangleLinesEx(modalRect, 3, RAYWHITE);

    // Header
    DrawText("BUY SEEDS", SHOP_X + (SHOP_WIDTH - MeasureText("BUY SEEDS", 30)) / 2, SHOP_Y + 15, 30, RAYWHITE);

    // Close Button
    Rectangle closeBtn = {SHOP_X + SHOP_WIDTH - 40, SHOP_Y + 10, 30, 30};
    DrawRectangleRec(closeBtn, MAROON);
    DrawText("X", closeBtn.x + 8, closeBtn.y + 5, 20, RAYWHITE);

    // Check Close Button Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), closeBtn))
    {
        isShopOpen = false;
        return; // Exit early after closing
    }

    // --- 3. Seed Items ---
    int startY = SHOP_Y + 60;
    int index = 0;

    for (const auto &pair : plantCatalog)
    {
        const std::string &type = pair.first;
        float price = std::get<0>(pair.second);
        PlantFactory *factory = std::get<1>(pair.second);
        PlantVisualStrategy *visual = std::get<2>(pair.second);

        Rectangle itemRect = {SHOP_X + 10, (float)startY, SHOP_WIDTH - 20, ITEM_ROW_HEIGHT - 5};

        // Draw Item Background
        DrawRectangleRec(itemRect, Fade(DARKGRAY, 0.2f));

        // Static Visual Icon
        visual->drawStatic(SHOP_X + 40, (float)startY + ITEM_ROW_HEIGHT / 2);

        //
        DrawText(type.c_str(), SHOP_X + 80, startY + 10, 20, RAYWHITE);
        DrawText(TextFormat("$%.2f", price), SHOP_X + 80, startY + 30, 15, GOLD);

        //
        Rectangle buyBtn = {SHOP_X + SHOP_WIDTH - 80, (float)startY + 10, 60, ITEM_ROW_HEIGHT - 20};
        bool canAfford = player->getMoney() >= price;
        bool canAdd = !player->getInventory()->isFull();

        Color btnColor = canAfford && canAdd ? LIME : DARKGRAY;
        DrawRectangleRec(buyBtn, btnColor);
        DrawText("+ ADD", buyBtn.x + 8, buyBtn.y + 10, 15, BLACK);

        // Check for click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), buyBtn))
        {

            // Get backend objects
            Player *player = Game::getInstance()->getPlayerPtr();
            Greenhouse *greenhouse = player->getPlot(); // Assuming player->getPlot() is defined

            // --- NEW LOGIC FLOW ---
            if (!canAfford)
            {
                std::cout << "LOG: Insufficient funds to buy " << type << std::endl;
            }
            else
            {
                // Step 1: Check for an available slot BEFORE creating the plant.
                if (greenhouse->getSize() >= greenhouse->getCapacity())
                {
                    std::cout << "LOG: All plots are currently occupied. Clear a plot first." << std::endl;
                    // No need to check for ripe/dead here; the player must manually clear the plot.
                }
                else
                {
                    // Step 2: Create the Plant (Seed)
                    Plant *newPlant = factory->produce();

                    // Step 3: Add the plant to the FIRST available slot (Greenhouse::addPlant(Plant*) does this)
                    if (greenhouse->addPlant(newPlant))
                    {
                        // Step 4: Deduct Money
                        player->setMoney(player->getMoney() - price);
                        std::cout << "LOG: Bought and planted " << type << " seed directly into plot." << std::endl;
                    }
                    else
                    {
                        // Should not happen if size < capacity, but good for safety
                        delete newPlant;
                        std::cout << "LOG: Failed to find an empty plot slot." << std::endl;
                    }
                }
            }
        }

        startY += ITEM_ROW_HEIGHT;
        index++;
    }
}

void GreenHouseScene::DrawGate(Vector2 position, bool isVertical)
{
    Color postColor = {101, 67, 33, 255};
    Color gateColor = {139, 69, 19, 255};

    if (isVertical)
    {
        DrawRectangleV({position.x - 5, position.y - 12}, {10, 8}, postColor);
        DrawRectangleV({position.x - 5, position.y + 4}, {10, 8}, postColor);
        DrawRectangleV({position.x - 3, position.y - 4}, {6, 8}, gateColor);
        DrawRectangleLines(position.x - 3, position.y - 4, 6, 8, postColor);
    }
    else
    {
        DrawRectangleV({position.x - 12, position.y - 5}, {8, 10}, postColor);
        DrawRectangleV({position.x + 4, position.y - 5}, {8, 10}, postColor);
        DrawRectangleV({position.x - 4, position.y - 3}, {8, 6}, gateColor);
        DrawRectangleLines(position.x - 4, position.y - 3, 8, 6, postColor);
    }
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