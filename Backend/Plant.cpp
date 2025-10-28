#include "Plant.h"
#include <string>
#include <iostream>
#include "GrowthCycle.h"

Plant::Plant(std::string type, float growthRate, float sellPrice) 
    : state(nullptr), 
      type(type), 
      growthRate(growthRate),
      sellPrice(sellPrice),
      growthCycle(new NormalGrowthCycle()),
      Protected(false)
{
    state = new SeedState(0.0f, 100.0f, 100.0f);
}

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
    delete growthCycle;
    this->growthCycle = gc;
}

void Plant::applyGrowthToState(float growth)
{
    if(state) {
        state->applyGrowth(growth * growthRate);
    }
}

float Plant::getBaseGrowthRate() const
{
    return growthRate;
}

float Plant::getSellPrice() const
{
    return sellPrice;
}

void Plant::tick() 
{
    if (state) {
        // Let state handle resource consumption and state transitions
        state->tick(this);
        
        // Use GrowthCycle if available to apply growth based on deltaTime
        // For now, assume a fixed deltaTime of 1.0f per tick
        if (growthCycle) {
            growthCycle->grow(this, 1.0f);
        }
    }
}

float Plant::getGrowthRate() const 
{
    return growthRate;
}

void Plant::notify()
{
    for(auto observer : observers){
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
    for (auto obs : observers){
        if(*obs == observer){
            // Remove observer from observers vector
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

std::string Plant::getStateName() const 
{
    return state ? state->getState() : "Unknown";
}

float Plant::getWater() const 
{
    return state ? state->getWater() : 0.0f;
}

float Plant::getNutrients() const 
{
    return state ? state->getNutrients() : 0.0f;
}

float Plant::getGrowth() const 
{
    return state ? state->getGrowth() : 0.0f;
}

bool Plant::isRipe() const 
{
    return state && state->getState() == "Ripe";
}

bool Plant::isDead() const 
{
    return state && state->getState() == "Dead";
}

void Plant::fertilize(float amount)
{
    if(state) state->addNutrients(amount);
}

void Plant::water(float amount)
{
    if(state) state->addWater(amount);
}

void Plant::printStatus() const {
    std::cout << "========================================" << std::endl;
    std::cout << "Plant: " << type << std::endl;
    std::cout << "State: " << getStateName() << std::endl;
    std::cout << "Growth: " << std::fixed << getGrowth() << "%" << std::endl;
    std::cout << "Water: " << getWater() << "%" << std::endl;
    std::cout << "Nutrients: " << getNutrients() << "%" << std::endl;
    std::cout << "Growth Rate: " << growthRate << "x" << std::endl;
    
    if (isRipe()) {
        std::cout << "✓ Ready to harvest!" << std::endl;
    } else if (isDead()) {
        std::cout << "✗ Plant is dead" << std::endl;
    }
    std::cout << "========================================" << std::endl;
}
