#pragma once

// Forward declaration instead of include to avoid circular dependency
class Plant;

/**
 * @class GrowthCycle
 * @brief The abstract base class for defining different strategies for plant growth.
 * * Implements the Strategy design pattern, allowing a Plant's growth mechanism to be swapped.
 */
class GrowthCycle {
public:
    /**
     * @brief Default constructor.
     */
    GrowthCycle();
    
    /**
     * @brief Virtual destructor for the base class.
     */
    virtual ~GrowthCycle();
    
    /**
     * @brief The main public method that executes the growth logic.
     * * This method uses the template method pattern: it calls the private/protected
     * * virtual methods internally to execute the specific strategy steps.
     * @param plant A pointer to the Plant object whose state needs to be updated.
     * @param deltaTime The time elapsed since the last update (tick).
     */
    void grow(Plant* plant, float deltaTime);
    
protected:
    /**
     * @brief Calculates the raw growth rate based on the Plant's current state (pure virtual).
     * @param plant A pointer to the Plant object.
     * @return The calculated growth rate multiplier (float).
     */
    virtual float calculateGrowthRate(Plant* plant) = 0;
    
private:
    /**
     * @brief Applies the calculated growth amount to the Plant's properties (pure virtual).
     * @param plant A pointer to the Plant object.
     * @param growth The calculated growth amount to apply.
     */
    virtual void applyGrowth(Plant* plant, float growth) = 0;
};

// --- Concrete Strategy Implementations ---

/**
 * @class BoostedGrowthCycle
 * @brief A growth strategy that applies a higher, multiplier-based growth rate.
 * * Suitable for fast-growing or fertilized plants.
 */
class BoostedGrowthCycle : public GrowthCycle {
protected:
    /**
     * @brief Calculates a growth rate, typically applying a boost multiplier.
     * @param plant A pointer to the Plant object.
     * @return The calculated, boosted growth rate.
     */
    float calculateGrowthRate(Plant* plant) override;
    
private:
    /**
     * @brief Applies the growth amount to the Plant's properties for the boosted cycle.
     * @param plant A pointer to the Plant object.
     * @param growth The calculated growth amount to apply.
     */
    void applyGrowth(Plant* plant, float growth) override;
    
    /**
     * @brief Static constant defining the multiplier used for boosted growth.
     */
    static const float BOOST_MULTIPLIER;
};

/**
 * @class NormalGrowthCycle
 * @brief The default growth strategy with a standard growth rate.
 */
class NormalGrowthCycle : public GrowthCycle {
protected:
    /**
     * @brief Calculates a standard, un-boosted growth rate.
     * @param plant A pointer to the Plant object.
     * @return The calculated, normal growth rate.
     */
    float calculateGrowthRate(Plant* plant) override;
    
private:
    /**
     * @brief Applies the growth amount to the Plant's properties for the normal cycle.
     * @param plant A pointer to the Plant object.
     * @param growth The calculated growth amount to apply.
     */
    void applyGrowth(Plant* plant, float growth) override;
};