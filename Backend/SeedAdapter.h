#pragma once

#include "StoreItem.h"
#include "Plant.h"
#include <functional>

/**
 * @class SeedAdapter
 * @brief An Adapter class that makes a Plant Factory function conform to the StoreItem interface.
 * * This is part of the **Adapter** design pattern, allowing the store to sell seeds 
 * (which are Plant Factory methods) as generic StoreItem objects.
 */
class SeedAdapter : public StoreItem 
{
private:
    /** @brief The price of the seed (store item). */
    float price;
    
    /** @brief A function object (lambda or function pointer) that, when called, creates a specific Plant instance (the Factory Method). */
    std::function<Plant*()> plantFactory;
    
public:
    /**
     * @brief Constructs a SeedAdapter.
     * @param seedPrice The price of the seed/item.
     * @param factory The function (factory method) used to create the specific Plant when the item is "requested" (purchased).
     */
    SeedAdapter(float seedPrice, std::function<Plant*()> factory);
    
    /**
     * @brief Destructor for the SeedAdapter.
     */
    ~SeedAdapter();
    
    /**
     * @brief Gets the price of the seed.
     * @return The price as a float.
     */
    float getPrice() const override;
    
    /**
     * @brief Requests (purchases) the item, which executes the Plant Factory function 
     * and returns a pointer to the newly created Plant (as a generic void*).
     * @return A void pointer to the newly created Plant object.
     */
    void* request() override;
};
