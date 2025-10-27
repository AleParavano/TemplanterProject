#pragma once
#include "PlantState.h"
#include "Subject.h"
#include "GrowthCycle.h"

class Plant: public Subject{
    public:
    Plant(std::string type,float growthRate);
    virtual ~Plant();
    void grow(float growth);
    std::string getType();
    void notify();
    void attach(Observer* observer);
    void detach(Observer* observer);
    void setGrowthCycle(GrowthCycle* gc);
    protected:
    PlantState* state;
    GrowthCycle* growthCycle;
    std::string type;
    float growthRate;
};