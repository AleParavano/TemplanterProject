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
}

StoreScene::~StoreScene()
{
    delete backendStore;
}

void StoreScene::update(Player *player)
{
    Inventory *storageInventory = backendStore->getStorage();
    if (!storageInventory)
        return;

    Vector2 mouse = GetMousePosition();

    if (CheckCollisionPointRec(mouse, manageToggle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        showModal = !showModal; // Toggle storage modal

        // Open/close player inventory along with storage
        if (player)
        {
            if (showModal)
            {
                // Opening storage - ensure player inventory is also open
                if (!player->isInventoryOpen())
                {
                    player->openInventory();
                }
            }
            else
            {
                // Closing storage - also close player inventory
                if (player->isInventoryOpen())
                {
                    player->openInventory(); // This toggles it closed
                }
            }
        }

        // Build storage slots when opening
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

        // Also close player inventory when ESC is pressed
        if (player && player->isInventoryOpen())
        {
            player->openInventory();
        }
    }

    if (CheckCollisionPointRec(mouse, openNClose) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        toggleOpen();
    }
}

void StoreScene::updateStorage(Player *player)
{
    if (!player)
        return;

    Inventory *storageInventory = backendStore->getStorage();
    if (!storageInventory)
        return;

    // Refresh slot pointers to reflect inventory changes
    for (int i = 0; i < storageSlots.size(); i++)
    {
        storageSlots[i].slot = storageInventory->getSlot(i);

        // Update selection visual
        storageSlots[i].selected = (i == selectedStorageSlot);
    }

    Vector2 mouse = GetMousePosition();

    // Handle storage slot clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        bool clickHandled = false;

        // First check if player has a selection - this enables player->storage transfer
        if (player->getSelectedSlotIndex() != -1)
        {
            int playerSlotIndex = player->getSelectedSlotIndex();

            for (int i = 0; i < storageSlots.size(); i++)
            {
                if (storageSlots[i].isClicked(mouse))
                {
                    const InventorySlot *playerSlot = player->getInventory()->getSlot(playerSlotIndex);
                    const InventorySlot *storageSlot = storageInventory->getSlot(i);

                    // Check if we should merge stacks
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
                        // Merge: move items from player to THIS specific storage slot
                        std::string plantType = playerSlot->getPlantType();
                        int spaceAvailable = storageSlot->getRemainingCapacity();
                        int itemsInSource = playerSlot->getSize();
                        int itemsToMove = std::min(spaceAvailable, itemsInSource);

                        // Remove items from player and add to specific storage slot
                        for (int j = 0; j < itemsToMove; j++)
                        {
                            // Re-check destination validity
                            const InventorySlot *currentStorageSlot = storageInventory->getSlot(i);
                            if (!currentStorageSlot || currentStorageSlot->isFull())
                                break;

                            Plant *plant = player->getInventory()->removeItem(plantType);
                            if (!plant)
                                break;

                            if (!storageInventory->addToSpecificSlot(plant, i))
                            {
                                // If add failed, put it back in player inventory
                                player->getInventory()->add(plant);
                                break;
                            }
                        }
                    }
                    else
                    {
                        // Simple swap between player and storage
                        Inventory::swapBetweenInventories(player->getInventory(), playerSlotIndex,
                                                          storageInventory, i);
                    }

                    // Refresh ALL storage slots after cross-inventory operation
                    for (int k = 0; k < storageSlots.size(); k++)
                    {
                        storageSlots[k].slot = storageInventory->getSlot(k);
                    }

                    // Clear player selection
                    player->clearSlotSelection();

                    clickHandled = true;
                    break;
                }
            }
        }

        // If no player selection or click wasn't handled, handle storage-only clicks
        if (!clickHandled)
        {
            for (int i = 0; i < storageSlots.size(); i++)
            {
                if (storageSlots[i].isClicked(mouse))
                {
                    // CASE 1: No storage slot selected - select this one
                    if (selectedStorageSlot == -1)
                    {
                        // Only select if slot has items
                        if (storageSlots[i].slot != nullptr && !storageSlots[i].slot->isEmpty())
                        {
                            selectedStorageSlot = i;
                            storageSlots[i].selected = true;
                        }
                    }
                    // CASE 2: Different storage slot already selected - swap/merge within storage
                    else if (selectedStorageSlot != i)
                    {
                        const InventorySlot *sourceSlot = storageInventory->getSlot(selectedStorageSlot);
                        const InventorySlot *destSlot = storageInventory->getSlot(i);

                        // Check if we should merge
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
                            // Merge stacks within storage
                            std::string plantType = sourceSlot->getPlantType();
                            int spaceAvailable = destSlot->getRemainingCapacity();
                            int itemsInSource = sourceSlot->getSize();
                            int itemsToMove = std::min(spaceAvailable, itemsInSource);

                            // Remove and add directly to destination
                            for (int j = 0; j < itemsToMove; j++)
                            {
                                // Re-check destination validity
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
                            // Simple swap within storage
                            storageInventory->swapSlots(selectedStorageSlot, i);
                        }

                        // Refresh both slots
                        storageSlots[selectedStorageSlot].slot = storageInventory->getSlot(selectedStorageSlot);
                        storageSlots[i].slot = storageInventory->getSlot(i);

                        // Clear selection
                        storageSlots[selectedStorageSlot].selected = false;
                        selectedStorageSlot = -1;
                    }
                    // CASE 3: Same slot clicked - deselect
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

    // Right-click to cancel selection
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

    // Draw storage slots
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

// void StoreScene::manageCustomerQ(){
//     if(storeOpen && customerQueue.size() <= 5){
//         Plant* tempPlant = rngPlant.produce();
//         Customer* newCust = rngFact.create(tempPlant);
//         customerQueue.back(newCust);
//     }
// }