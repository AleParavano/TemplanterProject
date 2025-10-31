#include "Player.h"
#include <chrono>
#include <cstdio>
#include <iostream>

bool Player::safe = true;

Player::Player()
    : inventory(nullptr), workers(nullptr), plot(nullptr),
      money(1000.0f), rating(0),
      day(1), hour(6), minute(0)
{
    inventory = new Inventory(15);
    workers = new Worker();
    plot = new Greenhouse();
}

Player::~Player()
{
    if (inventory)
    {
        delete inventory;
    }
    if (workers)
    {
        delete workers;
    }
    if (plot)
    {
        delete plot;
    }
}

Inventory *Player::getInventory() const
{
    return inventory;
}

Worker *Player::getWorkers() const
{
    return workers;
}

Greenhouse *Player::getPlot() const
{
    return plot;
}

float Player::getMoney() const
{
    return money;
}

int Player::getRating() const
{
    return rating;
}

int Player::getDay() const
{
    return day;
}

int Player::getHour() const
{
    return hour;
}

int Player::getMinute() const
{
    return minute;
}

std::string Player::getTimeString() const
{
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);

    return std::string(buffer);
}

std::string Player::getFullTimeString() const
{
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Day %d, %02d:%02d", day, hour, minute);

    return std::string(buffer);
}

void Player::setInventory(Inventory *inv)
{
    if (inventory != inv)
    {
        if (inventory)
        {
            delete inventory;
        }
        inventory = inv;
    }
}

void Player::setWorkers(Worker *w)
{
    if (workers != w)
    {
        if (workers)
        {
            delete workers;
        }
        workers = w;
    }
}

void Player::setPlot(Greenhouse *gh)
{
    if (plot != gh)
    {
        if (plot)
        {
            delete plot;
        }
        plot = gh;
    }
}

void Player::setMoney(float m)
{
    money = m;
}

void Player::setRating(int r)
{
    rating = r;
}

void Player::setDay(int d)
{
    if (d > 0)
    {
        day = d;
    }
}

void Player::setHour(int h)
{
    if (h >= 0 && h < 24)
    {
        hour = h;
    }
}

void Player::setMinute(int m)
{
    if (m >= 0 && m < 60)
    {
        minute = m;
    }
}

bool Player::isNewDay() const
{
    return hour == 6 && minute == 0;
}

void Player::setProtected(bool prot)
{
    safe = prot;
}

bool Player::isProtected()
{
    return safe;
}

Memento *Player::createMemento() const
{
    return new Memento(inventory, workers, plot, money, rating, day, hour, minute);
}

void Player::setMemento(Memento *memento)
{
    if (memento)
    {
        money = memento->getMoney();
        rating = memento->getRating();
        day = memento->getDay();
        hour = memento->getHour();
        minute = memento->getMinute();

        if (inventory)
        {
            delete inventory;
        }
        if (workers)
        {
            delete workers;
        }
        if (plot)
        {
            delete plot;
        }

        inventory = memento->getInventory() ? new Inventory(*memento->getInventory()) : nullptr;
        workers = memento->getWorkers() ? new Worker(*memento->getWorkers()) : nullptr;
        plot = memento->getPlot() ? new Greenhouse(*memento->getPlot()) : nullptr;
    }
}

void Player::openInventory()
{
    inventoryOpen = !inventoryOpen;

    // Build the slot vector ONCE when opening
    if (inventoryOpen && slotVector.empty())
    {
        int invPos = 0;

        for (int i = 75; i < 326; i += 100)
        {
            for (int j = 466; j < 930; j += 100)
            {
                Rectangle tempRect = {j, i, 75, 75};

                const InventorySlot *slotData = nullptr;
                if (invPos < inventory->getMaxSlots())
                {
                    slotData = inventory->getSlot(invPos);
                }

                Slot tempSlot(slotData, tempRect);
                slotVector.push_back(tempSlot);
                invPos++;
            }
        }
    }

    // Clear slots when closing
    if (!inventoryOpen)
    {
        slotVector.clear();
        selectedSlotIndex = -1;
    }
}

