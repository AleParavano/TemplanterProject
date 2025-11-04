/**
 * @file Plant.h
 * @brief Plant entity with state management and lifecycle.
 * @details Defines the Plant base class and all 10 plant types with complete lifecycle,
 *          state management, and visual representation.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see PlantState
 * @see GrowthCycle
 * @see PlantVisualStrategy
 */

#pragma once

#include "PlantState.h"
#include "../Frontend/PlantVisualStrategy.h"
#include <string>

// Forward declarations
/**
 * @class GrowthCycle
 * @brief Forward declaration of GrowthCycle class.
 */
class GrowthCycle;

/**
 * @class Plant
 * @brief Core plant entity with state machine and lifecycle management.
 * 
 * The Plant class represents a plant in the nursery with complete lifecycle management.
 * Each plant has:
 * - A state (Seed, Growing, Ripe, or Dead) via PlantState pattern
 * - Growth properties (growth rate, sell price, type)
 * - Resource levels (water, nutrients)
 * - A visual representation (PlantVisualStrategy)
 * - Growth cycle behavior (NormalGrowthCycle or BoostedGrowthCycle)
 * 
 * @par Design Pattern: State
 * Uses the State pattern via PlantState to manage plant lifecycle.
 * State transitions occur automatically based on resource levels and growth.
 * 
 * @par Design Pattern: Strategy
 * Uses PlantVisualStrategy for rendering behavior, allowing different visual
 * representations without modifying the Plant class.
 * 
 * @par Lifecycle
 * Plants progress through states:
 * 1. Seed (0-25% growth) - High resource consumption
 * 2. Growing (25-100% growth) - Normal resource consumption
 * 3. Ripe (100%+ growth) - Ready for harvest, reduced consumption
 * 4. Dead - No consumption, cannot recover
 * 
 * @par Resource Management
 * Each state consumes resources (water, nutrients) at different rates.
 * If either resource reaches 0, plant dies.
 * 
 * @example
 * @code
 * Plant* tomato = new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
 * tomato->tick();  // Advance lifecycle
 * tomato->water(20.0f);  // Add water
 * tomato->fertilize(15.0f);  // Add nutrients
 * if (tomato->isRipe()) {
 *     // Ready to harvest
 * }
 * @endcode
 * 
 * @see PlantState
 * @see SeedState
 * @see GrowingState
 * @see RipeState
 * @see DeadState
 */
class Plant
{
public:
    /**
     * @brief Constructor for a plant with visual strategy.
     * @param type Plant type identifier (e.g., "Tomato", "Lettuce")
     * @param growthRate Growth multiplier for this plant type (0.5-1.6)
     * @param sellPrice Harvest value in currency units
     * @param strategy Pointer to a PlantVisualStrategy for rendering
     * 
     * @details Initializes plant in Seed state with full resources.
     *         Strategy is owned by Plant and deleted in destructor.
     * 
     * @pre strategy must not be nullptr
     * @post Plant is in Seed state (0% growth, 100% water/nutrients)
     */
    Plant(std::string type, float growthRate, float sellPrice, PlantVisualStrategy* strategy);

    /**
     * @brief Copy constructor.
     * @param other Reference to another Plant to copy.
     */
    Plant(const Plant &other);

    /**
     * @brief Destructor.
     * @details Cleans up state, growth cycle, and visual strategy.
     */
    virtual ~Plant();
    
    // Growth cycle management
    
    /**
     * @brief Sets the growth cycle algorithm.
     * @param gc Pointer to a GrowthCycle subclass (Normal or Boosted)
     * 
     * @details Deletes the old growth cycle and adopts the new one.
     *         The Plant owns the growth cycle object.
     * 
     * @post Growth behavior changes to the new cycle
     */
    void setGrowthCycle(GrowthCycle* gc);

    /**
     * @brief Applies growth from the growth cycle to plant state.
     * @param growth Raw growth amount (typically 0-2.0f per tick)
     * 
     * @details Called by GrowthCycle::grow() to apply calculated growth.
     *         Growth is multiplied by the plant's base growth rate.
     * 
     * @post Plant's growth value increases (capped at 100%)
     */
    void applyGrowthToState(float growth);

    /**
     * @brief Gets the base growth rate for this plant type.
     * @return Growth rate multiplier (e.g., 1.0 for Tomato, 1.6 for Lettuce)
     * 
     * @details Higher rates mean faster maturation.
     * @see GrowthCycle::calculateGrowthRate()
     */
    float getBaseGrowthRate() const;
    
