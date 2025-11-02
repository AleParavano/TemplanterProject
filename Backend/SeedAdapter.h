#pragma once

#include "StoreItem.h"
#include "Plant.h"
#include <functional>

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
