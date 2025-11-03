/**
 * @file SeedAdapter.cpp
 * @brief Implementation of SeedAdapter for store integration
 *
 * Adapts plant creation into the StoreItem interface.
 */

#include "SeedAdapter.h"

/**
 * @brief Construct adapter with price and factory
 * @param seedPrice Price in store
 * @param factory Lambda to create specific plant type
 */
SeedAdapter::SeedAdapter(float seedPrice, std::function<Plant*()> factory)
    : price(seedPrice), plantFactory(factory) {}

/**
 * @brief Clean up adapter resources
 */
SeedAdapter::~SeedAdapter() {}

/**
 * @brief Get item price in store
 * @return float Price
 */
float SeedAdapter::getPrice() const 
{
    return price;
}

/**
 * @brief Create new plant instance
 * @return void* Plant pointer as generic item
 */
void* SeedAdapter::request() 
{
    return plantFactory();
}