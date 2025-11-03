/**
 * @file Inventory.cpp
 * @brief Implementation of the Inventory and InventorySlot classes for managing plant storage.
 * 
 * This file implements a composite inventory system that groups similar plants into stacks.
 * The Inventory uses InventorySlot objects to organize plants by type, with each slot
 * capable of holding multiple plants of the same type up to a maximum capacity.
 * 
 * @pattern Composite - InventorySlot groups individual Plant objects
 * @pattern Iterator - Supports iteration over inventory slots and items
 */

#include "Inventory.h"

/**
 * @brief Adds a plant to the inventory slot.
 * 
 * Attempts to add a plant to this slot. If the slot is empty, it accepts any plant type
 * and stores that type for future compatibility checks. If the slot already contains plants,
 * it only accepts plants of the same type.
 * 
 * @param plant Pointer to the plant to add
 * @return true if the plant was successfully added
 * @return false if plant is null, slot is full, or plant type doesn't match
 */
bool InventorySlot::add(Plant *plant)
{
    if (!plant)
        return false;
    if (isFull())
        return false;

    // If empty slot, accept any plant type
    if (isEmpty())
    {
        plantType = plant->getType(); // Assuming Plant has getType() method
        items.push_back(plant);
        return true;
    }

    // If not empty, check type compatibility
    if (plant->getType() != plantType)
    {
        return false;
    }

    items.push_back(plant);
    return true;
}

/**
 * @brief Removes and returns the most recently added plant from the slot.
 * 
 * Implements LIFO (Last In, First Out) removal. If the slot becomes empty after
 * removal, the stored plant type is cleared to allow future plants of any type.
 * 
 * @return Plant* Pointer to the removed plant, or nullptr if slot is empty
 */
Plant *InventorySlot::remove()
{
    if (isEmpty())
        return nullptr;

    Plant *plant = items.back();
    items.pop_back();

    // Clear plant type if slot becomes empty
    if (isEmpty())
    {
        plantType.clear();
    }

    return plant;
}

/**
 * @brief Checks if a plant can be added to this slot.
 * 
 * A plant can be accepted if: the plant pointer is valid, the slot is not full,
 * and either the slot is empty or the plant type matches the slot's stored type.
 * 
 * @param plant Pointer to the plant to check
 * @return true if the plant can be added to this slot
 * @return false otherwise
 */
bool InventorySlot::canAccept(Plant *plant) const
{
    if (!plant)
        return false;
    if (isFull())
        return false;
    if (isEmpty())
        return true;
    return plant->getType() == plantType;
}

/**
 * @brief Constructs an Inventory with the specified capacity.
 * 
 * Initializes the inventory with a maximum number of slots. All slots are
 * initially set to nullptr, representing empty slots available for use.
 * 
 * @param capacity Maximum number of inventory slots
 */
Inventory::Inventory(int capacity) : maxSlots(capacity)
{
    slots.resize(maxSlots);
    for (int i = 0; i < maxSlots; i++)
    {
        slots[i] = nullptr;
    }
}

/**
 * @brief Destructor that cleans up all inventory slots and their contents.
 * 
 * Deletes all plants stored in all slots and deallocates the slot objects themselves.
 */
Inventory::~Inventory()
{
    clear();
}

/**
 * @brief Adds a plant to the inventory.
 * 
 * Attempts to find an existing compatible slot for the plant. If found, adds to that slot.
 * If no compatible slot exists, creates a new slot if space is available.
 * 
 * @param plant Pointer to the plant to add
 * @return true if plant was successfully added to inventory
 * @return false if plant is null or inventory has no available space
 * 
 * @note Uses the Composite pattern to group similar plants
 */
bool Inventory::add(Plant *plant)
{    
    if (!plant) {
        return false;
    }


    // Try to find existing compatible slot
    InventorySlot *slot = findCompatibleSlot(plant);

    if (slot)
    {
        return slot->add(plant);
    }
    
    // Create new slot (removes the bad check!)
    slot = createNewSlot();
    if (!slot) {
        return false;
    }

    return slot->add(plant);
}

/**
 * @brief Removes one plant of the specified type from inventory.
 * 
 * Searches for the first slot containing the specified plant type and removes
 * one plant from it. If the slot becomes empty after removal, the slot is
 * deleted and removed from the inventory.
 * 
 * @param plantType The type of plant to remove (e.g., "Lettuce", "Tomato")
 * @return Plant* Pointer to the removed plant, or nullptr if type not found
 */
Plant *Inventory::removeItem(const std::string &plantType)
{
    // Find first slot with this plant type
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
        InventorySlot *slot = *it;
        if (slot->getPlantType() == plantType)
        {
            Plant *plant = slot->remove();

            if (slot->isEmpty())
            {
                slots.erase(it);
                delete slot;
            }

            return plant;
        }
    }
    return nullptr;
}

/**
 * @brief Removes an entire stack (slot) from inventory at the specified index.
 * 
 * Deletes all plants in the slot and removes the slot from inventory.
 * This operation cannot be undone.
 * 
 * @param index The index of the stack to remove
 * @return true if stack was successfully removed
 * @return false if index is out of bounds
 */
bool Inventory::removeStack(size_t index)
{
    if (index >= slots.size())
        return false;

    InventorySlot *slot = slots[index];

    while (!slot->isEmpty())
    {
        Plant *plant = slot->remove();
        delete plant;
    }

    slots.erase(slots.begin() + index);
    delete slot;

    return true;
}

