#include "GrowthCycle.h"
#include "Plant.h"
GrowthCycle::GrowthCycle() {}
GrowthCycle::~GrowthCycle() {}

const float BoostedGrowthCycle::BOOST_MULTIPLIER = 2.0f;

// Template method - defines the algorithm structure
void GrowthCycle::grow(Plant* plant, float deltaTime)
{
    float growthRate = calculateGrowthRate(plant);
    float growth = deltaTime * growthRate;
    applyGrowth(plant, growth);
}

float BoostedGrowthCycle::calculateGrowthRate(Plant* plant)
{
    float baseRate = plant->getBaseGrowthRate();
    return baseRate * BOOST_MULTIPLIER;
}

void BoostedGrowthCycle::applyGrowth(Plant* plant, float growth)
{
    plant->applyGrowthToState(growth);
}

float NormalGrowthCycle::calculateGrowthRate(Plant* plant)
{
    return plant->getBaseGrowthRate();
}

void NormalGrowthCycle::applyGrowth(Plant* plant, float growth)
{
    plant->applyGrowthToState(growth);
}