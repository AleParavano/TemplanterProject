/**
 * @file Inventory.h
 * @brief Inventory system for managing harvested plants in grouped slots.
 * @details Provides a flexible inventory system where plants can be stored in stacks
 *          grouped by type. Implements slot-based storage with type compatibility checking.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 */

#pragma once
#include <vector>
#include "Plant.h"

/**
 * @class InventorySlot
 * @brief A single inventory slot that can hold multiple plants of the same type.
 * 
 * InventorySlot manages a stack of plants, ensuring type compatibility within a slot.
 * Each slot has:
 * - Fixed capacity (64 plants per slot)
 * - Type restriction (only one plant type per slot)
 * - A vector of plant pointers
 * 
 * @par Thread Safety
 * This class is not thread-safe. External synchronization is required for concurrent access.
 * 
 * @example
 * @code
 * InventorySlot slot;
 * slot.add(tomato1);  // First plant sets the type
 * slot.add(tomato2);  // Compatible - same type
 * // slot.add(carrot); // Would return false - wrong type
 * @endcode
 */
class InventorySlot
{
public:
    /**
     * @brief Default constructor.
     * @details Creates an empty slot with no plant type set.
     */
    InventorySlot() = default;

    /**
     * @brief Adds a plant to this slot.
     * @param plant Pointer to the Plant to add.
     * @return true if successfully added, false if:
     *         - plant is nullptr
     *         - Slot is full
     *         - Plant type doesn't match slot type (and slot is not empty)
     * 
     * @pre plant must be a valid plant object
     * @post If successful, plant is added and type is set if empty
     */
    bool add(Plant *plant);

    /**
     * @brief Removes and returns the last plant from this slot.
     * @return Pointer to the removed Plant, or nullptr if the slot is empty.
     * 
     * @post If successful, the plant is removed from the slot
     * @post Plant type is cleared if slot becomes empty
     */
    Plant *remove();

    /**
     * @brief Checks if a plant can be added to this slot.
     * @param plant Pointer to the Plant to check.
     * @return true if the plant can be added without violating slot constraints, false otherwise.
     * 
     * @details A plant can be added if:
     *         - plant is not nullptr
     *         - Slot is not full
     *         - Slot is empty OR plant type matches the slot type
     */
    bool canAccept(Plant *plant) const;

    /**
     * @brief Checks if the slot is at maximum capacity.
     * @return true if the slot contains 64 plants, false otherwise.
     */
    bool isFull() const { return items.size() >= capacity; }

    /**
     * @brief Checks if the slot is empty.
     * @return true if no plants are in the slot, false otherwise.
     */
    bool isEmpty() const { return items.empty(); }

    /**
     * @brief Gets the number of plants in this slot.
     * @return Count of plants currently stored.
     */
    int getSize() const { return items.size(); }

    /**
     * @brief Gets the plant type stored in this slot.
     * @return String representing the plant type (e.g., "Tomato"), or empty string if empty.
     */
    std::string getPlantType() const { return plantType; }

    /**
     * @brief Gets the remaining capacity of this slot.
     * @return Number of plants that can still be added (capacity - size).
     */
    int getRemainingCapacity() const { return capacity - items.size(); }

    /**
     * @brief Gets a plant at a specific index in the slot.
     * @param index Position in the slot (0 to size-1).
     * @return Pointer to the plant at the index, or nullptr if index is out of bounds.
     */
    Plant* getPlant(int index) const 
    {
        if (index >= 0 && index < (int)items.size()) { return items[index]; }
        return nullptr;
    }
    
private:
    static constexpr int capacity = 64;     ///< Maximum plants per slot
    std::string plantType;                  ///< Type of plants stored in this slot
    std::vector<Plant *> items;             ///< Vector of plant pointers
};

/**
 * @class Inventory
 * @brief Main inventory system managing multiple slots.
 * 
 * The Inventory class provides a flexible storage system for harvested plants.
 * It dynamically creates slots as needed and manages type compatibility across slots.
 * 
 * @par Design Pattern: Iterator
 * Provides iteration over inventory slots for efficient traversal.
 * 
 * @par Thread Safety
 * This class is not thread-safe. External synchronization is required for concurrent access.
 * 
 * @example
 * @code
 * Inventory inv(10);  // Max 10 slots
 * 
 * inv.add(tomato1);
 * inv.add(tomato2);
 * inv.add(carrot1);   // Creates new slot
 * 
 * int count = inv.getPlantCount("Tomato");  // Returns 2
 * @endcode
 * 
 * @see InventorySlot
 */
