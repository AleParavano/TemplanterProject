/**
 * @file PlantState.h
 * @brief State pattern implementation for plant lifecycle management.
 * @details Defines the state machine for plants progressing through Seed, Growing,
 *          Ripe, and Dead states with resource consumption and transitions.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 */

#pragma once
#include <string>

// Forward declaration
/**
 * @class Plant
 * @brief Forward declaration of Plant class.
 */
class Plant;

/**
 * @class PlantState
 * @brief Abstract base class for plant lifecycle states.
 * 
 * PlantState implements the State pattern for plant lifecycle management.
 * Different states handle:
 * - Resource consumption (water, nutrients)
 * - Growth progression
 * - State transitions
 * - Death conditions
 * 
 * @par Design Pattern: State
 * Encapsulates state-specific behavior for plants. Each state defines how the plant
 * consumes resources and when to transition to the next state.
 * 
 * @par State Lifecycle
 * ```
 * Seed (0-25%) --> Growing (25-100%) --> Ripe (100%+)
 *   |                   |
 *   +----> Dead <-------+
 * ```
 * 
 * @par Resource Management
 * Each state consumes resources at different rates:
 * - Seed: 50% consumption (vulnerable phase)
 * - Growing: 100% consumption (active growth)
 * - Ripe: 30% consumption (stable, ready for harvest)
 * - Dead: 0% consumption (irreversible)
 * 
 * @par Thresholds (in % growth)
 * - SEED_TO_GROWING_THRESHOLD: 25%
 * - GROWING_TO_RIPE_THRESHOLD: 100%
 * - DEATH_WATER_THRESHOLD: 0%
 * - DEATH_NUTRIENT_THRESHOLD: 0%
 * 
 * @see SeedState
 * @see GrowingState
 * @see RipeState
 * @see DeadState
 */
class PlantState
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes state with default values (0% growth, 100% resources)
     */
    PlantState();

    /**
     * @brief Constructor with initial resource values.
     * @param gr Initial growth percentage
     * @param wa Initial water percentage
     * @param nu Initial nutrient percentage
     */
    PlantState(float gr, float wa, float nu);

    /**
     * @brief Copy constructor.
     * @param other Reference to another PlantState to copy
     */
    PlantState(const PlantState& other); 

    /**
     * @brief Pure virtual destructor.
     * @details Ensures proper cleanup of derived state objects
     */
    virtual ~PlantState() = 0;
    
    // State machine methods
    
    /**
     * @brief Handles state-specific logic and transitions.
     * @param plant Pointer to the plant whose state is being managed
     * 
     * @details Pure virtual method. Each state checks:
     *         - Death conditions (no water/nutrients)
     *         - Transition conditions (growth thresholds)
     *         - Special conditions (over-ripening)
     * 
     * @post Plant state may change if transition is needed
     */
    virtual void handle(Plant* plant) = 0;

    /**
     * @brief Advances plant state by one game tick.
     * @param plant Pointer to the plant to update
     * 
     * @details Called each game cycle. Typically:
     *         1. Consumes resources
     *         2. Logs warnings if resources are low
     *         3. Calls handle() for state transitions
     * 
     * @post Resources are consumed
     * @post Plant may transition to next state
     */
    virtual void tick(Plant* plant) = 0;

    /**
     * @brief Gets the current state identifier.
     * @return String name: "Seed", "Growing", "Ripe", or "Dead"
     */
    virtual std::string getState() = 0;
    
    // Resource accessors
    
    /**
     * @brief Gets the current growth percentage.
     * @return Growth value (0-100+, uncapped for overgrowth detection)
     */
    float getGrowth() const;

    /**
     * @brief Gets the current water percentage.
     * @return Water level (0-100)
     */
    float getWater() const;

    /**
     * @brief Gets the current nutrient percentage.
     * @return Nutrient level (0-100)
     */
    float getNutrients() const;
    
    // Resource setters
    
    /**
     * @brief Sets the growth percentage directly.
     * @param g New growth value (automatically clamped to 0+)
     */
    void setGrowth(float g);

    /**
     * @brief Sets the water percentage directly.
     * @param w New water value (automatically clamped to 0+)
     */
    void setWater(float w);

    /**
     * @brief Sets the nutrient percentage directly.
     * @param n New nutrient value (automatically clamped to 0+)
     */
    void setNutrients(float n);
    
    // Resource management
    
    /**
     * @brief Consumes resources each tick.
     * @param waterConsumption Water to consume
     * @param nutrientConsumption Nutrients to consume
     * 
     * @details Called by tick() to consume resources based on state.
     *         Values are clamped to prevent negative resources.
     * 
     * @post Water and nutrients decrease (minimum 0)
     */
    void consumeResources(float waterConsumption, float nutrientConsumption);

    /**
     * @brief Adds water to the plant.
     * @param amount Water to add (capped at 100%)
     * 
     * @post Water level increases (maximum 100)
     */
    void addWater(float amount);

    /**
     * @brief Adds nutrients to the plant.
     * @param amount Nutrients to add (capped at 100%)
     * 
     * @post Nutrient level increases (maximum 100)
     */
    void addNutrients(float amount);
    
    /**
     * @brief Applies growth from growth cycle.
     * @param growthAmount Raw growth amount (typically 0-2.0f per tick)
     * 
     * @details Called by GrowthCycle::grow() to update growth progress.
     *         Growth is capped at GROWING_TO_RIPE_THRESHOLD (100%).
     * 
     * @post Growth value increases (maximum 100%)
     */
    void applyGrowth(float growthAmount);
    
