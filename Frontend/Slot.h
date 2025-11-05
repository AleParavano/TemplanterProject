#ifndef SLOT_H
#define SLOT_H

#include "raylib.h"
#include "raymath.h"
#include <string>
#include "../Backend/Inventory.h"

struct Slot
    {
        const InventorySlot *slot;
        Rectangle rect;
        bool selected = false;
        std::string quantity;
        // Image icon;

        Slot(const InventorySlot *slotIn, Rectangle rectIn)
        {
            slot = slotIn;
            rect = rectIn;

            if (slotIn != nullptr)
            {
                quantity = std::to_string(slotIn->getSize());
            }
            else
            {
                quantity = "0";
            }
        }

        bool isClicked(Vector2 mousePos) const
        {
            return CheckCollisionPointRec(mousePos, rect);
        }
    };

#endif