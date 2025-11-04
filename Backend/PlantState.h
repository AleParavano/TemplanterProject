#pragma once
#include <string>

/**
 * @class Plant
 * @brief Forward declaration for the Context class (Plant).
 */
class Plant;

/**
 * @class PlantState
 * @brief The Abstract State class in the State design pattern. It defines the interface 
 * for encapsulating the behavior associated with a particular state of the Plant.
 * * This class manages the core metrics of a plant (growth, water, nutrients) and defines 
 * the virtual interface for state-specific operations like handling state transitions and ticking.
 */
class PlantState
{
public:
    /**
     * @brief Default constructor for PlantState, initializes metrics to zero.
     */
    PlantState();
    
    /**
     * @brief Constructs a PlantState object with specific metric values.
     * @param gr The initial growth progress (0.0 to 1.0).
     * @param wa The initial water level.
     * @param nu The initial nutrient level.
     */
    PlantState(float gr, float wa, float nu);
    
    /**
     * @brief Copy constructor for PlantState.
     * @param other The PlantState object to copy.
     */
    PlantState(const PlantState& other); 
    
    /**
     * @brief Pure virtual destructor, making PlantState an abstract class.
     */
    virtual ~PlantState() = 0;
    
    /**
     * @brief Pure virtual method to handle state-specific conditions and potentially trigger transitions.
     * * This method is the core of the State pattern, allowing states to change the Plant's state.
     * @param plant A pointer to the Plant context object.
     */
    virtual void handle(Plant* plant) = 0;
    
    /**
     * @brief Pure virtual method for resource consumption and growth logic specific to the state during a time tick.
     * @param plant A pointer to the Plant context object.
     */
    virtual void tick(Plant* plant) = 0;
    
    /**
     * @brief Pure virtual method that returns the name of the current state.
     * @return The state name as a string.
     */
    virtual std::string getState() = 0;
    
    // Getters
    /**
     * @brief Gets the current growth progress (0.0 to 1.0).
     * @return The growth progress as a float.
     */
    float getGrowth() const;
    
    /**
     * @brief Gets the current water level.
     * @return The water level as a float.
     */
    float getWater() const;
    
    /**
     * @brief Gets the current nutrient level.
     * @return The nutrient level as a float.
     */
    float getNutrients() const;
    
    // Setters
    /**
     * @brief Sets the growth progress.
     * @param g The new growth progress value.
     */
    void setGrowth(float g);
    
    /**
     * @brief Sets the water level.
     * @param w The new water level value.
     */
    void setWater(float w);
    
    /**
     * @brief Sets the nutrient level.
     * @param n The new nutrient level value.
     */
    void setNutrients(float n);
    
    // Resource management
    /**
     * @brief Decreases water and nutrients based on consumption rates.
     * @param waterConsumption The amount of water to consume.
     * @param nutrientConsumption The amount of nutrients to consume.
     */
    void consumeResources(float waterConsumption, float nutrientConsumption);
    
    /**
     * @brief Increases the water level.
     * @param amount The amount of water to add.
     */
    void addWater(float amount);
    
    /**
     * @brief Increases the nutrient level.
     * @param amount The amount of nutrients to add.
     */
    void addNutrients(float amount);
    
    // Growth application - called by GrowthCycle
    /**
     * @brief Increases the plant's growth progress.
     * @param growthAmount The amount to increase growth by.
     */
    void applyGrowth(float growthAmount);
    
protected:
    /** @brief Current growth progress (0.0 to 1.0). */
    float growth;
    
    /** @brief Current water level. */
    float water;
    
    /** @brief Current nutrient level. */
    float nutrients;
    
    // Resource consumption rates per state
    /**
     * @brief Pure virtual method to get the state-specific water consumption rate.
     * @return The water consumption rate as a float.
     */
    virtual float getWaterConsumptionRate() const = 0;
    
    /**
     * @brief Pure virtual method to get the state-specific nutrient consumption rate.
     * @return The nutrient consumption rate as a float.
     */
    virtual float getNutrientConsumptionRate() const = 0;
    
    /** @brief Static threshold for transition from SeedState to GrowingState. */
    static const float SEED_TO_GROWING_THRESHOLD;
    
    /** @brief Static threshold for transition from GrowingState to RipeState. */
    static const float GROWING_TO_RIPE_THRESHOLD;
    
    /** @brief Static water level below which the plant transitions to DeadState. */
    static const float DEATH_WATER_THRESHOLD;
    
    /** @brief Static nutrient level below which the plant transitions to DeadState. */
    static const float DEATH_NUTRIENT_THRESHOLD;
    