protected:
    float growth;       ///< Current growth percentage (0-100+)
    float water;        ///< Current water percentage (0-100)
    float nutrients;    ///< Current nutrient percentage (0-100)
    
    // Pure virtual methods for resource consumption rates
    
    /**
     * @brief Gets the water consumption rate for this state.
     * @return Water to consume per tick (varies by state)
     */
    virtual float getWaterConsumptionRate() const = 0;

    /**
     * @brief Gets the nutrient consumption rate for this state.
     * @return Nutrients to consume per tick (varies by state)
     */
    virtual float getNutrientConsumptionRate() const = 0;
    
    // State transition thresholds (constant across all states)
    static const float SEED_TO_GROWING_THRESHOLD;        ///< 25% growth
    static const float GROWING_TO_RIPE_THRESHOLD;        ///< 100% growth
    static const float DEATH_WATER_THRESHOLD;            ///< 0% water
    static const float DEATH_NUTRIENT_THRESHOLD;         ///< 0% nutrients
    static const float WATER_CONSUMPTION_RATE;           ///< Base consumption (2.0 per tick)
    static const float NUTRIENT_CONSUMPTION_RATE;        ///< Base consumption (1.0 per tick)
    static const float GROWTH_PER_TICK;                  ///< Base growth (3.0 per tick)

    friend class Plant;
};

/**
 * @class SeedState
 * @brief Initial plant state - germination phase.
 * 
 * The Seed state represents plant germination and early root development.
 * 
 * @par Characteristics
 * - Growth Range: 0-25%
 * - Water Consumption: 50% of normal (1.0 per tick)
 * - Nutrient Consumption: 50% of normal (0.5 per tick)
 * - Death Condition: Water or nutrients reach 0%
 * - Transition: Automatic at 25% growth to Growing
 * 
 * @par Gameplay
 * Seeds are vulnerable and require careful monitoring.
 * If they run out of resources before reaching 25% growth, they die.
 */
class SeedState : public PlantState
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes with 0% growth, 100% water/nutrients
     */
    SeedState();

    /**
     * @brief Constructor with initial values.
     * @param gr Initial growth (typically 0%)
     * @param wa Initial water (typically 100%)
     * @param nu Initial nutrients (typically 100%)
     */
    SeedState(float gr, float wa, float nu);

    /**
     * @brief Copy constructor.
     * @param other Reference to another SeedState
     */
    SeedState(const SeedState& other);

    /**
     * @brief Destructor.
     */
    virtual ~SeedState();
    
    /**
     * @brief Handles seed-phase logic and Seed->Growing transition.
     * @param plant Pointer to the plant
     */
    void handle(Plant* plant) override;

    /**
     * @brief Advances seed by one tick.
     * @param plant Pointer to the plant
     */
    void tick(Plant* plant) override;

    /**
     * @brief Returns "Seed".
     */
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

/**
 * @class GrowingState
 * @brief Active growth phase.
 * 
 * The Growing state represents active plant development and biomass accumulation.
 * 
 * @par Characteristics
 * - Growth Range: 25-100%
 * - Water Consumption: 100% of normal (2.0 per tick)
 * - Nutrient Consumption: 100% of normal (1.0 per tick)
 * - Death Condition: Water or nutrients reach 0%
 * - Transition: Automatic at 100% growth to Ripe
 * 
 * @par Gameplay
 * Growing plants require consistent care. This is the critical phase for
 * worker intervention (watering, fertilizing).
 */
