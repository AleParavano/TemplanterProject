#include "StoreScene.h"
#include "../Backend/Player.h"

StoreScene::StoreScene()
    : showModal(false),
      selectedStorageSlot(-1),
      selectedPlantFromGrid(false),
      selectedGridX(-1),
      selectedGridY(-1),
      manageToggle{341, 376, 149, 35},
      counterHitBox{875, 613, 525, 47},
      sDoor{1225, 613, 175, 46},
      plotHitBox{131, 131, 560, 525},
      boundaryWall{823, 0, 53, 660}
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            plants[i][j] = false;
        }
    }

    backendStore = new Store();
    customerManager = new CustomerManager({1312, 630}, {1200, 630});
}

StoreScene::~StoreScene()
{
    delete backendStore;
    delete customerManager;
}

void StoreScene::update(Player *player)
{
    Inventory *storageInventory = backendStore->getStorage();
    if (!storageInventory)
        return;

    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, manageToggle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        showModal = !showModal;

        if (player)
        {
            if (showModal)
            {
                if (!player->isInventoryOpen())
                {
                    player->openInventory();
                }
            }
            else
            {
                if (player->isInventoryOpen())
                {
                    player->openInventory();
                }
            }
        }

        if (showModal && storageSlots.empty())
        {
            int storagePos = 0;
            for (int i = 401; i < 900 && storagePos < 25; i += 100)
            {
                for (int j = 466; j < 930 && storagePos < 25; j += 100)
                {
                    Rectangle tempRect = {j, i, 75, 75};
                    const InventorySlot *slotData = storageInventory->getSlot(storagePos);
                    Slot tempSlot(slotData, tempRect);
                    storageSlots.push_back(tempSlot);
                    storagePos++;
                }
            }
        }
    }

    if (showModal && IsKeyPressed(KEY_ESCAPE))
    {
        showModal = false;
        storageSlots.clear();
        selectedStorageSlot = -1;

        if (player && player->isInventoryOpen())
        {
            player->openInventory();
        }
    }

    if (CheckCollisionPointRec(mouse, openNClose) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        toggleOpen();
    }

    // Update customers
    updateCustomers(GetFrameTime(), player);
}