/**
 * @brief Counts the total number of plants of a specific type in inventory.
 * 
 * Iterates through all slots and sums up the count of plants matching
 * the specified type.
 * 
 * @param plantType The type of plant to count (e.g., "Lettuce", "Tomato")
 * @return int Total count of plants of the specified type
 */
int Inventory::getPlantCount(const std::string &plantType) const
{
    int count = 0;
    for (const auto *slot : slots)
    {
        if (slot != nullptr && slot->getPlantType() == plantType) 
        {
            count += slot->getSize();
        }
    }
    return count;
}

/**
 * @brief Checks if the inventory is completely full.
 * 
 * The inventory is considered full when the number of non-null slots
 * reaches maxSlots and all slots are at capacity.
 * 
 * @return true if inventory is full and cannot accept more items
 * @return false if there is space available
 */
bool Inventory::isFull() const
{
 int filledSlots = 0;
    for (const auto *slot : slots)
    {
        if (slot != nullptr)  
        {
            filledSlots++;
            if (!slot->isFull())
                return false;
        }
    }
    return filledSlots >= maxSlots;
}

/**
 * @brief Retrieves a read-only pointer to the slot at the specified index.
 * 
 * @param index The index of the slot to retrieve
 * @return const InventorySlot* Pointer to the slot, or nullptr if index is invalid
 */
const InventorySlot *Inventory::getSlot(size_t index) const
{
    if (index >= slots.size())
        return nullptr;
    return slots[index];
}

/**
 * @brief Clears the entire inventory, deleting all plants and slots.
 * 
 * Iterates through all slots, deletes all contained plants, and then
 * deletes the slot objects themselves. Finally, clears the slots vector.
 */
void Inventory::clear()
{
    for (auto *slot : slots)
    {
        if (slot != nullptr)  
        {
            while (!slot->isEmpty())
            {
                Plant *plant = slot->remove();
                delete plant;
            }
            delete slot;
        }
    }
    slots.clear();
}

/**
 * @brief Finds the first slot that can accept the given plant.
 * 
 * Searches through existing slots for one that matches the plant's type
 * and has remaining capacity.
 * 
 * @param plant Pointer to the plant to find a compatible slot for
 * @return InventorySlot* Pointer to compatible slot, or nullptr if none found
 * 
 * @note This is a private helper method for the add() function
 */
InventorySlot *Inventory::findCompatibleSlot(Plant *plant)
{
    for (auto *slot : slots)
    {
        // Skip nullptr slots!
        if (slot != nullptr && slot->canAccept(plant))
        {
            return slot;
        }
    }
    return nullptr;
}

/**
 * @brief Creates a new inventory slot in the first available empty position.
 * 
 * Searches for the first nullptr slot in the slots vector, allocates
 * a new InventorySlot object there, and returns a pointer to it.
 * 
 * @return InventorySlot* Pointer to the newly created slot, or nullptr if no space
 * @note This is a private helper method for the add() function
 */
InventorySlot *Inventory::createNewSlot()
{
    // Find first nullptr slot
    for (int i = 0; i < slots.size(); i++)
    {
        if (slots[i] == nullptr)
        {
            slots[i] = new InventorySlot();
            return slots[i];
        }
    }

    return nullptr; // No empty slots
}

/**
 * @brief Swaps two inventory slots within the same inventory.
 * 
 * Exchanges the positions of two slots. This is useful for inventory
 * management and reorganization in the user interface.
 * 
 * @param index1 Index of the first slot to swap
 * @param index2 Index of the second slot to swap
 * 
 * @note Does nothing if either index is out of bounds
 */
void Inventory::swapSlots(int index1, int index2)
{
    if (index1 < 0 || index1 >= maxSlots || index2 < 0 || index2 >= maxSlots)
    {
        return;
    }

    InventorySlot *temp = slots[index1];
    slots[index1] = slots[index2];
    slots[index2] = temp;
}

/**
 * @brief Swaps slots between two different inventory objects.
 * 
 * This static method enables trading or transferring entire stacks between
 * different inventories (e.g., player inventory and storage).
 * 
 * @param inv1 Pointer to the first inventory
 * @param index1 Index of the slot in the first inventory
 * @param inv2 Pointer to the second inventory
 * @param index2 Index of the slot in the second inventory
 * 
 * @note Does nothing if inventories are null or indices are out of bounds
 */
void Inventory::swapBetweenInventories(Inventory* inv1, int index1, Inventory* inv2, int index2)
{
    if (!inv1 || !inv2) return;
    if (index1 < 0 || index1 >= inv1->maxSlots) return;
    if (index2 < 0 || index2 >= inv2->maxSlots) return;

    // Simple pointer swap
    InventorySlot* temp = inv1->slots[index1];
    inv1->slots[index1] = inv2->slots[index2];
    inv2->slots[index2] = temp;
}

/**
 * @brief Adds a plant to a specific inventory slot by index.
 * 
 * Attempts to add a plant to the slot at the specified index. If the slot doesn't exist,
 * creates a new slot at that position. The slot must be compatible with the plant type.
 * 
 * @param plant Pointer to the plant to add
 * @param slotIndex Index of the target slot
 * @return true if plant was successfully added to the specified slot
 * @return false if plant is null, index is out of bounds, or slot cannot accept the plant
 */
bool Inventory::addToSpecificSlot(Plant* plant, size_t slotIndex)
{
    if (!plant) return false;
    if (slotIndex >= slots.size()) return false;
    
    InventorySlot* slot = slots[slotIndex];
    
    // If slot doesn't exist, create it
    if (slot == nullptr) {
        slot = new InventorySlot();
        slots[slotIndex] = slot;
    }
    
    // Try to add to this specific slot
    return slot->add(plant);
}