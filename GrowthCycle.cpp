#include "GrowthCycle.h"

void GrowthCycle::grow(Plant *plant, float deltaTime)
{
    float growth = calculateGrowth(plant, deltaTime);
    applyGrowth(plant, growth);
}

float BoostedGrowthCycle::calculateGrowth(Plant* plant, float deltaTime)
{
    std::string state = plant->getState();
    float growthRate = 0.0f;

    if (state == "Seed") {
        growthRate = 0.5f;
    } else if (state == "Growing") {
        growthRate = 1.0f;
    } else if (state == "Ripe") {
        growthRate = 0.3f;
    } else {
        // Dead or invalid state
        return 0.0f;
    }

    const float boostMultiplier = 2.0f;
    return deltaTime * growthRate * boostMultiplier;
}

void BoostedGrowthCycle::applyGrowth(Plant* plant, float growth)
{
    plant->grow(growth);
}

float NormalGrowthCycle::calculateGrowth(Plant* plant, float deltaTime)
{
    std::string state = plant->getState();
    float growthRate = 0.0f;

    if (state == "Seed") {
        growthRate = 0.5f;
    } else if (state == "Growing") {
        growthRate = 1.0f;
    } else if (state == "Ripe") {
        growthRate = 0.3f;
    } else {
        // Dead or invalid state
        return 0.0f;
    }

    return deltaTime * growthRate;
}
void NormalGrowthCycle::applyGrowth(Plant* plant, float growth)
{
    plant->grow(growth);
}