void StoreScene::updateCustomers(float deltaTime, Player *player)
{
    if (!customerManager || !player) return;

    // Update customer manager (spawning, movement, etc)
    customerManager->update(deltaTime, storeOpen);

    // Handle customer clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !showModal && player->isInventoryOpen())
    {
        Vector2 mouse = GetMousePosition();
        CustomerVisual* clickedCustomer = customerManager->getClickedCustomer(mouse);

        if (clickedCustomer)
        {
            // Check if player has a selected item
            int selectedSlot = player->getSelectedSlotIndex();
            if (selectedSlot != -1)
            {
                // CRITICAL: Get fresh slot data each time
                const InventorySlot* slot = player->getInventory()->getSlot(selectedSlot);
                
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
                            Plant* plant = player->getInventory()->removeItem(plantType);
                            if (plant)
                            {
                                delete plant; // Customer took the plant
                            }
                            
                            // Clear selection after serving
                            player->clearSlotSelection();
                            
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
                        player->clearSlotSelection();
                    }
                }
                else
                {
                    // Empty slot selected - clear selection
                    player->clearSlotSelection();
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

void StoreScene::updateStorage(Player *player)
{
    if (!player)
        return;

    Inventory *storageInventory = backendStore->getStorage();
    if (!storageInventory)
        return;

    for (int i = 0; i < storageSlots.size(); i++)
    {
        storageSlots[i].slot = storageInventory->getSlot(i);
        storageSlots[i].selected = (i == selectedStorageSlot);
    }

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        bool clickHandled = false;

        if (player->getSelectedSlotIndex() != -1)
        {
            int playerSlotIndex = player->getSelectedSlotIndex();

            for (int i = 0; i < storageSlots.size(); i++)
            {
                if (storageSlots[i].isClicked(mouse))
                {
                    const InventorySlot *playerSlot = player->getInventory()->getSlot(playerSlotIndex);
                    const InventorySlot *storageSlot = storageInventory->getSlot(i);

                    bool shouldMerge = false;
                    if (playerSlot && storageSlot &&
                        !playerSlot->isEmpty() && !storageSlot->isEmpty() &&
                        playerSlot->getPlantType() == storageSlot->getPlantType() &&
                        !storageSlot->isFull())
                    {
                        shouldMerge = true;
                    }

                    if (shouldMerge)
                    {
                        std::string plantType = playerSlot->getPlantType();
                        int spaceAvailable = storageSlot->getRemainingCapacity();
                        int itemsInSource = playerSlot->getSize();
                        int itemsToMove = std::min(spaceAvailable, itemsInSource);

                        for (int j = 0; j < itemsToMove; j++)
                        {
                            const InventorySlot *currentStorageSlot = storageInventory->getSlot(i);
                            if (!currentStorageSlot || currentStorageSlot->isFull())
                                break;

                            Plant *plant = player->getInventory()->removeItem(plantType);
                            if (!plant)
                                break;

                            if (!storageInventory->addToSpecificSlot(plant, i))
                            {
                                player->getInventory()->add(plant);
                                break;
                            }
                        }
                    }
                    else
                    {
                        Inventory::swapBetweenInventories(player->getInventory(), playerSlotIndex,
                                                          storageInventory, i);
                    }

                    for (int k = 0; k < storageSlots.size(); k++)
                    {
                        storageSlots[k].slot = storageInventory->getSlot(k);
                    }

                    player->clearSlotSelection();
                    clickHandled = true;
                    break;
                }
            }
        }

        if (!clickHandled)
        {
            for (int i = 0; i < storageSlots.size(); i++)
            {
                if (storageSlots[i].isClicked(mouse))
                {
                    if (selectedStorageSlot == -1)
                    {
                        if (storageSlots[i].slot != nullptr && !storageSlots[i].slot->isEmpty())
                        {
                            selectedStorageSlot = i;
                            storageSlots[i].selected = true;
                        }
                    }
                    else if (selectedStorageSlot != i)
                    {
                        const InventorySlot *sourceSlot = storageInventory->getSlot(selectedStorageSlot);
                        const InventorySlot *destSlot = storageInventory->getSlot(i);

                        bool shouldMerge = false;
                        if (sourceSlot && destSlot &&
                            !sourceSlot->isEmpty() && !destSlot->isEmpty() &&
                            sourceSlot->getPlantType() == destSlot->getPlantType() &&
                            !destSlot->isFull())
                        {
                            shouldMerge = true;
                        }

                        if (shouldMerge)
                        {
                            std::string plantType = sourceSlot->getPlantType();
                            int spaceAvailable = destSlot->getRemainingCapacity();
                            int itemsInSource = sourceSlot->getSize();
                            int itemsToMove = std::min(spaceAvailable, itemsInSource);

                            for (int j = 0; j < itemsToMove; j++)
                            {
                                const InventorySlot *currentDestSlot = storageInventory->getSlot(i);
                                if (!currentDestSlot || currentDestSlot->isFull())
                                    break;

                                Plant *plant = storageInventory->removeItem(plantType);
                                if (!plant)
                                    break;

                                if (!storageInventory->addToSpecificSlot(plant, i))
                                {
                                    delete plant;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            storageInventory->swapSlots(selectedStorageSlot, i);
                        }

                        storageSlots[selectedStorageSlot].slot = storageInventory->getSlot(selectedStorageSlot);
                        storageSlots[i].slot = storageInventory->getSlot(i);

                        storageSlots[selectedStorageSlot].selected = false;
                        selectedStorageSlot = -1;
                    }
                    else
                    {
                        storageSlots[selectedStorageSlot].selected = false;
                        selectedStorageSlot = -1;
                    }

                    break;
                }
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && selectedStorageSlot != -1)
    {
        storageSlots[selectedStorageSlot].selected = false;
        selectedStorageSlot = -1;
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

    for (int i = 187, k = 0; i < 691; i += 56, k++)
    {
        for (int j = 184, p = 0; j < 648; p++, j += 53)
        {
            if (plants[k][p])
            {
                DrawRectangle(i, j, 5, 11, Color{50, 100, 50, 255});
                DrawRectangle(i, j, 5, 5, GREEN);
            }
        }
    }

    DrawText("Manage Plants", 350, 385, 18, WHITE);
    DrawRectangleRec(manageToggle, Color{255, 255, 255, 100});

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

void StoreScene::renderModal(int width, int height)
{
    if (!showModal)
        return;

    Inventory *storageInventory = backendStore->getStorage();
    if (!storageInventory)
        return;

    Rectangle modal = {461, 356, 485, 535};
    DrawRectangleRec(modal, Color{178, 102, 0, 255});
    DrawRectangleLinesEx(modal, 1, BLACK);

    DrawText("Storage:", 466, 361, 35, Color{86, 49, 0, 255});

    for (const Slot &slot : storageSlots)
    {
        if (slot.selected)
        {
            DrawRectangleRec(slot.rect, Color{110, 70, 20, 255});
        }
        else
        {
            DrawRectangleRec(slot.rect, Color{86, 49, 0, 255});
        }

        DrawRectangleLinesEx(slot.rect, 2, BLACK);

        if (slot.slot != nullptr && !slot.slot->isEmpty())
        {
            DrawCircle(slot.rect.x + 37, slot.rect.y + 37, 20, GREEN);

            std::string quantity = std::to_string(slot.slot->getSize());
            DrawText(quantity.c_str(), slot.rect.x + 5, slot.rect.y + 5, 10, WHITE);
        }
    }
}

string StoreScene::getType()
{
    return "Store";
}