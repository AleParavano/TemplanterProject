#include "StoreScene.h"
#include "../Backend/Player.h"

StoreScene::StoreScene()
    : showModal(false),
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

void StoreScene::update(Player *player)
{
    Vector2 mouse = GetMousePosition();

    // Toggle player inventory when manage plants is clicked
    if (CheckCollisionPointRec(mouse, manageToggle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (player)
        {
            if (!player->getInventoryUI()->isInventoryOpen())
            {
                player->getInventoryUI()->toggle();
            }
            else
            {
                player->getInventoryUI()->toggle();
            }
        }
    }

    // Close inventory with ESC
    if (showModal && IsKeyPressed(KEY_ESCAPE))
    {
        showModal = false;

        if (player && player->getInventoryUI()->isInventoryOpen())
        {
            player->getInventoryUI()->toggle();
        }
    }

    // Toggle store open/closed - NOW INDEPENDENT OF MANAGE PLANTS BUTTON
    if (CheckCollisionPointRec(mouse, openNClose) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        toggleOpen();
    }

    // Update customers - NOW ALWAYS RUNS WHEN PLAYER EXISTS
    if (player)
    {
        updateCustomers(GetFrameTime(), player);
    }
}
void StoreScene::updateCustomers(float deltaTime, Player *player)
{
    if (!customerManager || !player)
        return;

    // Update customer manager (spawning, movement, etc)
    customerManager->update(deltaTime, storeOpen);

    // Handle customer clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !showModal && player->getInventoryUI()->isInventoryOpen())
    {
        Vector2 mouse = GetMousePosition();
        CustomerVisual *clickedCustomer = customerManager->getClickedCustomer(mouse);

        if (clickedCustomer)
        {
            // Check if player has a selected item
            int selectedSlot = player->getInventoryUI()->getSelectedSlotIndex();
            if (selectedSlot != -1)
            {
                // CRITICAL: Get fresh slot data each time
                const InventorySlot *slot = player->getInventory()->getSlot(selectedSlot);

                // Check if slot is valid and not empty
                if (slot && !slot->isEmpty())
                {
                    std::string plantType = slot->getPlantType();

                    // Verify the plant type is valid
                    if (!plantType.empty())
                    {
                        // Try to serve the customer
                        if (customerManager->serveCustomer(clickedCustomer, plantType))
                        {
                            // Remove one plant from player inventory
                            Plant *plant = player->getInventory()->removeItem(plantType);
                            if (plant)
                            {
                                delete plant; // Customer took the plant
                            }

                            // Clear selection after serving
                            player->getInventoryUI()->clearSlotSelection();
                            // TODO: Add money to player for successful sale
                            // player->addMoney(plant->getPrice());
                        }
                        else
                        {
                            // Wrong plant - maybe show feedback to player
                            // Don't remove anything from inventory
                        }
                    }
                    else
                    {
                        // Invalid plant type - clear selection
                        player->getInventoryUI()->clearSlotSelection();
                    }
                }
                else
                {
                    // Empty slot selected - clear selection
                    player->getInventoryUI()->clearSlotSelection();
                }
            }
            else
            {
                // No item selected - just dismiss the customer
                customerManager->dismissCustomer(clickedCustomer);
            }
        }
    }
}

void StoreScene::render()
{
    ClearBackground(GRAY);

    DrawRectangle(875, 88, 525, 613, RAYWHITE);

    int cellSize = 88;

    for (int i = 868; i < GetScreenWidth(); i += cellSize)
    {
        DrawRectangle(i, 88, 12, 613, LIGHTGRAY);
    }
    for (int j = 163; j < 700; j += cellSize)
    {
        DrawRectangle(875, j, 525, 12, LIGHTGRAY);
    }

    for (int i = 875; i < GetScreenWidth(); i += cellSize)
    {
        DrawLine(i, 88, i, 700, BLACK);
    }
    for (int j = 88; j <= 700; j += cellSize)
    {
        DrawLine(875, j, GetScreenWidth(), j, BLACK);
    }

    Color customColor = {178, 102, 0, 255};
    Color custColor2 = {30, 15, 0, 255};
    Color custColor3 = {86, 49, 0, 255};
    DrawRectangle(875, 613, 350, 131, customColor);
    DrawRectangle(875, 660, 350, 84, custColor3);
    for (int i = 889; i < 1225; i += 168)
    {
        for (int j = 665; j < 744; j += 40)
        {
            DrawRectangle(i, j, 154, 35, custColor2);
        }
    }
    for (int i = 875; i <= 1225; i += 35)
    {
        DrawLine(i, 613, i, 660, custColor3);
    }
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

    // Draw store open/closed status
    if (storeOpen)
    {
        DrawText("Open", 1030, 10, 20, RED);
        openNClose = {1028, 8, 52, 22};
        DrawRectangleRec(openNClose, Color{255, 0, 0, 100});
    }
    else
    {
        DrawText("Closed", 1020, 10, 20, RED);
        openNClose = {1018, 8, 70, 22};
        DrawRectangleRec(openNClose, Color{255, 0, 0, 100});
    }

    // Render customers
    if (customerManager)
    {
        customerManager->render();
    }
}

string StoreScene::getType()
{
    return "Store";
}