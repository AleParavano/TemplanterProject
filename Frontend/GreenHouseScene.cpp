#include "GreenHouseScene.h"
#include <math.h>
#include <stdlib.h>

// --- INSPECTOR BAR CONSTANTS (NEW HORIZONTAL LAYOUT) ---

const float INSPECTOR_BAR_HEIGHT = 150.0f;                               // Height of the new bar
const float GRID_BOTTOM_MARGIN = 20.0f;                                  // Space between grid and bar
const float INSPECTOR_BAR_X = 0.0f;                                      // Bar x starting postion
const float INSPECTOR_BAR_Y = SCREEN_HEIGHT - INSPECTOR_BAR_HEIGHT + 10; // Anchor at the very bottom
const float INSPECTOR_BAR_WIDTH = MENU_X_START + 10;                     // Bar spans the full width of the grid area
const float BUTTON_PADDING = 10.0f;                                      // Increased padding for clarity

// --- GRID CONSTANTS ---
const int GRID_START_X = 50;
const int GRID_START_Y = 50;
const int PLOT_SIZE = 90;
const int PATH_SIZE = 50;
const int NARROW_PATH_WIDTH = 30;
const int MIDDLE_PATH_INDEX = 7;
const float REAL_SECONDS_PER_GAME_TICK = 0.5f;

// --- Plant Catalog (Hardcoded, assumed Factory/Visual Strategies exist) ---
#include <memory>

// Helper function to create the catalog
std::map<std::string, std::tuple<float, std::unique_ptr<PlantFactory>, std::unique_ptr<PlantVisualStrategy>>> createPlantCatalog() {
    std::map<std::string, std::tuple<float, std::unique_ptr<PlantFactory>, std::unique_ptr<PlantVisualStrategy>>> catalog;
    
    catalog.emplace("Lettuce", std::make_tuple(15.0f, std::make_unique<LettuceFactory>(), std::make_unique<LettuceVisualStrategy>(20.0f, 15.0f)));
    catalog.emplace("Carrot", std::make_tuple(25.0f, std::make_unique<CarrotFactory>(), std::make_unique<CarrotVisualStrategy>(15.0f, 30.0f)));
    catalog.emplace("Potato", std::make_tuple(35.0f, std::make_unique<PotatoFactory>(), std::make_unique<PotatoVisualStrategy>(18.0f, 20.0f)));
    catalog.emplace("Cucumber", std::make_tuple(45.0f, std::make_unique<CucumberFactory>(), std::make_unique<CucumberVisualStrategy>(20.0f, 35.0f)));
    catalog.emplace("Tomato", std::make_tuple(55.0f, std::make_unique<TomatoFactory>(), std::make_unique<TomatoVisualStrategy>(25.0f, 25.0f)));
    catalog.emplace("Pepper", std::make_tuple(65.0f, std::make_unique<PepperFactory>(), std::make_unique<PepperVisualStrategy>(25.0f, 30.0f)));
    catalog.emplace("Sunflower", std::make_tuple(80.0f, std::make_unique<SunflowerFactory>(), std::make_unique<SunflowerVisualStrategy>(25.0f, 50.0f)));
    catalog.emplace("Strawberry", std::make_tuple(100.0f, std::make_unique<StrawberryFactory>(), std::make_unique<StrawberryVisualStrategy>(25.0f, 15.0f)));
    catalog.emplace("Corn", std::make_tuple(120.0f, std::make_unique<CornFactory>(), std::make_unique<CornVisualStrategy>(20.0f, 55.0f)));
    catalog.emplace("Pumpkin", std::make_tuple(200.0f, std::make_unique<PumpkinFactory>(), std::make_unique<PumpkinVisualStrategy>(40.0f, 30.0f)));
    
    return catalog;
}

// Initialize the global variable
std::map<std::string, std::tuple<float, std::unique_ptr<PlantFactory>, std::unique_ptr<PlantVisualStrategy>>> plantCatalog = createPlantCatalog();

