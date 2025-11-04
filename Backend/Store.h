/**
 * @file Store.h
 * @brief Store system for buying and selling items.
 * @details Manages store inventory and handles customer purchase transactions
 *          with money and inventory validation.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see StoreItem
 * @see SeedAdapter
 * @see Player
 * @see Inventory
 */

#pragma once

#include "StoreItem.h"
#include "Player.h"
#include "Inventory.h"
#include <vector>

// Forward declarations
class Player;

/**
 * @class Store
 * @brief Central store for buying seeds and items.
 * 
 * The Store class manages purchasable items and handles transactions.
 * Players can browse items and make purchases with money.
 * 
 * @par Features
 * - Item inventory management
 * - Purchase validation (funds, inventory space)
 * - Transaction processing
 * - Item counting and retrieval
 * 
 * @par Transaction Flow
 * 1. Player requests purchase of item at index
 * 2. Store checks player has sufficient funds
 * 3. Store checks player has inventory space
 * 4. Store requests item via StoreItem::request()
 * 5. Item is added to player inventory
 * 6. Player funds are deducted
 * 
 * @par Usage
 * @code
 * Store store;
 * store.addItem(new SeedAdapter(15.0f, []() { return new Lettuce(...); }));
 * store.addItem(new SeedAdapter(55.0f, []() { return new Tomato(...); }));
 * 
 * if (store.purchaseItem(0, player)) {
 *     // Lettuce purchased successfully
 * }
 * @endcode
 * 
 * @see StoreItem
 * @see SeedAdapter
 * @see Player
 */
class Store {
private:
    std::vector<StoreItem*> items;  ///< Store inventory (items for sale)

public:
    /**
     * @brief Constructor.
     * @details Creates an empty store with no items.
     */
    Store();

    /**
     * @brief Destructor.
     * @details Deletes all items in the store.
     *         Called when store is destroyed or on game cleanup.
     */
    ~Store();
    
    /**
     * @brief Adds an item to the store.
     * @param item Pointer to a StoreItem to sell
     * 
     * @details Item is added to the store's inventory and becomes available
     *         for purchase. Store takes ownership of the item.
     * 
     * @post Item is added to items vector
     * 
     * @example
     * @code
     * store->addItem(new SeedAdapter(25.0f, createCarrot));
     * @endcode
     */
    void addItem(StoreItem* item);

    /**
     * @brief Purchases an item from the store.
     * @param index Store item index (0-based)
     * @param player Pointer to the player making purchase
     * @return true if purchase succeeds, false if insufficient funds or inventory full
     * 
     * @details Validates:
     *         1. Player has enough money for item
     *         2. Player inventory is not full
     *         3. Item can be created
     *
     *         Then performs:
     *         1. Requests item creation from StoreItem
     *         2. Adds item to player inventory
     *         3. Deducts money from player
     * 
     * @pre index must be valid (< getItemCount())
     * @pre player must not be nullptr
     * 
     * @post On success:
     *       - Item is added to player inventory
     *       - Player money is decreased by item price
     *       - true is returned
     * 
     * @post On failure:
     *       - No changes to player state
     *       - false is returned
     * 
     * @example
     * @code
     * if (store->purchaseItem(0, player)) {
     *     // Purchase successful
     * } else {
     *     // Purchase failed (insufficient funds or full inventory)
     * }
     * @endcode
     */
    bool purchaseItem(size_t index, Player* player);

    /**
     * @brief Gets the number of items in the store.
     * @return Item count
     * 
     * @details Used to validate item indices before purchase.
     */
    size_t getItemCount() const;

    /**
     * @brief Gets a specific store item.
     * @param index Item index (0-based)
     * @return Pointer to the StoreItem, or nullptr if index is out of bounds
     * 
     * @details Allows UI to display item information (price, description, etc.)
     * 
     * @pre index < getItemCount()
     * 
     * @example
     * @code
     * for (size_t i = 0; i < store->getItemCount(); ++i) {
     *     StoreItem* item = store->getItem(i);
     *     float price = item->getPrice();
     * }
     * @endcode
     */
    StoreItem* getItem(size_t index) const;
};