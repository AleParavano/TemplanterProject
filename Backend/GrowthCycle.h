/**
 * @file GrowthCycle.h
 * @brief Template Method pattern implementation for plant growth algorithms.
 * @details Defines a skeleton algorithm for plant growth that subclasses can customize.
 *          Allows different growth strategies (normal and boosted) while maintaining
 *          a consistent overall structure.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 */

#pragma once

// Forward declaration instead of include to avoid circular dependency
/**
 * @class Plant
 * @brief Forward declaration of Plant class.
 * @details Defined in Plant.h to avoid circular dependencies with GrowthCycle.
 */
class Plant;

/**
 * @class GrowthCycle
 * @brief Abstract base class defining the plant growth algorithm structure.
 * 
 * The GrowthCycle class implements the Template Method pattern to define the skeleton
 * of the plant growth algorithm. The overall structure is:
 * 1. Calculate the growth rate based on plant and conditions
 * 2. Multiply the rate by the time delta to get growth amount
 * 3. Apply the growth to the plant's state
 * 
 * Subclasses can override calculateGrowthRate() and applyGrowth() to implement
 * different growth behaviors while maintaining the same overall flow.
 * 
 * @par Design Pattern: Template Method
 * Defines the skeleton of an algorithm in a base class method, allowing subclasses
 * to override specific steps without changing the algorithm's structure.
 * 
 * @par Growth Calculation
 * growth = deltaTime × growthRate
 * The growth amount is then applied to the plant's state by the subclass.
 * 
 * @see BoostedGrowthCycle
 * @see NormalGrowthCycle
 */
class GrowthCycle {
public:
    /**
     * @brief Default constructor.
     */
    GrowthCycle();

    /**
     * @brief Virtual destructor.
     * @details Ensures proper cleanup of derived GrowthCycle objects.
     */
    virtual ~GrowthCycle();

    /**
     * @brief Executes the growth cycle for a plant over a time period.
     * @param plant Pointer to the Plant to grow.
     * @param deltaTime The elapsed time for this growth cycle.
     * 
     * @details This is the template method that defines the algorithm:
     *         1. Call calculateGrowthRate() to get the growth rate
     *         2. Calculate growth = deltaTime × growthRate
     *         3. Call applyGrowth() to apply the calculated growth
     * 
     * @pre plant must not be nullptr
     * @pre deltaTime should be positive
     * @post Plant's growth state is updated according to the subclass implementation
     * 
     * @note This method is concrete (not virtual) and should not be overridden.
     *       Subclasses should only override calculateGrowthRate() and applyGrowth().
     * 
     * @example
     * @code
     * GrowthCycle* cycle = new BoostedGrowthCycle();
     * cycle->grow(tomato, 1.0f);  // Grows tomato for 1 second with boost
     * @endcode
     */
    void grow(Plant* plant, float deltaTime);
    
protected:
    /**
     * @brief Calculates the growth rate for the plant.
     * @param plant Pointer to the Plant whose growth rate is being calculated.
     * @return The growth rate multiplier for this plant.
     * 
     * @details This is a hook method that subclasses can override to customize
     *         growth rate calculation. Called by the template method grow().
     * 
     * @see BoostedGrowthCycle::calculateGrowthRate()
     * @see NormalGrowthCycle::calculateGrowthRate()
     */
    virtual float calculateGrowthRate(Plant* plant) = 0;
    
private:
    /**
     * @brief Applies the calculated growth to the plant's state.
     * @param plant Pointer to the Plant to update.
     * @param growth The amount of growth to apply.
     * 
     * @details This is a hook method that subclasses override to apply growth
     *         in different ways. Called by the template method grow().
     * 
     * @see BoostedGrowthCycle::applyGrowth()
     * @see NormalGrowthCycle::applyGrowth()
     */
    virtual void applyGrowth(Plant* plant, float growth) = 0;
};

/**
 * @class BoostedGrowthCycle
 * @brief Growth cycle that applies a multiplier to the growth rate.
 * 
 * Implements an accelerated growth rate by applying a constant boost multiplier
 * to the plant's base growth rate. Useful for special conditions, upgrades,
 * or premium plant varieties.
 * 
 * @par Boost Multiplier
 * All growth rates are multiplied by 2.0x, doubling the growth speed compared
 * to normal growth.
 * 
 * @see GrowthCycle
 * @see NormalGrowthCycle
 */
class BoostedGrowthCycle : public GrowthCycle {
protected:
    /**
     * @brief Calculates the boosted growth rate.
     * @param plant Pointer to the Plant.
     * @return The plant's base growth rate multiplied by BOOST_MULTIPLIER (2.0).
     * 
     * @details Gets the plant's base growth rate and applies a 2x boost multiplier.
     * 
     * @override
     */
    float calculateGrowthRate(Plant* plant) override;
    
private:
    /**
     * @brief Applies the calculated growth to the plant's state.
     * @param plant Pointer to the Plant to update.
     * @param growth The boosted growth amount.
     * 
     * @override
     */
    void applyGrowth(Plant* plant, float growth) override;

    static const float BOOST_MULTIPLIER;  ///< Boost multiplier value (2.0f)
};

/**
 * @class NormalGrowthCycle
 * @brief Growth cycle with standard, unmodified growth rates.
 * 
 * Implements normal plant growth without any acceleration or modification.
 * Uses the plant's base growth rate directly.
 * 
 * @see GrowthCycle
 * @see BoostedGrowthCycle
 */
class NormalGrowthCycle : public GrowthCycle {
protected:
    /**
     * @brief Calculates the normal (base) growth rate.
     * @param plant Pointer to the Plant.
     * @return The plant's base growth rate without modification.
     * 
     * @override
     */
    float calculateGrowthRate(Plant* plant) override;
    
private:
    /**
     * @brief Applies the calculated growth to the plant's state.
     * @param plant Pointer to the Plant to update.
     * @param growth The normal growth amount.
     * 
     * @override
     */
    void applyGrowth(Plant* plant, float growth) override;
};