void Player::renderInventory()
{
    if (inventoryOpen)
    {
        // DrawRectangle(0, 0, 1400, 900, Fade(BLACK, 0.5f));
        Rectangle inv = {461, 26, 485, 333};
        DrawRectangleRec(inv, Color{178, 102, 0, 255});
        DrawRectangleLinesEx(inv, 1, BLACK);

        DrawText("INVENTORY:", 466, 35, 35, Color{86, 49, 0, 255});

        for (int i = 0; i < slotVector.size(); i++)
        {
            const Slot &slot = slotVector[i];

            // Draw slot background
            if (slot.selected)
            {
                DrawRectangleRec(slot.rect, Color{110, 70, 20, 255});
            }
            else
            {
                DrawRectangleRec(slot.rect, Color{86, 49, 0, 255});
            }

            DrawRectangleLinesEx(slot.rect, 2, BLACK);

            // If slot has an item, draw it
            if (slot.slot != nullptr && !slot.slot->isEmpty())
            {
                DrawCircle(slot.rect.x + 37, slot.rect.y + 37, 20, GREEN);

                std::string quantity = std::to_string(slot.slot->getSize());
                DrawText(quantity.c_str(), slot.rect.x + 5, slot.rect.y + 5, 10, WHITE);
            }
        }
    }
}

// void Player::updateInventory(Inventory* storageInventory, int* selectedStorageSlot)
// {
//     if (!inventoryOpen)
//         return;

//     // Refresh slot data to reflect any changes
//     for(int i = 0; i < slotVector.size(); i++){
//         slotVector[i].slot = inventory->getSlot(i);
//     }

//     Vector2 mouse = GetMousePosition();

//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
//     {
//         for (int i = 0; i < slotVector.size(); i++)
//         {
//             if (slotVector[i].isClicked(mouse))
//             {
//                 // CASE 1: A storage slot is selected - swap between inventories
//                 if(storageInventory && selectedStorageSlot && *selectedStorageSlot != -1)
//                 {
//                     Inventory::swapBetweenInventories(storageInventory, *selectedStorageSlot, 
//                                                      inventory, i);
                    
//                     // Refresh player inventory display
//                     slotVector[i].slot = inventory->getSlot(i);
                    
//                     // Clear storage selection
//                     *selectedStorageSlot = -1;
//                 }
//                 // CASE 2: No slot selected - select this player slot
//                 else if(selectedSlotIndex == -1)
//                 {
//                     // Only select if slot has items
//                     if(slotVector[i].slot != nullptr && !slotVector[i].slot->isEmpty())
//                     {
//                         selectedSlotIndex = i;
//                         slotVector[i].selected = true;
//                     }
//                 }
//                 // CASE 3: Player slot already selected - swap within player inventory
//                 else if(selectedSlotIndex != i)
//                 {
//                     inventory->swapSlots(selectedSlotIndex, i);
                    
//                     // Refresh both affected slots
//                     slotVector[selectedSlotIndex].slot = inventory->getSlot(selectedSlotIndex);
//                     slotVector[i].slot = inventory->getSlot(i);
                    
//                     // Clear selection
//                     slotVector[selectedSlotIndex].selected = false;
//                     selectedSlotIndex = -1;
//                 }
//                 // CASE 4: Clicking same slot - deselect
//                 else 
//                 {
//                     slotVector[selectedSlotIndex].selected = false;
//                     selectedSlotIndex = -1;
//                 }

//                 break;
//             }
//         }
//     }

//     // Right-click to cancel selection
//     if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && selectedSlotIndex != -1)
//     {
//         slotVector[selectedSlotIndex].selected = false;
//         selectedSlotIndex = -1;
//     }
// }

