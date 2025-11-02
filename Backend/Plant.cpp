#include "Plant.h"
#include <string>
#include <iostream>
#include "GrowthCycle.h"
#include "PlantState.h"    // Defines PlantState and SeedState

#include "../Frontend/PlantVisualStrategy.h" 

Plant::Plant(std::string type, float growthRate, float sellPrice, PlantVisualStrategy* strategy) 
    : state(nullptr), 
      type(type), 
      growthRate(growthRate),
      sellPrice(sellPrice),
      growthCycle(new NormalGrowthCycle()),
      visualStrategy(strategy)
{
    // Fix: State construction requires the full definition of SeedState
    state = new SeedState(0.0f, 100.0f, 100.0f);
}

Plant::Plant(const Plant &other)
    : type(other.type),
      growthRate(other.growthRate),
      sellPrice(other.sellPrice),
      growthCycle(new NormalGrowthCycle()),
      state(new SeedState())
{
}

Plant::~Plant()
{
    if(state){
        delete state;
    }
    if(growthCycle){
        delete growthCycle;
    }
    if(visualStrategy){
        delete visualStrategy;
    }
}

void Plant::draw(float x, float y, float initialWidth, float initialHeight) const {
    if (visualStrategy) {
        float progress = state ? (state->getGrowth() / 100.0f) : 0.0f;
        
        float currentWidth = initialWidth * (0.3f + 0.7f * progress);
        float currentHeight = initialHeight * (0.3f + 0.7f * progress);
        
        visualStrategy->setDimensions(currentWidth, currentHeight);
        visualStrategy->setGrowth(progress);
        
        visualStrategy->setDead(isDead()); 

        visualStrategy->drawDetailed(x, y);
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
        state->tick(this);
        
        if (growthCycle) {
            growthCycle->grow(this, 1.0f);
        }
    }
}

float Plant::getGrowthRate() const 
{
    return growthRate;
}


void Plant::setState(PlantState* newState) 
{
    if (state != newState) {
        if (state) {
            delete state;
        }
        state = newState;
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

// FIX: This function requires the full definition of PlantState
PlantState *Plant::getPlantState()
{
    return this->state;
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