    // Lifecycle management
    
    /**
     * @brief Advances plant lifecycle by one game tick.
     * @details Called each game cycle to:
     *         1. Consume resources based on current state
     *         2. Check for state transitions
     *         3. Update growth via growth cycle
     * 
     * @post Plant state may transition to next stage
     * @post Resources are consumed
     * @post Dead plants do not tick further
     */
    void tick();

    /**
     * @brief Manually sets the plant's state.
     * @param newState Pointer to a PlantState subclass
     * 
     * @details Deletes the old state and adopts the new one.
     *         Used internally for state transitions.
     * 
     * @pre newState must not be nullptr
     * @post Plant uses new state for resource management
     */
    void setState(PlantState* newState);
    
    // Rendering
    
    /**
     * @brief Draws the plant at a position with growth-based scaling.
     * @param x X-coordinate for drawing position
     * @param y Y-coordinate for drawing position
     * @param initialWidth Base width at 0% growth
     * @param initialHeight Base height at 0% growth
     * 
     * @details Visual size scales from 30% to 100% based on growth progress.
     *         Growth progress is calculated as: currentGrowth / 100.0f
     *         Passes rendering details to PlantVisualStrategy.
     * 
     * @post Plant is rendered on screen with current visual representation
     */
    void draw(float x, float y, float initialWidth, float initialHeight) const;
    
    // Plant properties
    
    /**
     * @brief Gets the plant type identifier.
     * @return String name (e.g., "Tomato", "Lettuce", "Carrot")
     */
    std::string getType();

    /**
     * @brief Gets the current state name as a string.
     * @return State name ("Seed", "Growing", "Ripe", or "Dead")
     */
    std::string getState();

    /**
     * @brief Gets the full PlantState object for advanced queries.
     * @return Pointer to the current PlantState
     * 
     * @details Allows direct access to state for reading all properties.
     * @see PlantState
     */
    PlantState* getPlantState();

    /**
     * @brief Gets the current state name as a string.
     * @return State name or "Unknown" if state is null
     */
    std::string getStateName() const;

    /**
     * @brief Gets the current growth rate.
     * @return Growth rate multiplier for this plant
     */
    float getGrowthRate() const;

    /**
     * @brief Gets the sell price of this plant type.
     * @return Price in currency units when harvested
     * 
     * @details Different plant types have different values:
     *         - Lettuce: 15
     *         - Carrot: 25
     *         - Tomato: 55
     *         - Pumpkin: 200
     */
    float getSellPrice() const;
    
    // Resource accessors
    
    /**
     * @brief Gets the current water level.
     * @return Water percentage (0-100)
     */
    float getWater() const;

    /**
     * @brief Gets the current nutrient level.
     * @return Nutrient percentage (0-100)
     */
    float getNutrients() const;

    /**
     * @brief Gets the current growth progress.
     * @return Growth percentage (0-100+)
     */
    float getGrowth() const;
    
    // State queries
    
    /**
     * @brief Checks if the plant is ready for harvest.
     * @return true if state is "Ripe", false otherwise
     */
    bool isRipe() const;

    /**
     * @brief Checks if the plant is dead.
     * @return true if state is "Dead", false otherwise
     * 
     * @note Dead plants cannot be recovered or interacted with
     */
    bool isDead() const;
    
    // Resource management (Command pattern support)
    
    /**
     * @brief Adds nutrients to the plant.
     * @param amount Nutrient amount to add (capped at 100%)
     * 
     * @details Called by FertilizeCommand when a worker fertilizes.
     * @post Nutrient level increases up to maximum
     */
    void fertilize(float amount);

    /**
     * @brief Adds water to the plant.
     * @param amount Water amount to add (capped at 100%)
     * 
     * @details Called by WaterCommand when a worker waters.
     * @post Water level increases up to maximum
     */
    void water(float amount);
    
    /**
     * @brief Prints the current plant status to console.
     * @details Outputs: type, state, growth, water, nutrients, growth rate
     *         And indicators for ripe/dead status.
     */
    void printStatus() const;

protected:
    PlantState* state;                      ///< Current lifecycle state
    GrowthCycle* growthCycle;               ///< Growth behavior algorithm
    std::string type;                       ///< Plant type name
    float growthRate;                       ///< Growth multiplier (affects maturation speed)
    float sellPrice;                        ///< Harvest value
    PlantVisualStrategy* visualStrategy;    ///< Rendering strategy
};

// ============================================================================
// DERIVED PLANT CLASSES (10 types)
// ============================================================================

