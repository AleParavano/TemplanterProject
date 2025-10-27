#pragma once
#include "GrowthCycle.h"
class BoostedGrowthCycle : public GrowthCycle {
private:
    float calculateGrowth(Plant* plant, float deltaTime) override ;
    void applyGrowth(Plant* plant, float growth) override ;
};