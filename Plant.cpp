#include "Plant.h"

Plant::Plant(std::string type, float growthRate)
: type(type),growthRate(growthRate),growthCycle(nullptr),state(new SeedState(0.0,0.0,0.0))
{}

Plant::~Plant()
{
    if(state){
        delete state;
    }
    if(growthCycle){
        delete growthCycle;
    }

}

void Plant::setGrowthCycle(GrowthCycle *gc)
{
    this->growthCycle=gc;
}

void Plant::grow(float growth)
{
    state->growth=growth*growthRate;
}

float Plant::getGrowthRate() const 
{
    return growthRate;
}

void Plant::notify()
{
    for(auto observer:observers){
        observer->update(this);
    }
}

void Plant::attach(Observer *observer)
{
    if(observer){
    observers.push_back(observer);
    }
}

void Plant::detach(Observer* observer)
{
    for (auto obs:observers){
        if(*obs==observer){
            //remove observer from observers vector
        }
    }
}

void Plant::setState(PlantState* newState) 
{
    if (state != newState) {
        if (state) {
            delete state;
        }
        state = newState;
        
        // Notify observers of state change
        notify();
    }
}

std::string Plant::getType()
{
    return type;
}

std::string Plant::getState()
{
    return state->getState();
}

void Plant::fertilize(float amount)
{
    state->nutrients+=amount;
}

void Plant::water(float amount)
{
    state->water+=amount;
}
