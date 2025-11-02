#pragma once
#include <vector>
#include "Plant.h"

class InventorySlot
{
public:
    InventorySlot() = default;

    bool add(Plant *plant);

    Plant *remove();

    bool canAccept(Plant *plant) const;

    bool isFull() const { return items.size() >= capacity; }

    bool isEmpty() const { return items.empty(); }

    int getSize() const { return items.size(); }

    std::string getPlantType() const { return plantType; }

    int getRemainingCapacity() const { return capacity - items.size(); }

    Plant* getPlant(int index) const 
    {
        if (index >= 0 && index < (int)items.size()) { return items[index]; }
        return nullptr;
    }
    
private:
    static constexpr int capacity = 64;
    std::string plantType;
    std::vector<Plant *> items;
};

class Inventory
{
public:
    Inventory(int capacity);
    ~Inventory();

    bool add(Plant *plant);
    Plant *removeItem(const std::string &plantType);
    bool removeStack(size_t index);
    int getPlantCount(const std::string &plantType) const;
    size_t getStackCount() const { return slots.size(); }
    bool isFull() const;
    const InventorySlot *getSlot(size_t index) const;
    void clear();

    size_t getMaxSlots() const { return maxSlots; }
    void setMaxSlots(size_t capacity) { maxSlots = capacity; }

    // Frontend methods
    void swapSlots(int index1, int index2);
    
    // NEW: Cross-inventory swap
    static void swapBetweenInventories(Inventory* inv1, int index1, Inventory* inv2, int index2);
    bool addToSpecificSlot(Plant* plant, size_t slotIndex);

private:
    size_t maxSlots;
    std::vector<InventorySlot *> slots;
    InventorySlot *findCompatibleSlot(Plant *plant);
    InventorySlot *createNewSlot();
};