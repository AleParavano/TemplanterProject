

#pragma once

#include "PlantState.h"       
#include "../Frontend/PlantVisualStrategy.h"      
#include <string>

// Forward declarations
class GrowthCycle;


class Plant
{
public:
    // MODIFIED BASE CONSTRUCTOR
    Plant(std::string type, float growthRate, float sellPrice, PlantVisualStrategy* strategy);
    virtual ~Plant();
    
    // GrowthCycle integration
    void setGrowthCycle(GrowthCycle* gc);
    void applyGrowthToState(float growth);
    float getBaseGrowthRate() const;
    
    // State management
    void tick();
    void setState(PlantState* newState);
    
    // NEW: Draw method
    void draw(float x, float y, float initialWidth, float initialHeight) const;
    
    // Getters
    std::string getType();
    std::string getState();
    PlantState* getPlantState(); // Requires PlantState.h
    std::string getStateName() const;
    float getGrowthRate() const;
    float getWater() const;
    float getNutrients() const;
    float getGrowth() const;
    float getSellPrice() const;
    bool isRipe() const;
    bool isDead() const;
    
    // Command pattern support
    void fertilize(float amount);
    void water(float amount);
    
    void printStatus() const;

protected:
    PlantState* state;
    GrowthCycle* growthCycle;
    std::string type;
    float growthRate;
    float sellPrice;
    
    PlantVisualStrategy* visualStrategy; 
};


// --- Derived Plant Classes (MODIFIED to accept and pass the strategy) ---

class Lettuce : public Plant {
public:
    // Accepts strategy from the Factory
    Lettuce(PlantVisualStrategy* strategy) : Plant("Lettuce", 1.6f, 15.0f, strategy) {} 
};

class Carrot : public Plant {
public:
    Carrot(PlantVisualStrategy* strategy) : Plant("Carrot", 1.4f, 25.0f, strategy) {}
};

class Potato : public Plant {
public:
    Potato(PlantVisualStrategy* strategy) : Plant("Potato", 1.2f, 35.0f, strategy) {}
};

class Cucumber : public Plant {
public:
    Cucumber(PlantVisualStrategy* strategy) : Plant("Cucumber", 1.1f, 45.0f, strategy) {}
};

class Tomato : public Plant {
public:
    Tomato(PlantVisualStrategy* strategy) : Plant("Tomato", 1.0f, 55.0f, strategy) {}
};

class Pepper : public Plant {
public:
    Pepper(PlantVisualStrategy* strategy) : Plant("Pepper", 0.9f, 65.0f, strategy) {}
};

class Sunflower : public Plant {
public:
    Sunflower(PlantVisualStrategy* strategy) : Plant("Sunflower", 0.8f, 80.0f, strategy) {}
};

class Strawberry : public Plant {
public:
    Strawberry(PlantVisualStrategy* strategy) : Plant("Strawberry", 0.7f, 100.0f, strategy) {}
};

class Corn : public Plant {
public:
    Corn(PlantVisualStrategy* strategy) : Plant("Corn", 0.6f, 120.0f, strategy) {}
};

class Pumpkin : public Plant {
public:
    Pumpkin(PlantVisualStrategy* strategy) : Plant("Pumpkin", 0.5f, 200.0f, strategy) {}
};