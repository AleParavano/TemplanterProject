/**
 * @file Store.h
 * @brief Store system for purchasing items
 *
 * @pattern Facade - Simplifies purchasing interface
 */

#pragma once

#include "StoreItem.h"
#include "Player.h"
#include "Inventory.h"
#include <vector>

/**
 * @class Store
 * @brief Manages purchasable items and transactions
 *
 * Controls item catalog and purchase validation.
 */
class Store {
private:
    std::vector<StoreItem*> items;
        
public:
    /**
     * @brief Construct empty store
     */
    Store();

    /**
     * @brief Clean up all store items
     */
    ~Store();
    
    /**
     * @brief Add item to store catalog
     * @param item Item to add (takes ownership)
     */
    void addItem(StoreItem* item);

    /**
     * @brief Attempt to purchase item
     * @param index Catalog index of item
     * @param player Player attempting purchase
     * @return true if purchase successful
     */
    bool purchaseItem(size_t index, Player* player);

    /**
     * @brief Get number of items in catalog
     * @return size_t Item count
     */
    size_t getItemCount() const;

    /**
     * @brief Get item at index
     * @param index Catalog index
     * @return StoreItem* or nullptr if invalid
     */
    StoreItem* getItem(size_t index) const;
};