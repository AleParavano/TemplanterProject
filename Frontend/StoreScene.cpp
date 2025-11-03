#include "StoreScene.h"
#include "../Backend/Player.h"
#include <iostream>

StoreScene::StoreScene()
    : player(nullptr),
      showModal(false),
      selectedPlantFromGrid(false),
      selectedGridX(-1),
      selectedGridY(-1),
      manageToggle{341, 376, 149, 35},
      counterHitBox{875, 613, 525, 47},
      sDoor{1225, 613, 175, 46},
      plotHitBox{131, 131, 560, 525},
      boundaryWall{823, 0, 53, 660}
{
    backendStore = new Store();
    customerManager = new CustomerManager({1270, 0}, {1200, 580});
}

StoreScene::~StoreScene()
{
    delete backendStore;
    delete customerManager;
}

void StoreScene::Init()
{
    showModal = false;
    selectedPlantFromGrid = false;
    selectedGridX = -1;
    selectedGridY = -1;
    storeOpen = false;
    
    // Ensure inventory is closed on scene entry
    if (player && player->getInventoryUI()->isInventoryOpen()) {
        player->getInventoryUI()->toggle();
    }
}

void StoreScene::UpdateStoreHours()
{
    if (!player || !customerManager) return;
    
    int currentHour = player->getHour();
    
    // Automatically close store if it's outside business hours (7:00 - 18:00)
    if (storeOpen && (currentHour >= 18 || currentHour < 7))
    {
        storeOpen = false;
        
        // Dismiss all customers when closing
        customerManager->dismissAllCustomers();
        
    }
}

bool StoreScene::canOpenStore() const
{
    if (!player) return false;
    
    int currentHour = player->getHour();
    
    // Store can only be open between 7:00 and 18:00
    return (currentHour >= 7 && currentHour < 18);
}

void StoreScene::toggleOpen()
{
    if (storeOpen)
    {
        // Can always close the store
        storeOpen = false;
    }
    else
    {
        // Can only open during business hours
        if (canOpenStore())
        {
            storeOpen = true;
        }
        else
        {
        }
    }
}

void StoreScene::Update(float dt)
{
    if (player)
    {
        // Check and enforce store hours every frame
        UpdateStoreHours();
        
        // Update customers
        UpdateCustomers(dt);
        
        // Update the InventoryUI logic every frame
        player->getInventoryUI()->update();
    }
}

void StoreScene::HandleInput()
{
    Vector2 mouse = GetMousePosition();

    // --- 1. Global 'E' Key Toggle ---
    if (IsKeyPressed(KEY_E))
    {
        if (player)
        {
            player->getInventoryUI()->toggle();
            return; 
        }
    }

    // --- 2. Check Modals/Escape (Inventory) ---
    if (player && player->getInventoryUI()->isInventoryOpen() && IsKeyPressed(KEY_ESCAPE))
    {
        player->getInventoryUI()->toggle();
        return;
    }
    
    if (showModal && IsKeyPressed(KEY_ESCAPE))
    {
        showModal = false;
        return;
    }

    // --- 3. Mouse Input ---
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Check Manage Plants Button (Toggles Inventory UI)
        if (CheckCollisionPointRec(mouse, manageToggle))
        {
            if (player)
            {
                player->getInventoryUI()->toggle(); 
                return;
            }
        }

        // Toggle store open/closed button (with time constraints)
        if (CheckCollisionPointRec(mouse, openNClose))
        {
            toggleOpen();
            return;
        }

        // --- CUSTOMER INTERACTION (ONLY if Inventory is Open) ---
        if (player && player->getInventoryUI()->isInventoryOpen())
        {
            CustomerVisual *clickedCustomer = customerManager->getClickedCustomer(mouse);

            if (clickedCustomer)
            {
                // Check if player has a selected item (in InventoryUI)
                int selectedSlot = player->getInventoryUI()->getSelectedSlotIndex();
                if (selectedSlot != -1)
                {
                    const InventorySlot *slot = player->getInventory()->getSlot(selectedSlot);

                    if (slot && !slot->isEmpty())
                    {
                        std::string plantType = slot->getPlantType();

                        if (customerManager->serveCustomer(clickedCustomer, plantType))
                        {
                            Plant *plant = player->getInventory()->removeItem(plantType);
                            if (plant)
                            {
                                float salePrice = plant->getSellPrice();
                                player->addMoney(salePrice);
                                player->addRating(0.4);
                                delete plant; 
                            }
                            player->getInventoryUI()->clearSlotSelection();
                        }
                    }
                    else
                    {
                        player->getInventoryUI()->clearSlotSelection();
                    }
                }
                else
                {
                    customerManager->dismissCustomer(clickedCustomer);
                }
                return;
            }
        }
    }
}

