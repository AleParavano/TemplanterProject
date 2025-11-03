/**
 * @file Plant.h
 * @brief Plant base class and concrete plant types declarations.
 *
 * Defines Plant core interface, state integration and visual strategy dependency.
 * Concrete plant types are lightweight wrappers providing default parameters.
 *
 * @pattern State, Strategy, Template Method (via GrowthCycle)
 */

#pragma once

#include "PlantState.h"       
#include "../Frontend/PlantVisualStrategy.h"      
#include <string>

// Forward declarations
class GrowthCycle;

/**
 * @class Plant
 * @brief Represents a plant with growth state, growth cycle and visual strategy.
 *
 * Responsible for ticking, state transitions and exposing attributes used by other systems
 * (inventory, greenhouse, workers, serializer).
 */
class Plant
{
public:
    /**
     * @brief Construct a new Plant object.
     * @param type Plant type name
     * @param growthRate Base growth multiplier
     * @param sellPrice Sell price when harvested
     * @param strategy Visual strategy used by frontend
     */
    Plant(std::string type, float growthRate, float sellPrice, PlantVisualStrategy* strategy);

    /**
     * @brief Copy constructor.
     */
    Plant(const Plant &other);

    /**
     * @brief Destroy the Plant object.
     */
    virtual ~Plant();
    
    /**
     * @brief Assign a GrowthCycle controller.
     * @param gc GrowthCycle pointer (ownership transferred)
     */
    void setGrowthCycle(GrowthCycle* gc);

    /**
     * @brief Apply growth delta to the underlying PlantState.
     * @param growth Growth amount to apply (scaled internally)
     */
    void applyGrowthToState(float growth);

    /**
     * @brief Get base growth rate of the plant.
     * @return float
     */
    float getBaseGrowthRate() const;
    
    /**
     * @brief Advance the plant state for one tick.
     */
    void tick();

    /**
     * @brief Replace the current PlantState with a new one.
     * @param newState New PlantState instance (ownership transferred)
     */
    void setState(PlantState* newState);
    
    /**
     * @brief Draw the plant using the visual strategy.
     * @param x X coordinate
     * @param y Y coordinate
     * @param initialWidth Base width
     * @param initialHeight Base height
     */
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

// Derived plant classes provide default parameterization and keep documentation minimal.
class Lettuce : public Plant {
public:
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