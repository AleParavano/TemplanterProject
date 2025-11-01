// #pragma once

// #include "StoreItem.h"
// #include "Player.h"
// #include <vector>

// class Store {
// private:
//     std::vector<StoreItem*> items;
    
// public:
//     Store();
//     ~Store();
    
//     void addItem(StoreItem* item);
//     bool purchaseItem(size_t index, Player* player);
//     size_t getItemCount() const;
//     StoreItem* getItem(size_t index) const;
// };
#pragma once

#include "StoreItem.h"
#include "Player.h"
#include "Inventory.h"
#include <vector>

class Store {
private:
    std::vector<StoreItem*> items;
    Inventory* storageInventory;  // Add storage inventory
    
public:
    Store();
    ~Store();
    
    void addItem(StoreItem* item);
    bool purchaseItem(size_t index, Player* player);
    size_t getItemCount() const;
    StoreItem* getItem(size_t index) const;
    
    // Storage access methods
    Inventory* getStorage() { return storageInventory; }
    const Inventory* getStorage() const { return storageInventory; }
    
    // Add plant directly to storage
    bool addToStorage(Plant* plant);
};