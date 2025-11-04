#pragma once
#include <vector>
#include <string> // Added include for std::string

// Forward declaration
class Plant;

/**
 * @class InventorySlot
 * @brief Represents a single stackable container within an Inventory, holding items of the same type.
 * * It implements stack logic up to a fixed capacity.
 */
class InventorySlot
{
public:
    /**
     * @brief Default constructor for an InventorySlot.
     */
    InventorySlot() = default;

    /**
     * @brief Attempts to add a plant to the slot.
     * * The plant must be compatible with the existing type and the slot must not be full.
     * @param plant Pointer to the Plant object to add.
     * @return true if the plant was successfully added, false otherwise.
     */
    bool add(Plant *plant);

    /**
     * @brief Removes and returns the last plant added to the stack (LIFO).
     * @return A pointer to the removed Plant object, or nullptr if the slot is empty.
     */
    Plant *remove();

    /**
     * @brief Checks if the slot can accept the given plant type.
     * @param plant Pointer to the Plant object to check compatibility against.
     * @return true if the plant's type matches the slot's type or if the slot is empty, false otherwise.
     */
    bool canAccept(Plant *plant) const;

    /**
     * @brief Checks if the slot has reached its maximum capacity.
     * @return true if the slot is full, false otherwise.
     */
    bool isFull() const { return items.size() >= capacity; }

    /**
     * @brief Checks if the slot is empty (contains no items).
     * @return true if the slot is empty, false otherwise.
     */
    bool isEmpty() const { return items.empty(); }

    /**
     * @brief Gets the current number of items in the slot.
     * @return The size of the stack.
     */
    int getSize() const { return items.size(); }

    /**
     * @brief Gets the type identifier of the plant stored in this slot.
     * @return The string name of the plant type, or an empty string if empty.
     */
    std::string getPlantType() const { return plantType; }

    /**
     * @brief Gets the number of items that can still be added before the slot is full.
     * @return The remaining capacity.
     */
    int getRemainingCapacity() const { return capacity - items.size(); }

    /**
     * @brief Gets a plant from the stack at a specific index.
     * @param index The 0-indexed position within the stack.
     * @return A pointer to the Plant at the index, or nullptr if the index is invalid.
     */
    Plant* getPlant(int index) const 
    {
        if (index >= 0 && index < (int)items.size()) { return items[index]; }
        return nullptr;
    }
    
private:
    /**
     * @brief The maximum number of items this slot can hold.
     */
    static constexpr int capacity = 64;
    
    /**
     * @brief The string type identifier for the plants stored in this slot.
     */
    std::string plantType;
    
    /**
     * @brief The vector holding pointers to the actual Plant objects (the stack).
     */
    std::vector<Plant *> items;
};

// --- Inventory Manager ---

/**
 * @class Inventory
 * @brief Manages a collection of InventorySlots, providing high-level item management functions.
 */
class Inventory
{
public:
    /**
     * @brief Constructor for the Inventory.
     * @param capacity The maximum number of InventorySlots this inventory can hold.
     */
    Inventory(int capacity);
    
    /**
     * @brief Destructor for the Inventory. Responsible for cleaning up InventorySlot pointers.
     */
    ~Inventory();

    /**
     * @brief Adds a plant to a compatible or new slot.
     * @param plant Pointer to the Plant object to add.
     * @return true if the plant was successfully added, false otherwise (e.g., if inventory is full).
     */
    bool add(Plant *plant);
    
    /**
     * @brief Finds and removes a single item of the specified type from its corresponding slot.
     * @param plantType The string type of the plant to remove.
     * @return A pointer to the removed Plant object, or nullptr if none was found.
     */
    Plant *removeItem(const std::string &plantType);
    
    /**
     * @brief Removes and deletes an entire InventorySlot (stack) at a specific index.
     * @param index The index of the slot to remove.
     * @return true if the stack was successfully removed, false otherwise.
     */
    bool removeStack(size_t index);
    
    /**
     * @brief Counts the total number of plants of a specific type across all slots.
     * @param plantType The type of plant to count.
     * @return The total number of plants of that type.
     */
    int getPlantCount(const std::string &plantType) const;
    
    /**
     * @brief Gets the current number of occupied InventorySlots.
     * @return The count of inventory stacks.
     */
    size_t getStackCount() const { return slots.size(); }
    
    /**
     * @brief Checks if the Inventory has reached its maximum number of slots.
     * @return true if maxSlots capacity is reached, false otherwise.
     */
    bool isFull() const;
    
    /**
     * @brief Gets a pointer to a specific InventorySlot.
     * @param index The index of the slot to retrieve.
     * @return A const pointer to the InventorySlot, or nullptr if the index is invalid.
     */
    const InventorySlot *getSlot(size_t index) const;
    
    /**
     * @brief Clears all slots and deletes all stored Plant objects.
     */
    void clear();

    /**
     * @brief Gets the maximum number of slots the inventory can currently hold.
     * @return The maximum slot capacity.
     */
    size_t getMaxSlots() const { return maxSlots; }
    
    /**
     * @brief Sets or updates the maximum number of slots the inventory can hold.
     * @param capacity The new maximum slot capacity.
     */
    void setMaxSlots(size_t capacity) { maxSlots = capacity; }

    // Frontend methods
    
    /**
     * @brief Swaps the contents (pointers to InventorySlots) of two slot indices within this inventory.
     * @param index1 The index of the first slot.
     * @param index2 The index of the second slot.
     */
    void swapSlots(int index1, int index2);
    
    // NEW: Cross-inventory swap
    
    /**
     * @brief Static utility method to swap the contents of two slots between two different inventories.
     * @param inv1 Pointer to the first Inventory.
     * @param index1 The slot index in the first inventory.
     * @param inv2 Pointer to the second Inventory.
     * @param index2 The slot index in the second inventory.
     */
    static void swapBetweenInventories(Inventory* inv1, int index1, Inventory* inv2, int index2);
    
    /**
     * @brief Attempts to add a plant directly into an existing specific slot.
     * @param plant Pointer to the Plant object to add.
     * @param slotIndex The index of the target slot.
     * @return true if the plant was successfully added, false otherwise (e.g., slot full or incompatible type).
     */
    bool addToSpecificSlot(Plant* plant, size_t slotIndex);

private:
    /**
     * @brief The maximum number of InventorySlots this inventory can contain.
     */
    size_t maxSlots;
    
    /**
     * @brief The vector holding pointers to the InventorySlot objects.
     */
    std::vector<InventorySlot *> slots;
    
    /**
     * @brief Finds an existing slot that can accept the given plant (either empty or compatible type/not full).
     * @param plant Pointer to the Plant object to check compatibility for.
     * @return A pointer to a compatible InventorySlot, or nullptr if none is found.
     */
    InventorySlot *findCompatibleSlot(Plant *plant);
    
    /**
     * @brief Creates a new InventorySlot and adds it to the inventory's slots vector, if capacity allows.
     * @return A pointer to the newly created InventorySlot, or nullptr if the inventory is full.
     */
    InventorySlot *createNewSlot();
};