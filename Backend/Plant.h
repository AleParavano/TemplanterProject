#pragma once

#include "PlantState.h"       
#include "../Frontend/PlantVisualStrategy.h"      
#include <string>

// Forward declarations
/**
 * @class GrowthCycle
 * @brief Forward declaration for the component responsible for managing plant growth.
 */
class GrowthCycle;


/**
 * @class Plant
 * @brief Represents a general plant entity in the game, managing its state, growth, and visualization strategy.
 * * This class implements the Context for the **State** pattern (using PlantState) and holds a reference to 
 * the **Strategy** pattern (PlantVisualStrategy) for its rendering logic.
 */
class Plant
{
public:
    /**
     * @brief Constructs a Plant object.
     * @param type The species name of the plant (e.g., "Lettuce").
     * @param growthRate The base rate at which this plant grows.
     * @param sellPrice The base price for which a ripe plant can be sold.
     * @param strategy A pointer to the specific visualization strategy for this plant.
     */
    Plant(std::string type, float growthRate, float sellPrice, PlantVisualStrategy* strategy);
    
    /**
     * @brief Copy constructor for the Plant class.
     * @param other The Plant object to copy.
     */
    Plant(const Plant &other);
    
    /**
     * @brief Virtual destructor for the Plant class.
     */
    virtual ~Plant();
    
    // GrowthCycle integration
    /**
     * @brief Sets the GrowthCycle component responsible for managing the plant's growth over time.
     * @param gc A pointer to the GrowthCycle object.
     */
    void setGrowthCycle(GrowthCycle* gc);
    
    /**
     * @brief Applies a given amount of growth to the current state of the plant.
     * @param growth The amount of growth to apply.
     */
    void applyGrowthToState(float growth);
    
    /**
     * @brief Gets the base growth rate defined for this plant type.
     * @return The base growth rate as a float.
     */
    float getBaseGrowthRate() const;
    
    // State management
    /**
     * @brief Executes a single time step (tick) for the plant, updating its growth and state.
     */
    void tick();
    
    /**
     * @brief Transitions the plant to a new state (part of the State pattern).
     * @param newState A pointer to the new PlantState object.
     */
    void setState(PlantState* newState);
    
    // NEW: Draw method
    /**
     * @brief Draws the plant using its assigned PlantVisualStrategy (part of the Strategy pattern).
     * @param x The x-coordinate for drawing.
     * @param y The y-coordinate for drawing.
     * @param initialWidth The initial base width for scaling.
     * @param initialHeight The initial base height for scaling.
     */
    void draw(float x, float y, float initialWidth, float initialHeight) const;
    
    // Getters
    /**
     * @brief Gets the species type of the plant.
     * @return The plant type as a string.
     */
    std::string getType();
    
    /**
     * @brief Gets a string representation of the plant's current state.
     * @return The state as a string.
     */
    std::string getState();
    
    /**
     * @brief Gets a pointer to the current PlantState object.
     * @return A pointer to the current PlantState.
     */
    PlantState* getPlantState(); // Requires PlantState.h
    
    /**
     * @brief Gets the name of the plant's current state.
     * @return The state name as a constant string reference.
     */
    std::string getStateName() const;
    
    /**
     * @brief Gets the plant's effective current growth rate.
     * @return The growth rate as a float.
     */
    float getGrowthRate() const;
    
    /**
     * @brief Gets the current water level of the plant.
     * @return The water level as a float.
     */
    float getWater() const;
    
    /**
     * @brief Gets the current nutrient level of the plant.
     * @return The nutrient level as a float.
     */
    float getNutrients() const;
    
    /**
     * @brief Gets the plant's current growth progress (0.0 to 1.0).
     * @return The growth progress as a float.
     */
    float getGrowth() const;
    
    /**
     * @brief Gets the base sell price of the plant.
     * @return The sell price as a float.
     */
    float getSellPrice() const;
    
    /**
     * @brief Checks if the plant is in the ripe state.
     * @return true if the plant is ripe, false otherwise.
     */
    bool isRipe() const;
    
    /**
     * @brief Checks if the plant is in the dead state.
     * @return true if the plant is dead, false otherwise.
     */
    bool isDead() const;
    
    // Command pattern support
    /**
     * @brief Applies fertilizer to the plant (part of the Command pattern).
     * @param amount The amount of fertilizer to apply.
     */
    void fertilize(float amount);
    
    /**
     * @brief Applies water to the plant (part of the Command pattern).
     * @param amount The amount of water to apply.
     */
    void water(float amount);
    
