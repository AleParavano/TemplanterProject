#pragma once
#include <string>

class Plant;

class PlantState
{
public:
    PlantState();
    PlantState(float gr, float wa, float nu);
    PlantState(const PlantState& other); 
    virtual ~PlantState() = 0;
    
    virtual void handle(Plant* plant) = 0;
    virtual void tick(Plant* plant) = 0;
    virtual std::string getState() = 0;
    
    // Getters
    float getGrowth() const;
    float getWater() const;
    float getNutrients() const;
    
    // Setters
    void setGrowth(float g);
    void setWater(float w);
    void setNutrients(float n);
    
    // Resource management
    void consumeResources(float waterConsumption, float nutrientConsumption);
    void addWater(float amount);
    void addNutrients(float amount);
    
    // Growth application - called by GrowthCycle
    void applyGrowth(float growthAmount);
    
protected:
    float growth;
    float water;
    float nutrients;
    
    // Resource consumption rates per state
    virtual float getWaterConsumptionRate() const = 0;
    virtual float getNutrientConsumptionRate() const = 0;
    
    static const float SEED_TO_GROWING_THRESHOLD;
    static const float GROWING_TO_RIPE_THRESHOLD;
    static const float DEATH_WATER_THRESHOLD;
    static const float DEATH_NUTRIENT_THRESHOLD;
    static const float WATER_CONSUMPTION_RATE;
    static const float NUTRIENT_CONSUMPTION_RATE;
    static const float GROWTH_PER_TICK;

    friend class Plant;
};

class SeedState : public PlantState
{
public:
    SeedState();
    SeedState(float gr, float wa, float nu);
    SeedState(const SeedState& other);
    virtual ~SeedState();
    
    void handle(Plant* plant) override;
    void tick(Plant* plant) override;
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

class GrowingState : public PlantState
{
public:
    GrowingState();
    GrowingState(float gr, float wa, float nu);
    GrowingState(const GrowingState& other); 
    virtual ~GrowingState();
    
    void handle(Plant* plant) override;
    void tick(Plant* plant) override;
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

class RipeState : public PlantState
{
public:
    RipeState();
    RipeState(float gr, float wa, float nu);
    RipeState(const RipeState& other); 
    virtual ~RipeState();
    
    void handle(Plant* plant) override;
    void tick(Plant* plant) override;
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

class DeadState : public PlantState
{
public:
    DeadState();
    DeadState(float gr, float wa, float nu);
    DeadState(const DeadState& other);
    virtual ~DeadState();
    
    void handle(Plant* plant) override;
    void tick(Plant* plant) override;
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};
