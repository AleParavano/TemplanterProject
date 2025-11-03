/**
 * @file StoreItem.h
 * @brief Abstract interface for purchasable items
 *
 * Defines the interface that all store items must implement.
 * Part of the Adapter pattern for seed/plant purchases.
 *
 * @pattern Adapter - Interface for purchasable items
 */

#pragma once

/**
 * @class StoreItem
 * @brief Interface for items that can be purchased from the store
 *
 * Abstract base class defining the contract for purchasable items.
 * Implemented by SeedAdapter to convert between store and plant systems.
 */
class StoreItem 
{
public:
    virtual ~StoreItem() = default;
    virtual float getPrice() const = 0;
    virtual void* request() = 0;
};