void Player::updateInventory(Inventory* storageInventory, int* selectedStorageSlot)
{
    if (!inventoryOpen)
        return;

    // Refresh slot data to reflect any changes
    for(int i = 0; i < slotVector.size(); i++){
        slotVector[i].slot = inventory->getSlot(i);
    }

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < slotVector.size(); i++)
        {
            if (slotVector[i].isClicked(mouse))
            {
                // CASE 1: A storage slot is selected - transfer from storage to player
                if(storageInventory && selectedStorageSlot && *selectedStorageSlot != -1)
                {
                    const InventorySlot* storageSlot = storageInventory->getSlot(*selectedStorageSlot);
                    const InventorySlot* playerSlot = inventory->getSlot(i);
                    
                    // Check if we should merge stacks
                    bool shouldMerge = false;
                    if(storageSlot && playerSlot && 
                       !storageSlot->isEmpty() && !playerSlot->isEmpty() &&
                       storageSlot->getPlantType() == playerSlot->getPlantType() &&
                       !playerSlot->isFull())
                    {
                        shouldMerge = true;
                    }
                    
                    if(shouldMerge)
                    {
                        // Merge stacks: move items from storage to THIS specific player slot
                        std::string plantType = storageSlot->getPlantType();
                        int spaceAvailable = playerSlot->getRemainingCapacity();
                        int itemsInSource = storageSlot->getSize();
                        int itemsToMove = std::min(spaceAvailable, itemsInSource);
                        
                        // Remove items from storage and add directly to the destination slot
                        for(int j = 0; j < itemsToMove; j++)
                        {
                            Plant* plant = storageInventory->removeItem(plantType);
                            if(!plant) break;
                            
                            // Add directly to the specific slot
                            if(!inventory->addToSpecificSlot(plant, i))
                            {
                                // If add failed, put it back
                                storageInventory->add(plant);
                                break;
                            }
                        }
                    }
                    else
                    {
                        // Simple swap
                        Inventory::swapBetweenInventories(storageInventory, *selectedStorageSlot, 
                                                         inventory, i);
                    }
                    
                    // Refresh ALL slots after cross-inventory operation
                    for(int k = 0; k < slotVector.size(); k++){
                        slotVector[k].slot = inventory->getSlot(k);
                    }
                    
                    // Clear storage selection
                    *selectedStorageSlot = -1;
                }
                // CASE 2: A player slot is selected - swap/merge within player inventory
                else if(selectedSlotIndex != -1 && selectedSlotIndex != i)
                {
                    const InventorySlot* sourceSlot = inventory->getSlot(selectedSlotIndex);
                    const InventorySlot* destSlot = inventory->getSlot(i);
                    
                    // Check if we should merge
                    bool shouldMerge = false;
                    if(sourceSlot && destSlot && 
                       !sourceSlot->isEmpty() && !destSlot->isEmpty() &&
                       sourceSlot->getPlantType() == destSlot->getPlantType() &&
                       !destSlot->isFull())
                    {
                        shouldMerge = true;
                    }
                    
                    if(shouldMerge)
                    {
                        // Merge: move ALL items from source to dest (within same inventory)
                        std::string plantType = sourceSlot->getPlantType();
                        int spaceAvailable = destSlot->getRemainingCapacity();
                        int itemsInSource = sourceSlot->getSize();
                        int itemsToMove = std::min(spaceAvailable, itemsInSource);
                        
                        // Temporarily store items to move
                        std::vector<Plant*> plantsToMove;
                        for(int j = 0; j < itemsToMove; j++)
                        {
                            Plant* plant = inventory->removeItem(plantType);
                            if(plant) {
                                plantsToMove.push_back(plant);
                            }
                        }
                        
                        // Now add them back - they should go to the destination slot
                        for(Plant* plant : plantsToMove)
                        {
                            if(!inventory->add(plant))
                            {
                                // This shouldn't happen, but clean up if it does
                                delete plant;
                            }
                        }
                    }
                    else
                    {
                        // Simple swap within player inventory
                        inventory->swapSlots(selectedSlotIndex, i);
                    }
                    
                    // Refresh both affected slots
                    slotVector[selectedSlotIndex].slot = inventory->getSlot(selectedSlotIndex);
                    slotVector[i].slot = inventory->getSlot(i);
                    
                    // Clear selection
                    slotVector[selectedSlotIndex].selected = false;
                    selectedSlotIndex = -1;
                }
                // CASE 3: No slot selected - select this player slot
                else if(selectedSlotIndex == -1)
                {
                    // Only select if slot has items
                    if(slotVector[i].slot != nullptr && !slotVector[i].slot->isEmpty())
                    {
                        selectedSlotIndex = i;
                        slotVector[i].selected = true;
                    }
                }
                // CASE 4: Clicking same slot - deselect
                else 
                {
                    slotVector[selectedSlotIndex].selected = false;
                    selectedSlotIndex = -1;
                }

                break;
            }
        }
    }

    // Right-click to cancel selection
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && selectedSlotIndex != -1)
    {
        slotVector[selectedSlotIndex].selected = false;
        selectedSlotIndex = -1;
    }
}