    /** @brief Static default water consumption rate. */
    static const float WATER_CONSUMPTION_RATE;
    
    /** @brief Static default nutrient consumption rate. */
    static const float NUTRIENT_CONSUMPTION_RATE;
    
    /** @brief Static default growth applied per time tick. */
    static const float GROWTH_PER_TICK;

    /** @brief Grants the Plant class access to protected members for state transitions. */
    friend class Plant;
};

/**
 * @class SeedState
 * @brief Concrete State representing the initial, dormant phase of the plant's life cycle.
 */
class SeedState : public PlantState
{
public:
    /** @brief Default constructor. */
    SeedState();
    
    /** @brief Constructs SeedState with metrics. */
    SeedState(float gr, float wa, float nu);
    
    /** @brief Copy constructor. */
    SeedState(const SeedState& other);
    
    /** @brief Destructor. */
    virtual ~SeedState();
    
    /** @brief Handles transition logic: checks if growth is sufficient to become GrowingState. */
    void handle(Plant* plant) override;
    
    /** @brief Executes resource consumption and potential growth for the SeedState. */
    void tick(Plant* plant) override;
    
    /** @brief Returns the state name "Seed". */
    std::string getState() override;
    
protected:
    /** @brief Returns the water consumption rate for the Seed state. */
    float getWaterConsumptionRate() const override;
    
    /** @brief Returns the nutrient consumption rate for the Seed state. */
    float getNutrientConsumptionRate() const override;
};

/**
 * @class GrowingState
 * @brief Concrete State representing the active growth phase of the plant.
 */
class GrowingState : public PlantState
{
public:
    /** @brief Default constructor. */
    GrowingState();
    
    /** @brief Constructs GrowingState with metrics. */
    GrowingState(float gr, float wa, float nu);
    
    /** @brief Copy constructor. */
    GrowingState(const GrowingState& other); 
    
    /** @brief Destructor. */
    virtual ~GrowingState();
    
    /** @brief Handles transition logic: checks for death condition or if growth is sufficient to become RipeState. */
    void handle(Plant* plant) override;
    
    /** @brief Executes resource consumption and growth logic for the GrowingState. */
    void tick(Plant* plant) override;
    
    /** @brief Returns the state name "Growing". */
    std::string getState() override;
    
protected:
    /** @brief Returns the water consumption rate for the Growing state. */
    float getWaterConsumptionRate() const override;
    
    /** @brief Returns the nutrient consumption rate for the Growing state. */
    float getNutrientConsumptionRate() const override;
};

/**
 * @class RipeState
 * @brief Concrete State representing the mature, ready-to-harvest phase of the plant.
 */
class RipeState : public PlantState
{
public:
    /** @brief Default constructor. */
    RipeState();
    
    /** @brief Constructs RipeState with metrics. */
    RipeState(float gr, float wa, float nu);
    
    /** @brief Copy constructor. */
    RipeState(const RipeState& other); 
    
    /** @brief Destructor. */
    virtual ~RipeState();
    
    /** @brief Handles transition logic: checks for death condition. */
    void handle(Plant* plant) override;
    
    /** @brief Executes resource consumption logic (no growth) for the RipeState. */
    void tick(Plant* plant) override;
    
    /** @brief Returns the state name "Ripe". */
    std::string getState() override;
    
protected:
    /** @brief Returns the water consumption rate for the Ripe state. */
    float getWaterConsumptionRate() const override;
    
    /** @brief Returns the nutrient consumption rate for the Ripe state. */
    float getNutrientConsumptionRate() const override;
};

/**
 * @class DeadState
 * @brief Concrete State representing the deceased phase of the plant.
 */
class DeadState : public PlantState
{
public:
    /** @brief Default constructor. */
    DeadState();
    
    /** @brief Constructs DeadState with metrics. */
    DeadState(float gr, float wa, float nu);
    
    /** @brief Copy constructor. */
    DeadState(const DeadState& other);
    
    /** @brief Destructor. */
    virtual ~DeadState();
    
    /** @brief Handles transition logic: the plant remains dead, no transitions occur from this state. */
    void handle(Plant* plant) override;
    
    /** @brief Executes resource consumption logic: no consumption occurs in the DeadState. */
    void tick(Plant* plant) override;
    
    /** @brief Returns the state name "Dead". */
    std::string getState() override;
    
protected:
    /** @brief Returns the water consumption rate for the Dead state (typically zero). */
    float getWaterConsumptionRate() const override;
    
    /** @brief Returns the nutrient consumption rate for the Dead state (typically zero). */
    float getNutrientConsumptionRate() const override;
};

