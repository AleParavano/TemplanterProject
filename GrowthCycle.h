#pragma once
//abstract strategy with template method
#include "Plant.h"
class GrowthCycle {
public:
    GrowthCycle();
    ~GrowthCycle();
     void grow(Plant* plant, float deltaTime);
private:
    virtual float calculateGrowth(Plant* plant,float deltaTime ) = 0;
    virtual void applyGrowth(Plant* plant ,float growth) = 0;
};