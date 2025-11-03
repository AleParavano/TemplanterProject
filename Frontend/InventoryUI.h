#pragma once
#include "raylib.h"
#include <vector>
#include "../Backend/Inventory.h"
#include "Slot.h"

class InventoryUI
{
private:
    Inventory* inventory;
    bool isOpen;
    std::vector<Slot> slotVector;
    int selectedSlotIndex;
<<<<<<< HEAD
=======
    float timeSinceLastUpdate;
>>>>>>> origin/Frontend

public:
    InventoryUI(Inventory* inv);
    InventoryUI(){};
    ~InventoryUI() = default;

    // Toggle inventory open/close
    void toggle();
    
    // Rendering
    void render();
    
    // Update logic (handles mouse input, slot selection, swapping, merging)
    void update();
    
    // Getters
    bool isInventoryOpen() const { return isOpen; }
    int getSelectedSlotIndex() const { return selectedSlotIndex; }
    
    // Selection management
    void clearSlotSelection();
    
    // For cross-inventory interactions (e.g., with customer/shop)
    const Slot* getSlot(int index) const;
    std::vector<Slot>& getSlots() { return slotVector; }
};