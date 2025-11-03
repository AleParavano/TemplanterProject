/**
 * @file GrowthCycle.h
 * @brief Plant growth cycle management declaration.
 * 
 * Defines the GrowthCycle class which handles plant growth stages
 * and growth requirements.
 */

// Forward declaration instead of include to avoid circular dependency
class Plant;

/**
 * @class GrowthCycle
 * @brief Manages plant growth stages and requirements.
 * 
 * Handles the progression of plant growth through various stages,
 * including timing and condition requirements for each stage.
 */
class GrowthCycle {
public:
    GrowthCycle();
    virtual ~GrowthCycle();
    void grow(Plant* plant, float deltaTime);
    
protected:
    virtual float calculateGrowthRate(Plant* plant) = 0;
    
private:
    virtual void applyGrowth(Plant* plant, float growth) = 0;
};

class BoostedGrowthCycle : public GrowthCycle {
protected:
    float calculateGrowthRate(Plant* plant) override;
    
private:
    void applyGrowth(Plant* plant, float growth) override;
    static const float BOOST_MULTIPLIER;
};

class NormalGrowthCycle : public GrowthCycle {
protected:
    float calculateGrowthRate(Plant* plant) override;
    
private:
    void applyGrowth(Plant* plant, float growth) override;
};