class Inventory
{
public:
    /**
     * @brief Constructor with capacity specification.
     * @param capacity Maximum number of slots in the inventory.
     * 
     * @pre capacity should be positive
     */
    Inventory(int capacity);

    /**
     * @brief Destructor.
     * @details Cleans up all slots and plants. Calls clear().
     */
    ~Inventory();

    /**
     * @brief Adds a plant to the inventory.
     * @param plant Pointer to the Plant to add.
     * @return true if successfully added, false if:
     *         - plant is nullptr
     *         - Inventory is full (all slots full)
     * 
     * @details Automatically finds a compatible slot or creates a new one.
     * @post If successful, plant is stored in an inventory slot
     */
    bool add(Plant *plant);

    /**
     * @brief Removes a plant of a specific type from inventory.
     * @param plantType String identifying the plant type (e.g., "Tomato").
     * @return Pointer to the removed plant, or nullptr if not found.
     * 
     * @details Finds the first slot containing the plant type and removes one plant.
     *          If the slot becomes empty, it is deleted.
     */
    Plant *removeItem(const std::string &plantType);

    /**
     * @brief Removes an entire slot stack.
     * @param index The slot index (0 to getStackCount()-1).
     * @return true if successfully removed, false if index is out of bounds.
     * 
     * @details Deletes all plants in the slot and removes the slot from inventory.
     * @post If successful, the slot is deleted and inventory size decreases
     */
    bool removeStack(size_t index);

    /**
     * @brief Gets the total count of plants of a specific type.
     * @param plantType String identifying the plant type.
     * @return Number of plants of that type across all slots.
     */
    int getPlantCount(const std::string &plantType) const;

    /**
     * @brief Gets the number of occupied slots.
     * @return Count of non-empty slots in inventory.
     */
    size_t getStackCount() const { return slots.size(); }

    /**
     * @brief Checks if the inventory is completely full.
     * @return true if all slots are created and full, false if space remains.
     */
    bool isFull() const;

    /**
     * @brief Gets a specific inventory slot by index.
     * @param index The slot index (0 to getStackCount()-1).
     * @return Const pointer to the InventorySlot, or nullptr if out of bounds.
     */
    const InventorySlot *getSlot(size_t index) const;

    /**
     * @brief Clears the entire inventory.
     * @details Deletes all plants and slots, freeing all memory.
     * 
     * @post Inventory is empty and can accept new plants
     */
    void clear();

    /**
     * @brief Gets the maximum number of slots.
     * @return The capacity specified in the constructor.
     */
    size_t getMaxSlots() const { return maxSlots; }

    /**
     * @brief Changes the maximum number of slots.
     * @param capacity New maximum slot capacity.
     * 
     * @warning Be careful when reducing capacity - existing slots beyond new capacity are not handled.
     */
    void setMaxSlots(size_t capacity) { maxSlots = capacity; }

    /**
     * @brief Swaps the contents of two slots within this inventory.
     * @param index1 First slot index.
     * @param index2 Second slot index.
     * 
     * @pre Both indices must be valid and within bounds
     * @post Contents of the two slots are swapped
     */
    void swapSlots(int index1, int index2);
    
    /**
     * @brief Swaps inventory slots between two different inventories.
     * @param inv1 First Inventory object.
     * @param index1 Slot index in first inventory.
     * @param inv2 Second Inventory object.
     * @param index2 Slot index in second inventory.
     * 
     * @pre Both inventories must not be nullptr
     * @pre Both indices must be valid within their respective inventories
     * @post Slots are swapped between the two inventories
     */
    static void swapBetweenInventories(Inventory* inv1, int index1, Inventory* inv2, int index2);

    /**
     * @brief Adds a plant to a specific slot.
     * @param plant Pointer to the Plant to add.
     * @param slotIndex Index of the target slot.
     * @return true if successfully added, false if:
     *         - plant is nullptr
     *         - slotIndex is out of bounds
     *         - Slot cannot accept the plant
     * 
     * @details If the slot doesn't exist, it is created automatically.
     */
    bool addToSpecificSlot(Plant* plant, size_t slotIndex);

private:
    size_t maxSlots;                        ///< Maximum number of slots allowed
    std::vector<InventorySlot *> slots;     ///< Vector of slot pointers (can contain nullptr)

    /**
     * @brief Finds a compatible slot for a plant.
     * @param plant Pointer to the plant to place.
     * @return Pointer to a slot that can accept the plant, or nullptr if none found.
     */
    InventorySlot *findCompatibleSlot(Plant *plant);

    /**
     * @brief Creates a new empty slot in the first available position.
     * @return Pointer to the newly created slot, or nullptr if no space for new slots.
     */
    InventorySlot *createNewSlot();
};