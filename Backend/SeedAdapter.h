/**
 * @file SeedAdapter.h
 * @brief Adapter pattern implementation connecting Plant to StoreItem.
 * @details Allows plants (seeds) to be sold through the store interface using
 *          the Adapter pattern to bridge incompatible interfaces.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see StoreItem
 * @see Plant
 * @see Store
 */

#pragma once

#include "StoreItem.h"
#include "Plant.h"
#include <functional>

/**
 * @class SeedAdapter
 * @brief Adapts a plant factory to the StoreItem interface.
 * 
 * Enables seeds to be sold in the store by adapting the Plant interface
 * to the StoreItem interface using the Adapter pattern.
 * 
 * @par Design Pattern: Adapter
 * Makes incompatible Plant objects compatible with the StoreItem interface,
 * allowing them to be sold through the Store without modifying Plant class.
 * 
 * @par Usage
 * SeedAdapter wraps a factory function that creates Plant objects and
 * presents them as StoreItem objects:
 * @code
 * // Create a seed adapter for Tomatoes
 * SeedAdapter* tomatoSeed = new SeedAdapter(
 *     55.0f,  // price
 *     []() { return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f)); }
 * );
 * 
 * // Add to store
 * store->addItem(tomatoSeed);
 * 
 * // Purchase
 * store->purchaseItem(index, player);
 * @endcode
 * 
 * @par Benefits
 * - Store doesn't need to know about Plant class
 * - Plants can be created without modifying existing code
 * - Factory functions keep creation logic centralized
 * - Compatible with Store's StoreItem interface
 * 
 * @see StoreItem
 * @see Plant
 * @see Store
 * @see PlantFactory
 */
class SeedAdapter : public StoreItem 
{
private:
    float price;                                    ///< Seed purchase price
    std::function<Plant*()> plantFactory;          ///< Factory function to create plants

public:
    /**
     * @brief Constructor.
     * @param seedPrice Price of the seed item
     * @param factory Lambda/function that creates Plant objects
     * 
     * @details Stores the price and factory function for later use.
     *         Factory is called when plant is purchased.
     * 
     * @example
     * @code
     * SeedAdapter carrot(
     *     25.0f,
     *     []() { return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f)); }
     * );
     * @endcode
     */
    SeedAdapter(float seedPrice, std::function<Plant*()> factory);

    /**
     * @brief Destructor.
     */
    ~SeedAdapter();
    
    /**
     * @brief Gets the seed price.
     * @return Price in currency units
     * 
     * @override
     */
    float getPrice() const override;

    /**
     * @brief Creates and returns a plant seed.
     * @return Pointer to a newly created Plant
     * 
     * @details Calls the stored factory function to create a new plant instance.
     *         The returned plant is ready to be added to inventory.
     * 
     * @post New Plant is created via factory
     * @override
     */
    void* request() override;
};