/**
 * @file GrowthCycle.h
 * @brief Plant growth behavior management
 *
 * Defines growth cycle strategies and their application to plants.
 * 
 * @pattern Template Method - Defines skeleton of growth algorithm
 * @pattern Strategy - Swappable growth behaviors
 */

class Plant;

/**
 * @class GrowthCycle
 * @brief Base class for plant growth behaviors
 *
 * Abstract base class that defines the template method for growing plants
 * and lets subclasses define specific growth rate calculations.
 */
class GrowthCycle {
public:
    /**
     * @brief Default constructor
     */
    GrowthCycle();

    /**
     * @brief Virtual destructor
     */
    virtual ~GrowthCycle();

    /**
     * @brief Template method that defines growth algorithm
     * @param plant Plant to grow
     * @param deltaTime Time elapsed since last update
     */
    void grow(Plant* plant, float deltaTime);
    
protected:
    /**
     * @brief Calculate growth rate for a specific plant
     * @param plant Plant to calculate rate for
     * @return float Growth rate multiplier
     */
    virtual float calculateGrowthRate(Plant* plant) = 0;
    
private:
    /**
     * @brief Apply calculated growth to plant
     * @param plant Target plant
     * @param growth Amount of growth to apply
     */
    virtual void applyGrowth(Plant* plant, float growth) = 0;
};

/**
 * @class BoostedGrowthCycle
 * @brief Growth cycle with enhanced growth rate
 *
 * Applies a multiplier to normal growth rate for faster plant development.
 */
class BoostedGrowthCycle : public GrowthCycle {
protected:
    float calculateGrowthRate(Plant* plant) override;
    
private:
    void applyGrowth(Plant* plant, float growth) override;
    static const float BOOST_MULTIPLIER;
};

/**
 * @class NormalGrowthCycle
 * @brief Standard growth cycle with base growth rate
 *
 * Uses plant's natural growth rate without modification.
 */
class NormalGrowthCycle : public GrowthCycle {
protected:
    float calculateGrowthRate(Plant* plant) override;
    
private:
    void applyGrowth(Plant* plant, float growth) override;
};