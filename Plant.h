#pragma once
#include "PlantState.h"
#include "Subject.h"
#include "GrowthCycle.h"

class Plant: public Subject
{
    public:
    Plant(std::string type,float growthRate);
    Plant(const Plant& other);
    virtual ~Plant();
    bool Protected=false;
    //for use with growthCycle
    void setGrowthCycle(GrowthCycle* gc);
    void grow(float growth);    
    
    //for use with observer
    void notify();
    void attach(Observer* observer);
    void detach(Observer* observer);

    //getters
    std::string getType();
    std::string getState();
    float getGrowthRate() const;
    //setters
    void setState(PlantState* newState);    
    
    // for use with commands
    void fertilize(float amount);
    void water(float amount);

    protected:
    PlantState* state;
    GrowthCycle* growthCycle;
    std::string type;
    float growthRate;
};

class Carrot : public Plant {
public:
    Carrot() : Plant("Carrot", 1.1f) {}
    Carrot(const Carrot& other) : Plant(other) {}
};

class Tomato : public Plant {
public:
    Tomato() : Plant("Tomato", 1.4f) {}
    Tomato(const Tomato& other) : Plant(other) {}
};

class Sunflower : public Plant {
public:
    Sunflower() : Plant("Sunflower", 1.6f) {}
    Sunflower(const Sunflower& other) : Plant(other) {}
};

class Lettuce : public Plant {
public:
    Lettuce() : Plant("Lettuce", 1.0f) {}
    Lettuce(const Lettuce& other) : Plant(other) {}
};

class Potato : public Plant {
public:
    Potato() : Plant("Potato", 1.2f) {}
    Potato(const Potato& other) : Plant(other) {}
};

class Cucumber : public Plant {
public:
    Cucumber() : Plant("Cucumber", 1.3f) {}
    Cucumber(const Cucumber& other) : Plant(other) {}
};

class Pepper : public Plant {
public:
    Pepper() : Plant("Pepper", 1.5f) {}
    Pepper(const Pepper& other) : Plant(other) {}
};

class Strawberry : public Plant {
public:
    Strawberry() : Plant("Strawberry", 1.7f) {}
    Strawberry(const Strawberry& other) : Plant(other) {}
};

class Corn : public Plant {
public:
    Corn() : Plant("Corn", 1.8f) {}
    Corn(const Corn& other) : Plant(other) {}
};

class Pumpkin : public Plant {
public:
    Pumpkin() : Plant("Pumpkin", 2.0f) {}
    Pumpkin(const Pumpkin& other) : Plant(other) {}
};