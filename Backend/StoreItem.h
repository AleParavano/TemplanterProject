/**
 * @file StoreItem.h
 * @brief Store item interface for purchasable items.
 * @details Defines the interface for items that can be sold in the store.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Store
 * @see SeedAdapter
 */

#pragma once

/**
 * @class StoreItem
 * @brief Abstract interface for store items.
 * 
 * Defines the contract for purchasable items in the store.
 * Can be implemented by seeds (SeedAdapter) or other items.
 * 
 * @par Design Pattern: Factory
 * Works with Store to provide abstract interface for various item types
 * that can be created through factories.
 * 
 * @par Usage
 * Store maintains a collection of StoreItem pointers and provides:
 * - Getting price for purchase validation
 * - Requesting item creation on purchase
 * 
 * @see Store
 * @see SeedAdapter
 */
class StoreItem 
{
public:
    /**
     * @brief Virtual destructor.
     * @details Ensures proper cleanup of derived item objects.
     */
    virtual ~StoreItem() = default;

    /**
     * @brief Gets the price of this item.
     * @return Price in currency units
     * 
     * @details Used by Store to validate player purchase ability.
     */
    virtual float getPrice() const = 0;

    /**
     * @brief Requests the item (for purchase).
     * @return Pointer to the requested item (typically a Plant)
     * 
     * @details Called when player purchases this item.
     *         Returns a newly created instance of the item.
     * 
     * @post New item is created and returned
     */
    virtual void* request() = 0;
};