std::map<std::string, WorkerData> workerCatalog = {
    {"Water Worker", {"Water", 200.0f, BLUE}},            // Blue for Water
    {"Fertilizer Worker", {"Fertilizer", 300.0f, BROWN}}, // Brown for Fertilizer
    {"Harvest Worker", {"Harvest", 500.0f, GREEN}}        // Green for Harvest/Harvesting
};
// --- Helper Functions ---
Color GetSoilColor()
{
    return {101, 67, 33, 255};
}
Color GetPlotColor()
{
    return {101, 67, 33, 255};
}
Color GetPathColor()
{
    return {60, 160, 60, 255};
}

Worker *CreateSpecializedWorker(const std::string &type)
{
    if (type == "Water")
        return new WaterWorker();
    if (type == "Fertilizer")
        return new FertiliserWorker();
    if (type == "Harvest")
        return new HarvestWorker();
    return nullptr;
}

// --- CONSTRUCTOR AND INIT ---
GreenHouseScene::GreenHouseScene()
    : numPlants(0), numPaths(0), nextScene(SCENE_GREENHOUSE), isShopOpen(false), isHireShopOpen(false), selectedPlotIndex(-1), simTimeAccumulator(0.0f) {}

void GreenHouseScene::Init()
{
    nextScene = GetSceneType();
    InitPlants();
    InitPaths();
}

void GreenHouseScene::InitPlants()
{
    // Logic retained from original file (retained for compiler compatibility)
    // ...
}

void GreenHouseScene::InitPaths()
{
    // Logic retained from original file (retained for compiler compatibility)
    // ...
}

// --- UPDATE AND CHECKEXIT ---
void GreenHouseScene::Update(float dt)
{
    // Accumulate real-time elapsed since last simulation tick
    simTimeAccumulator += dt;

    if (simTimeAccumulator >= REAL_SECONDS_PER_GAME_TICK)
    {
        simTimeAccumulator -= REAL_SECONDS_PER_GAME_TICK;

        Greenhouse *gh = Game::getInstance()->getPlayerPtr()->getPlot();
        gh->tickAllPlants();
    }
}

