#pragma once
#include "GrowthCycle.h"
class NormalGrowthCycle : public GrowthCycle {
private:
    float calculateGrowth(Plant* plant, float deltaTime) override ;
    void applyGrowth(Plant* plant, float growth) override ;
};