/**
 * @class Lettuce
 * @brief Fast-growing, low-value vegetable.
 * @details Growth Rate: 1.6x (fastest)
 *         Sell Price: 15 (lowest)
 *         Ideal for quick harvests
 */
class Lettuce : public Plant {
public:
    /**
     * @brief Constructor for Lettuce.
     * @param strategy Pointer to visual strategy for rendering
     */
    Lettuce(PlantVisualStrategy* strategy) : Plant("Lettuce", 1.6f, 15.0f, strategy) {} 
};

/**
 * @class Carrot
 * @brief Medium-speed root vegetable.
 * @details Growth Rate: 1.4x
 *         Sell Price: 25
 */
class Carrot : public Plant {
public:
    /**
     * @brief Constructor for Carrot.
     * @param strategy Pointer to visual strategy for rendering
     */
    Carrot(PlantVisualStrategy* strategy) : Plant("Carrot", 1.4f, 25.0f, strategy) {}
};

/**
 * @class Potato
 * @brief Moderate-speed tuber.
 * @details Growth Rate: 1.2x
 *         Sell Price: 35
 */
class Potato : public Plant {
public:
    /**
     * @brief Constructor for Potato.
     * @param strategy Pointer to visual strategy for rendering
     */
    Potato(PlantVisualStrategy* strategy) : Plant("Potato", 1.2f, 35.0f, strategy) {}
};

/**
 * @class Cucumber
 * @brief Climbing vine vegetable.
 * @details Growth Rate: 1.1x
 *         Sell Price: 45
 */
class Cucumber : public Plant {
public:
    /**
     * @brief Constructor for Cucumber.
     * @param strategy Pointer to visual strategy for rendering
     */
    Cucumber(PlantVisualStrategy* strategy) : Plant("Cucumber", 1.1f, 45.0f, strategy) {}
};

/**
 * @class Tomato
 * @brief Classic fruiting plant.
 * @details Growth Rate: 1.0x (baseline)
 *         Sell Price: 55
 */
class Tomato : public Plant {
public:
    /**
     * @brief Constructor for Tomato.
     * @param strategy Pointer to visual strategy for rendering
     */
    Tomato(PlantVisualStrategy* strategy) : Plant("Tomato", 1.0f, 55.0f, strategy) {}
};

/**
 * @class Pepper
 * @brief Slightly slow fruiting plant.
 * @details Growth Rate: 0.9x
 *         Sell Price: 65
 */
class Pepper : public Plant {
public:
    /**
     * @brief Constructor for Pepper.
     * @param strategy Pointer to visual strategy for rendering
     */
    Pepper(PlantVisualStrategy* strategy) : Plant("Pepper", 0.9f, 65.0f, strategy) {}
};

/**
 * @class Sunflower
 * @brief Tall decorative flower.
 * @details Growth Rate: 0.8x
 *         Sell Price: 80
 */
class Sunflower : public Plant {
public:
    /**
     * @brief Constructor for Sunflower.
     * @param strategy Pointer to visual strategy for rendering
     */
    Sunflower(PlantVisualStrategy* strategy) : Plant("Sunflower", 0.8f, 80.0f, strategy) {}
};

/**
 * @class Strawberry
 * @brief Delicate berry plant.
 * @details Growth Rate: 0.7x
 *         Sell Price: 100
 */
class Strawberry : public Plant {
public:
    /**
     * @brief Constructor for Strawberry.
     * @param strategy Pointer to visual strategy for rendering
     */
    Strawberry(PlantVisualStrategy* strategy) : Plant("Strawberry", 0.7f, 100.0f, strategy) {}
};

/**
 * @class Corn
 * @brief Tall grain crop.
 * @details Growth Rate: 0.6x
 *         Sell Price: 120
 */
class Corn : public Plant {
public:
    /**
     * @brief Constructor for Corn.
     * @param strategy Pointer to visual strategy for rendering
     */
    Corn(PlantVisualStrategy* strategy) : Plant("Corn", 0.6f, 120.0f, strategy) {}
};

/**
 * @class Pumpkin
 * @brief Slow-growing, high-value crop.
 * @details Growth Rate: 0.5x (slowest)
 *         Sell Price: 200 (highest)
 *         Ideal for long-term investment
 */
class Pumpkin : public Plant {
public:
    /**
     * @brief Constructor for Pumpkin.
     * @param strategy Pointer to visual strategy for rendering
     */
    Pumpkin(PlantVisualStrategy* strategy) : Plant("Pumpkin", 0.5f, 200.0f, strategy) {}
};