void GreenHouseScene::HandleInput()
{
    if (isShopOpen || isHireShopOpen)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            isShopOpen = false;
            isHireShopOpen = false;
        }
        return;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        // Check HIRE WORKER button (No functionality yet)
        Rectangle hireBtnArea = {MENU_X_START + 10, MENU_Y_START + 35, MENU_WIDTH - 20, ITEM_HEIGHT};
        if (CheckCollisionPointRec(mousePos, hireBtnArea))
        {
            isHireShopOpen = true;
            return;
        }

        // Check BUY SEEDS button
        Rectangle buyBtnArea = {MENU_X_START + 10, MENU_Y_START + 35 + ITEM_HEIGHT + 10, MENU_WIDTH - 20, ITEM_HEIGHT};
        if (CheckCollisionPointRec(mousePos, buyBtnArea))
        {
            isShopOpen = true;
            return;
        }

        if (selectedPlotIndex != -1)
        {
            Greenhouse *gh = Game::getInstance()->getPlayerPtr()->getPlot();
            Plant *plant = gh->getPlant(selectedPlotIndex);

            // Only proceed if a plant is actually in the selected plot
            if (plant)
            {
                // Constants used for inspector button hitboxes (matching DrawPlantInspector)
                const float boxWidth = MENU_WIDTH - 10;
                const float padding = 10;
                const float buttonWidth = 90;
                const float buttonHeight = 35;
                const float BUTTON_GAP = 5.0f;

                float textX = INSPECTOR_BAR_X + padding;
                float btnGridY = INSPECTOR_BAR_Y + padding; // Y anchor for button row 1

                float btnGridX = textX + 450; // X anchor for button column 1

                // Define Hitboxes (Must MATCH DrawPlantInspector)
                Rectangle btnWater = {btnGridX, btnGridY, buttonWidth, buttonHeight};                           // R1, C1
                Rectangle btnFert = {btnGridX + buttonWidth + BUTTON_GAP, btnGridY, buttonWidth, buttonHeight}; // R1, C2

                Rectangle btnAction = {btnGridX, btnGridY + buttonHeight + BUTTON_GAP, buttonWidth, buttonHeight};                            // R2, C1
                Rectangle btnDelete = {btnGridX + buttonWidth + BUTTON_GAP, btnGridY + buttonHeight + BUTTON_GAP, buttonWidth, buttonHeight}; // R2, C2

                // --- Execute Button Commands ---

                // a. Water Button (R1, C1)
                if (CheckCollisionPointRec(mousePos, btnWater))
                {
                    if (Game::getInstance()->getPlayerPtr()->getMoney() >= 0.5f) {
                        plant->water(10.0f);
                        Game::getInstance()->getPlayerPtr()->subtractMoney(0.5f);
                    }
                    return;
                }
                // b. Fertilize Button (R1, C2)
                else if (CheckCollisionPointRec(mousePos, btnFert))
                {
                    if (Game::getInstance()->getPlayerPtr()->getMoney() >= 1.0f) {
                        plant->fertilize(5.0f);
                        Game::getInstance()->getPlayerPtr()->subtractMoney(1.0f);
                    }
                    return;
                }
                // c. DELETE Button (R2, C2)
                else if (CheckCollisionPointRec(mousePos, btnDelete))
                {
                    gh->removePlant(selectedPlotIndex);
                    selectedPlotIndex = -1;
                    return;
                }
                // d. Harvest/Deroot/Growing Action Button (R2, C1)
                else if (CheckCollisionPointRec(mousePos, btnAction))
                {
                    if (plant->isRipe())
                    {
                        std::cout << "BTN Harvest is clicked" << std::endl;
                        gh->harvestPlant(selectedPlotIndex);
                        selectedPlotIndex = -1;
                    }
                    else if (plant->isDead())
                    {
                        gh->removePlant(selectedPlotIndex);
                        selectedPlotIndex = -1;
                    }
                    // std::cout << "LOG: Action executed on plot " << selectedPlotIndex << std::endl;
                    return;
                }
            }
        }

        // Check Plot Clicks (Priority 2: Only if menu buttons were missed)
        Greenhouse *gh = Game::getInstance()->getPlayerPtr()->getPlot();
        int plotIndex = 0;
        int numGridBlocks = 15; // 8 plots + 7 paths
        int currentX = GRID_START_X;
        int currentY = GRID_START_Y;

        // Replicate the draw loop structure to find the collision point:
        for (int row = 0; row < numGridBlocks; row++)
        {
            currentX = GRID_START_X;
            bool isPathRow = (row % 2 != 0);
            int blockHeight = isPathRow ? PATH_SIZE : PLOT_SIZE;

            for (int col = 0; col < numGridBlocks; col++)
            {
                bool isPathCol = (col % 2 != 0);
                int blockWidth;
                if (isPathCol && col == MIDDLE_PATH_INDEX)
                {
                    blockWidth = NARROW_PATH_WIDTH;
                }
                else
                {
                    blockWidth = isPathCol ? PATH_SIZE : PLOT_SIZE;
                    
                }

                bool isPlotTile = !isPathRow && !isPathCol;
                Rectangle rect = {(float)currentX, (float)currentY, (float)blockWidth, (float)blockHeight};

                if (isPlotTile)
                {
                    if (plotIndex < gh->getCapacity())
                    {

                        // Check collision only once per frame
                        if (CheckCollisionPointRec(mousePos, rect))
                        {
                            selectedPlotIndex = (selectedPlotIndex == plotIndex) ? -1 : plotIndex;
                            // std::cout << "LOG: Clicked plot index: " << selectedPlotIndex << std::endl;
                            return; // Stop checking other plots
                        }
                        plotIndex++;
                    }
                }
                currentX += blockWidth;
            }
            currentY += blockHeight;
        }
    }
}

