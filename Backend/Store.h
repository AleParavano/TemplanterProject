/**
 * @file Store.h
 * @brief Defines the Store class for managing purchasable items.
 */

#pragma once

#include "StoreItem.h"
#include "Player.h"
#include "Inventory.h"
#include <vector>

/**
 * @class Store
 * @brief Represents an in-game store where players can purchase items.
 *
 * The Store holds a collection of available StoreItem objects and provides
 * functionality for a Player to attempt to purchase an item.
 */
class Store {
private:
    /**
     * @brief A collection of items currently available for purchase in the store.
     *
     * Items are stored as raw pointers. The Store is responsible for managing
     * the memory of the StoreItem objects added to it.
     */
    std::vector<StoreItem*> items;
        
public:
    /**
     * @brief Constructs a new Store object.
     */
    Store();

    /**
     * @brief Destroys the Store object and cleans up memory.
     *
     * It is assumed that the destructor is responsible for deleting the
     * StoreItem objects stored in the 'items' vector to prevent memory leaks.
     */
    ~Store();
    
    /**
     * @brief Adds a new item to the store's inventory.
     * @param item A pointer to the StoreItem to be added.
     */
    void addItem(StoreItem* item);

    /**
     * @brief Attempts to purchase an item from the store at a specific index.
     *
     * The function checks if the player has enough currency and if the purchase
     * is successful, it deducts the cost from the player and adds the item
     * to the player's inventory.
     *
     * @param index The index of the item in the store's list (0-based).
     * @param player A pointer to the Player attempting the purchase.
     * @return true if the purchase was successful, false otherwise (e.g., player lacks funds).
     */
    bool purchaseItem(size_t index, Player* player);

    /**
     * @brief Gets the total number of items currently available in the store.
     * @return The count of items (size_t).
     */
    size_t getItemCount() const;

    /**
     * @brief Retrieves a pointer to an item at a specific index.
     * @param index The index of the item to retrieve (0-based).
     * @return A pointer to the StoreItem, or nullptr if the index is out of bounds.
     */
    StoreItem* getItem(size_t index) const;
};