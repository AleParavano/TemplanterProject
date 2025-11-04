#pragma once
#include "raylib.h"
#include <vector>
#include "../Backend/Inventory.h" // Assumed to define the core Inventory data structure
#include "Slot.h"                  // Assumed to define the visual Slot structure

/**
 * @class InventoryUI
 * @brief Manages the visual representation, rendering, and user interaction logic for the player's inventory.
 *
 * This class acts as the **View/Controller** component for the Inventory **Model**, handling mouse input 
 * for slot selection, item swapping, and rendering the UI elements.
 */
class InventoryUI
{
private:
    /** @brief Pointer to the core game Inventory data structure (the Model). */
    Inventory* inventory;
    
    /** @brief Flag indicating whether the inventory window is currently displayed. */
    bool isOpen;
    
    /** @brief A collection of visual Slot objects, representing the individual inventory cells. */
    std::vector<Slot> slotVector;
    
    /** @brief The index of the currently selected slot, or -1 if none is selected. */
    int selectedSlotIndex;
    
    /** @brief Timer to manage input debounce or animation timing. */
    float timeSinceLastUpdate;

public:
    /**
     * @brief Constructor for InventoryUI when linked to an existing Inventory model.
     * @param inv A pointer to the Inventory object this UI will manage.
     */
    InventoryUI(Inventory* inv);
    
    /**
     * @brief Default constructor (potentially for delayed initialization).
     */
    InventoryUI(){};
    
    /**
     * @brief Default destructor. Resources are generally managed by raylib or other systems.
     */
    ~InventoryUI() = default;

    /**
     * @brief Toggles the visibility state of the inventory window.
     */
    void toggle();
    
    /**
     * @brief Renders the inventory window, slots, and items to the screen.
     */
    void render();
    
    /**
     * @brief Updates the inventory UI state, processing mouse input, slot selection, and handling item manipulation.
     */
    void update();
    
    // Getters
    /**
     * @brief Checks if the inventory window is currently open.
     * @return true if open, false otherwise.
     */
    bool isInventoryOpen() const { return isOpen; }
    
    /**
     * @brief Gets the index of the slot that is currently selected by the user.
     * @return The zero-based index of the selected slot, or -1.
     */
    int getSelectedSlotIndex() const { return selectedSlotIndex; }
    
    // Selection management
    /**
     * @brief Resets the currently selected slot index to an unselected state.
     */
    void clearSlotSelection();
    
    // For cross-inventory interactions (e.g., with customer/shop)
    /**
     * @brief Retrieves a read-only pointer to a specific slot object.
     * @param index The index of the slot to retrieve.
     * @return A const pointer to the Slot, or nullptr if the index is out of bounds.
     */
    const Slot* getSlot(int index) const;
    
    /**
     * @brief Provides access to the vector of all visual Slot objects.
     * @return A reference to the mutable vector of Slots.
     */
    std::vector<Slot>& getSlots() { return slotVector; }
};