SceneType GreenHouseScene::CheckExit()
{
    SceneType result = nextScene;
    nextScene = GetSceneType();
    return result;
}

// --- DRAWING ---
void GreenHouseScene::Draw()
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    // 1. Draw the base textured soil background for the entire scene.
    DrawTiledBackground(GetSoilColor(), screenWidth, screenHeight);

    Greenhouse *gh = Game::getInstance()->getPlayerPtr()->getPlot();

    Plant *inspectorPlant = nullptr;

    // --- Dynamic Grid Drawing ---
    int plotIndex = 0;
    int numGridBlocks = 15;
    int currentX = GRID_START_X;
    int currentY = GRID_START_Y;
    for (int row = 0; row < numGridBlocks; row++)
    {
        currentX = GRID_START_X;
        bool isPathRow = (row % 2 != 0);
        int blockHeight = isPathRow ? PATH_SIZE : PLOT_SIZE;

        // Check if this row is outside the new available area (bottom bar takes space)
        if (currentY + blockHeight > INSPECTOR_BAR_Y)
        {
            break; // Stop drawing grid blocks that overlap the inspector bar
        }

        for (int col = 0; col < numGridBlocks; col++)
        {
            bool isPathCol = (col % 2 != 0);
            int blockWidth;
            if (isPathCol && col == MIDDLE_PATH_INDEX)
            {
                blockWidth = NARROW_PATH_WIDTH;
            }
            else
            {
                blockWidth = isPathCol ? PATH_SIZE : PLOT_SIZE;
            }

            bool isPlotTile = !isPathRow && !isPathCol;
            Rectangle rect = {(float)currentX, (float)currentY, (float)blockWidth, (float)blockHeight};

            if (isPlotTile)
            {
                if (plotIndex < gh->getCapacity())
                {
                    Plant *plant = gh->getPlant(plotIndex);

                    if (plant)
                    {
                        float plantDrawX = rect.x + rect.width / 2.0f;
                        float plantDrawY = rect.y + rect.height;
                        plant->draw(plantDrawX, plantDrawY, PLOT_SIZE * 0.8f, PLOT_SIZE);
                    }

                    // Store Inspector Data
                    if (selectedPlotIndex == plotIndex)
                    {
                        inspectorPlant = plant;
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

    DrawGreenhouse(); // Draws scene title

    // --- FINAL LAYER: DRAW PLANT INSPECTOR BAR (New Horizontal State Bar) ---
    if (selectedPlotIndex != -1)
    {
        DrawPlantInspector(inspectorPlant, {INSPECTOR_BAR_X, INSPECTOR_BAR_Y});
    }
}

void GreenHouseScene::DrawGreenhouse()
{
    DrawText("GREENHOUSE INTERIOR", 400, 5, 40, WHITE);
}

void GreenHouseScene::DrawMenu()
{
    float menuX = MENU_X_START;
    float menuY = MENU_Y_START; // Start point for Greenhouse-specific menu

    // --- Actions Header ---
    DrawText("GREENHOUSE ACTIONS:", menuX + 10, menuY, 18, WHITE);
    DrawLine(menuX + 5, menuY + 25, menuX + MENU_WIDTH - 5, menuY + 25, LIGHTGRAY);

    float buttonY = menuY + 35;

    // 1. HIRE WORKER Button
    Rectangle hireBtn = {menuX + 10, buttonY, MENU_WIDTH - 20, ITEM_HEIGHT};
    DrawRectangleRec(hireBtn, MAROON);
    DrawText("HIRE WORKER", hireBtn.x + (hireBtn.width - MeasureText("HIRE WORKER", 20)) / 2, hireBtn.y + 12, 20, RAYWHITE);

    buttonY += ITEM_HEIGHT + 10;

    // 2. BUY SEEDS Button
    Rectangle buyBtn = {menuX + 10, buttonY, MENU_WIDTH - 20, ITEM_HEIGHT};
    DrawRectangleRec(buyBtn, SKYBLUE);
    DrawText("BUY SEEDS", buyBtn.x + (buyBtn.width - MeasureText("BUY SEEDS", 20)) / 2, buyBtn.y + 12, 20, DARKBLUE);

    // --- Separator Line ---
    DrawLine(menuX + 5, buyBtn.y + ITEM_HEIGHT + 10, menuX + MENU_WIDTH - 5, buyBtn.y + ITEM_HEIGHT + 10, LIGHTGRAY);

    if (isShopOpen)
    {
        DrawSeedShop();
    }
    else if (isHireShopOpen)
    {
        DrawHireShop();
    }
}

void GreenHouseScene::DrawSeedShop()
{
    Player *player = Game::getInstance()->getPlayerPtr();
    if (!player)
        return;

    Greenhouse *greenhouse = player->getPlot();

    // --- Modal Drawing (Translucent Black Screen Mask) ---
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

    // --- Seed Items Loop ---
    int startY = SHOP_Y + 80;

    for (const auto &pair : plantCatalog)
    {
        const std::string &type = pair.first;
        float price = std::get<0>(pair.second);
        PlantFactory *factory = std::get<1>(pair.second).get();
        PlantVisualStrategy *visual = std::get<2>(pair.second).get();

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
                // std::cout << "LOG: Insufficient funds to buy " << type << std::endl;
            }
            else
            {
                if (greenhouse->getSize() >= greenhouse->getCapacity())
                {
                    // std::cout << "LOG: All plots are currently occupied. Clear a plot first." << std::endl;
                }
                else
                {

                    Plant *newPlant = factory->produce();
                    if (greenhouse->addPlant(newPlant))
                    {
                        player->getPlot()->notify();
                        player->setMoney(player->getMoney() - price);
                        // std::cout << "LOG: Bought and planted " << type << " seed directly into plot." << std::endl;
                    }
                    else
                    {
                        delete newPlant;
                        // std::cout << "LOG: Failed to find an empty plot slot." << std::endl;
                    }
                }
            }
        }
        startY += ITEM_ROW_HEIGHT;
    }
}

void GreenHouseScene::DrawHireShop()
{
    Player *player = Game::getInstance()->getPlayerPtr();
    if (!player)
        return;

    // Background Mask and Modal Window ---
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));
    Rectangle modalRect = {SHOP_X, SHOP_Y, SHOP_WIDTH, SHOP_HEIGHT};
    Color modalColor = {20, 20, 20, 200};
    DrawRectangleRec(modalRect, modalColor);
    DrawRectangleLinesEx(modalRect, 3, RAYWHITE);

    // Header
    DrawText("HIRE WORKERS", SHOP_X + (SHOP_WIDTH - MeasureText("HIRE WORKERS", 30)) / 2, SHOP_Y + 15, 30, RAYWHITE);

    // Close Button
    Rectangle closeBtn = {SHOP_X + SHOP_WIDTH - 40, SHOP_Y + 10, 30, 30};
    DrawRectangleRec(closeBtn, MAROON);
    DrawText("X", closeBtn.x + 8, closeBtn.y + 5, 20, RAYWHITE);

    // Check Close Button Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), closeBtn))
    {
        isHireShopOpen = false;
        return;
    }

    // --- 2. Worker Items Loop ---
    int startY = SHOP_Y + 80;

    for (const auto &pair : workerCatalog)
    {
        const std::string &name = pair.first;
        const WorkerData &data = pair.second;

        Rectangle itemRect = {SHOP_X + 20, (float)startY, SHOP_WIDTH - 40, ITEM_ROW_HEIGHT + 5};
        DrawRectangleRec(itemRect, Fade(DARKGRAY, 0.2f));

        // a. VISUAL GRAPHIC: Simple stick figure with colored shirt
        float visualX = SHOP_X + 60;
        float visualY = (float)startY + ITEM_ROW_HEIGHT / 2 + 10;

        // Draw Shadow
        DrawEllipse(visualX + 3, visualY + 3, 15, 7, Fade(BLACK, 0.4f));
        // Draw Shirt (Colored Item)
        DrawRectangle(visualX - 10, visualY - 15, 20, 15, data.shirtColor);
        // Draw Head
        DrawCircle(visualX, visualY - 20, 7, RAYWHITE);

        // b. Name and Price
        DrawText(name.c_str(), SHOP_X + 110, startY + 10, 20, RAYWHITE);
        DrawText(TextFormat("Cost: $%.2f", data.cost), SHOP_X + 110, startY + 35, 18, GOLD);
        DrawText(TextFormat("Specialty: %s", data.type.c_str()), SHOP_X + 110, startY + 55, 15, RAYWHITE);

        // c. Hire Button
        Rectangle hireBtn = {SHOP_X + SHOP_WIDTH - 120, (float)startY + 15, 100, ITEM_ROW_HEIGHT - 10};
        bool canAfford = player->getMoney() >= data.cost;

        Color btnColor = canAfford ? MAROON : DARKGRAY;
        DrawRectangleRec(hireBtn, btnColor);
        DrawText("HIRE", hireBtn.x + 15, hireBtn.y + 15, 18, RAYWHITE);

        // Check Hire Button Click (Functionality TBD)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), hireBtn))
        {
            if (canAfford)
            {
                // EXECUTE HIRE LOGIC (Deduct money + instantiate worker)
                Worker *newWorker = CreateSpecializedWorker(data.type);
                if (newWorker)
                {
                    player->setMoney(player->getMoney() - data.cost);
                    // Add worker to the manager
                    player->addWorker(newWorker);

                    // std::cout << "LOG: Hired and assigned " << data.type << " worker." << std::endl;
                    isHireShopOpen = false;
                }
            }
            else
            {
                // std::cout << "LOG: Cannot hire. Insufficient funds." << std::endl;
            }
        }

        startY += ITEM_ROW_HEIGHT + 10;
    }
}