    /**
     * @brief Prints the current status details of the plant to the console.
     */
    void printStatus() const;

protected:
    /** @brief The current state of the plant (State pattern context). */
    PlantState* state;
    
    /** @brief Component handling the plant's growth logic. */
    GrowthCycle* growthCycle;
    
    /** @brief The species type of the plant (e.g., "Lettuce"). */
    std::string type;
    
    /** @brief The base growth rate of the plant. */
    float growthRate;
    
    /** @brief The base sell price of the plant when ripe. */
    float sellPrice;
    
    /** @brief The strategy for visualizing the plant (Strategy pattern reference). */
    PlantVisualStrategy* visualStrategy; 
};


// --- Derived Plant Classes (MODIFIED to accept and pass the strategy) ---

/**
 * @class Lettuce
 * @brief Concrete Plant type: Lettuce.
 */
class Lettuce : public Plant {
public:
    /**
     * @brief Constructs a Lettuce plant.
     * @param strategy The visualization strategy for Lettuce.
     */
    Lettuce(PlantVisualStrategy* strategy) : Plant("Lettuce", 1.6f, 15.0f, strategy) {} 
};

/**
 * @class Carrot
 * @brief Concrete Plant type: Carrot.
 */
class Carrot : public Plant {
public:
    /**
     * @brief Constructs a Carrot plant.
     * @param strategy The visualization strategy for Carrot.
     */
    Carrot(PlantVisualStrategy* strategy) : Plant("Carrot", 1.4f, 25.0f, strategy) {}
};

/**
 * @class Potato
 * @brief Concrete Plant type: Potato.
 */
class Potato : public Plant {
public:
    /**
     * @brief Constructs a Potato plant.
     * @param strategy The visualization strategy for Potato.
     */
    Potato(PlantVisualStrategy* strategy) : Plant("Potato", 1.2f, 35.0f, strategy) {}
};

/**
 * @class Cucumber
 * @brief Concrete Plant type: Cucumber.
 */
class Cucumber : public Plant {
public:
    /**
     * @brief Constructs a Cucumber plant.
     * @param strategy The visualization strategy for Cucumber.
     */
    Cucumber(PlantVisualStrategy* strategy) : Plant("Cucumber", 1.1f, 45.0f, strategy) {}
};

/**
 * @class Tomato
 * @brief Concrete Plant type: Tomato.
 */
class Tomato : public Plant {
public:
    /**
     * @brief Constructs a Tomato plant.
     * @param strategy The visualization strategy for Tomato.
     */
    Tomato(PlantVisualStrategy* strategy) : Plant("Tomato", 1.0f, 55.0f, strategy) {}
};

/**
 * @class Pepper
 * @brief Concrete Plant type: Pepper.
 */
class Pepper : public Plant {
public:
    /**
     * @brief Constructs a Pepper plant.
     * @param strategy The visualization strategy for Pepper.
     */
    Pepper(PlantVisualStrategy* strategy) : Plant("Pepper", 0.9f, 65.0f, strategy) {}
};

/**
 * @class Sunflower
 * @brief Concrete Plant type: Sunflower.
 */
class Sunflower : public Plant {
public:
    /**
     * @brief Constructs a Sunflower plant.
     * @param strategy The visualization strategy for Sunflower.
     */
    Sunflower(PlantVisualStrategy* strategy) : Plant("Sunflower", 0.8f, 80.0f, strategy) {}
};

/**
 * @class Strawberry
 * @brief Concrete Plant type: Strawberry.
 */
class Strawberry : public Plant {
public:
    /**
     * @brief Constructs a Strawberry plant.
     * @param strategy The visualization strategy for Strawberry.
     */
    Strawberry(PlantVisualStrategy* strategy) : Plant("Strawberry", 0.7f, 100.0f, strategy) {}
};

/**
 * @class Corn
 * @brief Concrete Plant type: Corn.
 */
class Corn : public Plant {
public:
    /**
     * @brief Constructs a Corn plant.
     * @param strategy The visualization strategy for Corn.
     */
    Corn(PlantVisualStrategy* strategy) : Plant("Corn", 0.6f, 120.0f, strategy) {}
};

/**
 * @class Pumpkin
 * @brief Concrete Plant type: Pumpkin.
 */
class Pumpkin : public Plant {
public:
    /**
     * @brief Constructs a Pumpkin plant.
     * @param strategy The visualization strategy for Pumpkin.
     */
    Pumpkin(PlantVisualStrategy* strategy) : Plant("Pumpkin", 0.5f, 200.0f, strategy) {}
};
