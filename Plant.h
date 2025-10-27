#pragma once
#include "PlantState.h"
#include "Subject.h"
#include "GrowthCycle.h"

class Plant: public Subject
{
    public:
    Plant(std::string type,float growthRate);
    virtual ~Plant();
    void grow(float growth);
    std::string getType();
    void notify();
    void attach(Observer* observer);
    void detach(Observer* observer);
    void setGrowthCycle(GrowthCycle* gc);
    std::string getState();

    protected:
    PlantState* state;
    GrowthCycle* growthCycle;
    std::string type;
    float growthRate;
};

class Carrot : public Plant {
public:
    Carrot() : Plant("Carrot", 1.1f) {}
};

class Tomato : public Plant {
public:
    Tomato() : Plant("Tomato", 1.4f) {}
};

class Sunflower : public Plant {
public:
    Sunflower() : Plant("Sunflower", 1.6f) {}
};

class Lettuce : public Plant {
public:
    Lettuce() : Plant("Lettuce", 1.0f) {}
};

class Potato : public Plant {
public:
    Potato() : Plant("Potato", 1.2f) {}
};

class Cucumber : public Plant {
public:
    Cucumber() : Plant("Cucumber", 1.3f) {}
};

class Pepper : public Plant {
public:
    Pepper() : Plant("Pepper", 1.5f) {}
};

class Strawberry : public Plant {
public:
    Strawberry() : Plant("Strawberry", 1.7f) {}
};

class Corn : public Plant {
public:
    Corn() : Plant("Corn", 1.8f) {}
};

class Pumpkin : public Plant {
public:
    Pumpkin() : Plant("Pumpkin", 2.0f) {}
};