void StoreScene::UpdateCustomers(float deltaTime)
{
    if (!customerManager || !player)
        return;

    customerManager->update(deltaTime, storeOpen);
}

void StoreScene::Draw()
{
    ClearBackground(GRAY);

    // Draw Store Environment
    DrawRectangle(875, 88, 525, 613, RAYWHITE);

    int cellSize = 88;
    for (int i = 868; i < GetScreenWidth(); i += cellSize) { DrawRectangle(i, 88, 12, 613, LIGHTGRAY); }
    for (int j = 163; j < 700; j += cellSize) { DrawRectangle(875, j, 525, 12, LIGHTGRAY); }
    for (int i = 875; i < GetScreenWidth(); i += cellSize) { DrawLine(i, 88, i, 700, BLACK); }
    for (int j = 88; j <= 700; j += cellSize) { DrawLine(875, j, GetScreenWidth(), j, BLACK); }

    Color customColor = {178, 102, 0, 255};
    Color custColor2 = {30, 15, 0, 255};
    Color custColor3 = {86, 49, 0, 255};
    DrawRectangle(875, 613, 350, 131, customColor);
    DrawRectangle(875, 660, 350, 84, custColor3);
    for (int i = 889; i < 1225; i += 168) {
        for (int j = 665; j < 744; j += 40) { DrawRectangle(i, j, 154, 35, custColor2); }
    }
    for (int i = 875; i <= 1225; i += 35) { DrawLine(i, 613, i, 660, custColor3); }
    DrawLine(875, 660, 1225, 660, custColor3);
    DrawRectangleRec(counterHitBox, Color{0, 0, 0, 0});
    DrawRectangleRec(sDoor, customColor);
    DrawRectangle(1225, 658, 175, 5, custColor3);
    DrawLine(1225, 613, 1225, 744, BLACK);
    Color custColor5 = {50, 50, 50, 255};
    DrawRectangleRec(boundaryWall, DARKGRAY);
    Rectangle boundaryWallShadow = {823, 569, 53, 175};
    DrawRectangleRec(boundaryWallShadow, custColor5);
    Color custColor4 = {50, 25, 0, 255};
    DrawRectangle(131, 131, 560, 525, customColor);
    DrawRectangle(149, 149, 525, 490, custColor4);
    DrawRectangle(131, 656, 560, 35, custColor3);
    DrawRectangleRec(plotHitBox, Color{0, 0, 0, 0});
    DrawRectangle(1225, 0, 88, 18, Color{50, 100, 50, 255});
    DrawRectangle(875, 0, 350, 88, custColor5);
    DrawRectangle(1313, 0, 88, 88, custColor5);
    DrawRectangle(1295, 0, 18, 70, custColor3);
    DrawRectangle(919, 0, 263, 53, custColor3);
    DrawRectangle(928, 0, 245, 44, customColor);
    DrawRectangle(928, 0, 245, 35, Color{130, 200, 250, 255});
    DrawRectangle(928, 0, 245, 18, Color{100, 165, 250, 255});

    // Draw "Manage Plants" button
    DrawText("Manage Plants", 350, 385, 18, WHITE);
    DrawRectangleRec(manageToggle, Color{255, 255, 255, 100});

    // Draw store open/closed status with visual feedback
    if (storeOpen)
    {
        DrawText("Open", 1030, 10, 20, RED);
        openNClose = {1028, 8, 52, 22};
        DrawRectangleRec(openNClose, Color{255, 0, 0, 100});
    }
    else
    {
        // Show different color if outside business hours
        bool canOpen = canOpenStore();
        Color statusColor = canOpen ? RED : DARKGRAY;
        Color buttonTint = canOpen ? Color{255, 0, 0, 100} : Color{100, 100, 100, 100};
        
        DrawText("Closed", 1020, 10, 20, statusColor);
        openNClose = {1018, 8, 70, 22};
        DrawRectangleRec(openNClose, buttonTint);
        
        // Optional: Show business hours when closed outside hours
        if (!canOpen && player)
        {
            DrawText("Business Hours: 6:00 - 18:00", 880, 40, 14, DARKGRAY);
        }
    }

    // Render customers
    if (customerManager)
    {
        customerManager->render();
    }
    
    // Render the Inventory UI modal last
    if (player && player->getInventoryUI()->isInventoryOpen()) {
        player->getInventoryUI()->render();
    }
}

SceneType StoreScene::GetSceneType() const
{
    return SCENE_STORE;
}