class GrowingState : public PlantState
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes with 25% growth (minimum for this state), 100% resources
     */
    GrowingState();

    /**
     * @brief Constructor with initial values.
     * @param gr Initial growth (typically 25%+)
     * @param wa Initial water (typically 100%)
     * @param nu Initial nutrients (typically 100%)
     */
    GrowingState(float gr, float wa, float nu);

    /**
     * @brief Copy constructor.
     * @param other Reference to another GrowingState
     */
    GrowingState(const GrowingState& other);

    /**
     * @brief Destructor.
     */
    virtual ~GrowingState();
    
    /**
     * @brief Handles growing-phase logic and Growing->Ripe transition.
     * @param plant Pointer to the plant
     */
    void handle(Plant* plant) override;

    /**
     * @brief Advances growing plant by one tick.
     * @param plant Pointer to the plant
     */
    void tick(Plant* plant) override;

    /**
     * @brief Returns "Growing".
     */
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

/**
 * @class RipeState
 * @brief Mature, harvest-ready phase.
 * 
 * The Ripe state represents a mature plant ready for harvest or natural decay.
 * 
 * @par Characteristics
 * - Growth Range: 100%+ (capped visually at 100%)
 * - Water Consumption: 30% of normal (0.6 per tick)
 * - Nutrient Consumption: 30% of normal (0.3 per tick)
 * - Death Condition: Water/nutrients reach 0%, or growth exceeds 150%
 * - Can be harvested at any time in this state
 * 
 * @par Gameplay
 * Ripe plants are ready for sale. If left unharvested, they can become
 * overripe and die (encouraging timely harvesting).
 */
class RipeState : public PlantState
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes with 100% growth, 100% resources
     */
    RipeState();

    /**
     * @brief Constructor with initial values.
     * @param gr Initial growth (typically 100%)
     * @param wa Initial water (typically 100%)
     * @param nu Initial nutrients (typically 100%)
     */
    RipeState(float gr, float wa, float nu);

    /**
     * @brief Copy constructor.
     * @param other Reference to another RipeState
     */
    RipeState(const RipeState& other);

    /**
     * @brief Destructor.
     */
    virtual ~RipeState();
    
    /**
     * @brief Handles ripe-phase logic and potential Ripe->Dead transition.
     * @param plant Pointer to the plant
     */
    void handle(Plant* plant) override;

    /**
     * @brief Advances ripe plant by one tick.
     * @param plant Pointer to the plant
     */
    void tick(Plant* plant) override;

    /**
     * @brief Returns "Ripe".
     */
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};

/**
 * @class DeadState
 * @brief Terminal state - plant cannot recover.
 * 
 * The Dead state represents plant death. This is irreversible.
 * 
 * @par Characteristics
 * - Growth: Slowly decreases (visual decay)
 * - Water Consumption: 0%
 * - Nutrient Consumption: 0%
 * - No transitions possible (terminal state)
 * - Cannot be harvested or recovered
 * 
 * @par Gameplay
 * Dead plants should be removed and replaced. They occupy greenhouse space
 * without producing value.
 */
class DeadState : public PlantState
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes with 0% for all values
     */
    DeadState();

    /**
     * @brief Constructor with initial values.
     * @param gr Initial growth (should be 0%)
     * @param wa Initial water (should be 0%)
     * @param nu Initial nutrients (should be 0%)
     */
    DeadState(float gr, float wa, float nu);

    /**
     * @brief Copy constructor.
     * @param other Reference to another DeadState
     */
    DeadState(const DeadState& other);

    /**
     * @brief Destructor.
     */
    virtual ~DeadState();
    
    /**
     * @brief No-op for dead plants (no transitions possible).
     * @param plant Pointer to the plant (unused)
     */
    void handle(Plant* plant) override;

    /**
     * @brief Slowly decays dead plant.
     * @param plant Pointer to the plant
     * 
     * @details Slightly decreases growth for visual decay effect.
     */
    void tick(Plant* plant) override;

    /**
     * @brief Returns "Dead".
     */
    std::string getState() override;
    
protected:
    float getWaterConsumptionRate() const override;
    float getNutrientConsumptionRate() const override;
};