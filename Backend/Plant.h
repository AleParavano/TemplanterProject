#pragma once
#include "PlantState.h"
#include "Subject.h"

// Forward declaration - define in cpp
class GrowthCycle;

class Plant: public Subject
{
public:
    Plant(std::string type, float growthRate, float sellPrice);
    Plant(const Plant& other);
    virtual ~Plant();
    
    
    // GrowthCycle integration
    void setGrowthCycle(GrowthCycle* gc);
    void applyGrowthToState(float growth);
    float getBaseGrowthRate() const;
    
    // Observer pattern
    void notify();
    void attach(Observer* observer);
    void detach(Observer* observer);
    
    // State management
    void tick();
    void setState(PlantState* newState);
    
    // Getters - all maintained for backward compatibility
    std::string getType();
    std::string getState();
    PlantState* getPlantState();
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
};

class Lettuce : public Plant {
public:
    Lettuce() : Plant("Lettuce", 1.6f, 15.0f) {}  // Fast, cheap
};

class Carrot : public Plant {
public:
    Carrot() : Plant("Carrot", 1.4f, 25.0f) {}
};

class Potato : public Plant {
public:
    Potato() : Plant("Potato", 1.2f, 35.0f) {}
};

class Cucumber : public Plant {
public:
    Cucumber() : Plant("Cucumber", 1.1f, 45.0f) {}
};

class Tomato : public Plant {
public:
    Tomato() : Plant("Tomato", 1.0f, 55.0f) {}
};

class Pepper : public Plant {
public:
    Pepper() : Plant("Pepper", 0.9f, 65.0f) {}
};

class Sunflower : public Plant {
public:
    Sunflower() : Plant("Sunflower", 0.8f, 80.0f) {}
};

class Strawberry : public Plant {
public:
    Strawberry() : Plant("Strawberry", 0.7f, 100.0f) {}
};

class Corn : public Plant {
public:
    Corn() : Plant("Corn", 0.6f, 120.0f) {}
};

class Pumpkin : public Plant {
public:
    Pumpkin() : Plant("Pumpkin", 0.5f, 200.0f) {}  // Slowest, most valuable
};