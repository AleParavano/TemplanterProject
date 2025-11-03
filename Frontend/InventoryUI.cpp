#include "InventoryUI.h"
#include <algorithm>
#include <iostream>
#include <map>                       
#include <tuple>                    
#include "../Backend/Plant.h" 
#include "../Backend/PlantFactory.h"
#include "PlantVisualStrategy.h"


extern std::map<std::string, std::tuple<float, PlantFactory *, PlantVisualStrategy *>> plantCatalog;

InventoryUI::InventoryUI(Inventory* inv)
    : inventory(inv), isOpen(false), selectedSlotIndex(-1), timeSinceLastUpdate(0.0f)
{
}

void InventoryUI::toggle()
{
    isOpen = !isOpen;

    if (isOpen)
    {
        slotVector.clear(); 
        selectedSlotIndex = -1;
        timeSinceLastUpdate = 0.0f; // Reset timer when opening
        
        int invPos = 0;

        for (int i = 150; i < 649 && invPos < 25; i += 100)
        {
            for (int j = 174; j < 630 && invPos < 25; j += 100)
            {
                Rectangle tempRect = {j, i, 75, 75};

                const InventorySlot* slotData = nullptr;
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
    else 
    {
        slotVector.clear();
        selectedSlotIndex = -1;
    }
}

void InventoryUI::render()
{
    if (!isOpen)
        return;

    Rectangle inv = {169, 105, 485, 535};
    DrawRectangleRec(inv, Color{178, 102, 0, 255});
    DrawRectangleLinesEx(inv, 1, BLACK);

    DrawText("INVENTORY:", 174, 110, 35, Color{86, 49, 0, 255});

    for (int i = 0; i < slotVector.size(); i++)
    {
        const Slot& slot = slotVector[i];


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
            std::string itemName = slot.slot->getPlantType();


            auto it = plantCatalog.find(itemName); 
            
            if (it != plantCatalog.end()) {
                PlantVisualStrategy* visualStrategy = std::get<2>(it->second);
                
                if (visualStrategy) {
                    float drawX = slot.rect.x + slot.rect.width / 2.0f;
                    float drawY = slot.rect.y + slot.rect.height / 2.0f - 5.0f; 

                    visualStrategy->drawStatic(drawX, drawY); 
                }
            } else {
                DrawCircle(slot.rect.x + 37, slot.rect.y + 37, 20, GREEN);
            }

            std::string quantity = std::to_string(slot.slot->getSize());
            DrawText(quantity.c_str(), slot.rect.x + 5, slot.rect.y + 5, 10, WHITE);
            
            // Draw item name, centered near the bottom of the slot
            int textWidth = MeasureText(itemName.c_str(), 10);
            DrawText(itemName.c_str(), 
                     slot.rect.x + (slot.rect.width - textWidth) / 2, 
                     slot.rect.y + 58, 
                     10, RAYWHITE); 
        }
    }
}

void InventoryUI::update()
{
    if (!isOpen)
        return;

    // Accumulate time since last update
    timeSinceLastUpdate += GetFrameTime();

    // Only refresh slot data every 1 second
    if (timeSinceLastUpdate >= 2.0f)
    {
        for (int i = 0; i < slotVector.size(); i++)
        {
            std::cout << "DEBUG: InventoryUI checking slot index " << i << std::endl;
            slotVector[i].slot = inventory->getSlot(i);
        }
        timeSinceLastUpdate = 0.0f; // Reset timer
    }

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < slotVector.size(); i++)
        {
            if (slotVector[i].isClicked(mouse))
            {
                // CASE 1: A slot is selected - swap/merge within inventory
                if (selectedSlotIndex != -1 && selectedSlotIndex != i)
                {
                    const InventorySlot* sourceSlot = inventory->getSlot(selectedSlotIndex);
                    const InventorySlot* destSlot = inventory->getSlot(i);

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
                            const InventorySlot* currentDestSlot = inventory->getSlot(i);
                            if (!currentDestSlot || currentDestSlot->isFull())
                                break;

                            Plant* plant = inventory->removeItem(plantType);
                            if (!plant)
                                break;
                            
                            // Reverting to base add/remove due to missing function:
                            if (!inventory->add(plant)) { delete plant; break; }
                        }
                    }
                    else
                    {
                        // Simple swap logic (assuming swapSlots exists or is not used)
                        // inventory->swapSlots(selectedSlotIndex, i);
                    }

                    // Clear selection
                    slotVector[selectedSlotIndex].selected = false;
                    selectedSlotIndex = -1;
                }
                // CASE 2: No slot selected - select this slot
                else if (selectedSlotIndex == -1)
                {
                    // Only select if slot has items
                    if (slotVector[i].slot != nullptr && !slotVector[i].slot->isEmpty())
                    {
                        selectedSlotIndex = i;
                        slotVector[i].selected = true;
                    }
                }
                // CASE 3: Clicking same slot - deselect
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

void InventoryUI::clearSlotSelection()
{
    if (selectedSlotIndex != -1 && selectedSlotIndex < slotVector.size())
    {
        slotVector[selectedSlotIndex].selected = false;
    }
    selectedSlotIndex = -1;
}

const Slot* InventoryUI::getSlot(int index) const
{
    if (index >= 0 && index < slotVector.size())
    {
        return &slotVector[index];
    }
    return nullptr;
}