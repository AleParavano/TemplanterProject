#pragma once
#include <vector>
#include "Plant.h"


class InventorySlot {
public:
    InventorySlot() = default;
    
    bool add(Plant* plant);
    
    Plant* remove();
    
    bool canAccept( Plant* plant) const;
    
    bool isFull() const { return items.size() >= capacity; }

    bool isEmpty() const { return items.empty(); }
    
    int getSize() const { return items.size(); }

    std::string getPlantType() const { return plantType; }
    
    int getRemainingCapacity() const { return capacity - items.size(); }
    
private:
    static constexpr int capacity = 64;
    std::string plantType;
    std::vector<Plant*> items;
};
class Inventory{
public:
    Inventory();
    ~Inventory();
    
    bool add(Plant* plant);
    Plant* removeItem(const std::string& plantType);
    bool removeStack(size_t index);
    int getPlantCount(const std::string& plantType) const;
    size_t getStackCount() const { return slots.size(); }
    bool isFull() const;
    const InventorySlot* getSlot(size_t index) const;
    void clear();
    
private:
    static constexpr size_t MAX_SLOTS = 32;
    std::vector<InventorySlot*> slots;
    InventorySlot* findCompatibleSlot(Plant* plant);
    InventorySlot* createNewSlot();
};
