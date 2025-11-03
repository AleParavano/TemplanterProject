/**
 * @file SeedAdapter.h
 * @brief Adapter between StoreItem interface and Plant system
 *
 * Implements StoreItem interface to allow plants to be purchased through
 * the store system.
 *
 * @pattern Adapter - Converts between store and plant systems
 */

#pragma once

#include "StoreItem.h"
#include "Plant.h"
#include <functional>

/**
 * @class SeedAdapter
 * @brief Adapts Plant creation to StoreItem interface
 *
 * Uses factory function to create plants when purchased.
 * Bridges the gap between store system and plant system.
 */
class SeedAdapter : public StoreItem 
{
private:
    float price;
    std::function<Plant*()> plantFactory;
    
public:
    SeedAdapter(float seedPrice, std::function<Plant*()> factory);
    ~SeedAdapter();
    
    float getPrice() const override;
    void* request() override;
};
