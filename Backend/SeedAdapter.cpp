#include "SeedAdapter.h"

SeedAdapter::SeedAdapter(float seedPrice, std::function<Plant*()> factory)
    : price(seedPrice), plantFactory(factory) {}

SeedAdapter::~SeedAdapter() {}

float SeedAdapter::getPrice() const 
{
    return price;
}

void* SeedAdapter::request() 
{
    return plantFactory();
}