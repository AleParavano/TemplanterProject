#ifndef SLOT_H
#define SLOT_H

#include "raylib.h"
#include "raymath.h"
#include <string>
#include "../Backend/Inventory.h" // Assumed to define the core InventorySlot structure

/**
 * @struct Slot
 * @brief Represents a single visual slot in the **InventoryUI**, linking the display area 
 * to the actual item data in the core game **Inventory**.
 *
 * This structure primarily handles visual representation and input checking (like clicking).
 */
struct Slot
{
    /** @brief A read-only pointer to the actual game data slot (the Model component). */
    const InventorySlot *slot;
    
    /** @brief The rectangular bounding box defining the slot's drawing area and click zone. */
    Rectangle rect;
    
    /** @brief Flag indicating if this slot is currently selected by the player for interaction. */
    bool selected = false;
    
    /** @brief String representation of the item quantity for display purposes. */
    std::string quantity;
    
    /**
     * @brief Constructor. Initializes the visual slot by linking it to the game data and defining its rectangle.
     * @param slotIn A pointer to the InventorySlot object containing item data (can be nullptr).
     * @param rectIn The screen coordinates and size of the slot.
     */
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
            // Set quantity to "0" or empty string if the slot is empty
            quantity = "0";
        }
    }

    /**
     * @brief Checks if a given mouse position is within the boundaries of this slot's rectangle.
     * @param mousePos The mouse coordinates to check.
     * @return true if the mouse is over the slot, false otherwise.
     */
    bool isClicked(Vector2 mousePos) const
    {
        return CheckCollisionPointRec(mousePos, rect);
    }
};

#endif