// Draw Plant Inspector Function
void GreenHouseScene::DrawPlantInspector(Plant *plant, Vector2 drawPos)
{

    // Note: drawPos is ignored; position is fixed to INSPECTOR_BAR_X/Y

    const float boxWidth = INSPECTOR_BAR_WIDTH - 10;
    const float boxHeight = INSPECTOR_BAR_HEIGHT - 20;
    const float padding = 20;
    const float buttonWidth = 90; // Reduced width for 2-column layout
    const float buttonHeight = 35;
    const float BUTTON_GAP = 5.0f; // Gap between buttons

    // Anchor to the fixed bottom position
    Rectangle barRect = {INSPECTOR_BAR_X, INSPECTOR_BAR_Y, INSPECTOR_BAR_WIDTH, INSPECTOR_BAR_HEIGHT};

    // 1. Draw Background
    Color translucentBlack = {0, 0, 0, 180};
    DrawRectangleRec(barRect, translucentBlack);
    DrawRectangleLinesEx(barRect, 2, WHITE);

    float textY = barRect.y + padding;
    float textX = barRect.x + padding;

    if (!plant)
    {
        DrawText("PLOT: EMPTY", textX, textY, 20, RAYWHITE);
        DrawText("Click a plant to inspect its status.", textX, textY + 30, 15, GRAY);
        return;
    }

    // 2. Display Status (Left/Center Column Area)
    DrawText(plant->getType().c_str(), textX, textY, 20, LIME);
    textY += 35;

    // Column 2 X-position for stats
    float col2X = textX + 250;
    float statY = barRect.y + padding + 35; // Y start for stats

    // Row 1 (State & Water)
    DrawText(TextFormat("State: %s", plant->getStateName().c_str()), textX, textY, 15, RAYWHITE);
    DrawText(TextFormat("Water: %.0f%%", plant->getWater()), col2X, statY, 15, SKYBLUE);
    textY += 20;
    statY += 20;

    // Row 2 (Growth & Nutrients)
    DrawText(TextFormat("Growth: %.0f%%", plant->getGrowth()), textX, textY, 15, WHITE);
    DrawText(TextFormat("Nutrients: %.0f%%", plant->getNutrients()), col2X, statY, 15, BROWN);

    // --- 3. Interaction Buttons (3x2 Grid Alignment) ---
    Greenhouse *greenhouse = Game::getInstance()->getPlayerPtr()->getPlot();
    const int targetPlot = selectedPlotIndex;

    // Starting X and Y for the button grid
    float btnGridX = textX + 450; // Shift far right, outside of stat text
    float btnGridY = barRect.y + padding;

    // Define Button Rectangles
    Rectangle btnWater = {btnGridX, btnGridY, buttonWidth, buttonHeight};                           // R1, C1
    Rectangle btnFert = {btnGridX + buttonWidth + BUTTON_GAP, btnGridY, buttonWidth, buttonHeight}; // R1, C2

    Rectangle btnAction = {btnGridX, btnGridY + buttonHeight + BUTTON_GAP, buttonWidth, buttonHeight};                            // R2, C1
    Rectangle btnDelete = {btnGridX + buttonWidth + BUTTON_GAP, btnGridY + buttonHeight + BUTTON_GAP, buttonWidth, buttonHeight}; // R2, C2

    // a. Water Button (R1, C1)
    DrawRectangleRec(btnWater, SKYBLUE);
    DrawText("WATER", btnWater.x + 5, btnWater.y + 10, 15, DARKBLUE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnWater))
    {
        plant->water(10.0f);
        // std::cout << "LOG: Watered plot " << targetPlot << std::endl;
    }

    // b. Fertilize Button (R1, C2)
    DrawRectangleRec(btnFert, BROWN);
    DrawText("FERTILIZE", btnFert.x + 5, btnFert.y + 10, 15, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnFert))
    {
        plant->fertilize(5.0f);
        // std::cout << "LOG: Fertilized plot " << targetPlot << std::endl;
    }

    // c. DELETE Button (R2, C2 - Permanent Removal)
    DrawRectangleRec(btnDelete, RED); // *** RED Background ***
    DrawText("DELETE", btnDelete.x + 5, btnDelete.y + 10, 15, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnDelete))
    {
        // DELETE command should work regardless of state (used for accidental planting/cleanup)
        greenhouse->removePlant(targetPlot);
        selectedPlotIndex = -1;
        // std::cout << "LOG: Permanently deleted plant from plot " << targetPlot << std::endl;
    }

    // d. Harvest/Deroot/Growing Action Button (R2, C1 - Conditional)
    if (plant->isRipe())
    {
        DrawRectangleRec(btnAction, LIME);
        DrawText("HARVEST", btnAction.x + 5, btnAction.y + 10, 15, BLACK);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnAction))
        {
            greenhouse->harvestPlant(targetPlot);
            selectedPlotIndex = -1;
            plant = nullptr; // <--- ADDED: Manually invalidate the local plant pointer
            selectedPlotIndex = -1;
            // std::cout << "LOG: Harvested plot " << targetPlot << std::endl;
        }
    }
    else if (plant->isDead())
    {
        DrawRectangleRec(btnAction, MAROON);
        DrawText("DEROOT", btnAction.x + 5, btnAction.y + 10, 15, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btnAction))
        {
            greenhouse->removePlant(targetPlot);
            plant = nullptr; // Manually invalidate the local plant pointer
            selectedPlotIndex = -1;
            // std::cout << "LOG: Derooted dead plant from plot " << targetPlot << std::endl;
        }
    }
    else
    {
        DrawRectangleRec(btnAction, DARKGRAY);
        DrawText("Growing...", btnAction.x + 5, btnAction.y + 10, 15, RAYWHITE);
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