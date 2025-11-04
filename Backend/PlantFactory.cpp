/**
 * @file PlantFactory.cpp
 * @brief Implementation of factory classes for creating plant objects.
 * @details Provides concrete factory implementations for all 10 plant types
 *          plus the RandomPlantFactory for dynamic plant creation.
 * 
 * @author Team Templation
 * @date November 2025
 */

#include "PlantFactory.h"
#include <random>

// ============================================================================
// CARROT FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Carrot plant.
 * 
 * Creates a new Carrot instance with CarrotVisualStrategy for rendering.
 * Carrot dimensions: 15x30 pixels
 * 
 * @return Pointer to newly allocated Carrot with CarrotVisualStrategy
 * @see Carrot
 * @see CarrotVisualStrategy
 */
Plant* CarrotFactory::produce() {
    return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
}

// ============================================================================
// TOMATO FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Tomato plant.
 * 
 * Creates a new Tomato instance with TomatoVisualStrategy for rendering.
 * Tomato dimensions: 25x25 pixels
 * 
 * @return Pointer to newly allocated Tomato with TomatoVisualStrategy
 * @see Tomato
 * @see TomatoVisualStrategy
 */
Plant* TomatoFactory::produce() {
    return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
}

// ============================================================================
// LETTUCE FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Lettuce plant.
 * 
 * Creates a new Lettuce instance with LettuceVisualStrategy for rendering.
 * Lettuce dimensions: 20x15 pixels
 * 
 * @return Pointer to newly allocated Lettuce with LettuceVisualStrategy
 * @see Lettuce
 * @see LettuceVisualStrategy
 */
Plant* LettuceFactory::produce() {
    return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
}

// ============================================================================
// SUNFLOWER FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Sunflower plant.
 * 
 * Creates a new Sunflower instance with SunflowerVisualStrategy for rendering.
 * Sunflower dimensions: 25x50 pixels (tall flower)
 * 
 * @return Pointer to newly allocated Sunflower with SunflowerVisualStrategy
 * @see Sunflower
 * @see SunflowerVisualStrategy
 */
Plant* SunflowerFactory::produce() {
    return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
}

// ============================================================================
// POTATO FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Potato plant.
 * 
 * Creates a new Potato instance with PotatoVisualStrategy for rendering.
 * Potato dimensions: 18x20 pixels
 * 
 * @return Pointer to newly allocated Potato with PotatoVisualStrategy
 * @see Potato
 * @see PotatoVisualStrategy
 */
Plant* PotatoFactory::produce() {
    return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
}

// ============================================================================
// CUCUMBER FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Cucumber plant.
 * 
 * Creates a new Cucumber instance with CucumberVisualStrategy for rendering.
 * Cucumber dimensions: 20x35 pixels (climbing vine)
 * 
 * @return Pointer to newly allocated Cucumber with CucumberVisualStrategy
 * @see Cucumber
 * @see CucumberVisualStrategy
 */
Plant* CucumberFactory::produce() {
    return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
}

// ============================================================================
// PEPPER FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Pepper plant.
 * 
 * Creates a new Pepper instance with PepperVisualStrategy for rendering.
 * Pepper dimensions: 25x30 pixels
 * 
 * @return Pointer to newly allocated Pepper with PepperVisualStrategy
 * @see Pepper
 * @see PepperVisualStrategy
 */
Plant* PepperFactory::produce() {
    return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
}

// ============================================================================
// STRAWBERRY FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Strawberry plant.
 * 
 * Creates a new Strawberry instance with StrawberryVisualStrategy for rendering.
 * Strawberry dimensions: 25x15 pixels (low-growing)
 * 
 * @return Pointer to newly allocated Strawberry with StrawberryVisualStrategy
 * @see Strawberry
 * @see StrawberryVisualStrategy
 */
Plant* StrawberryFactory::produce() {
    return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
}

// ============================================================================
// CORN FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Corn plant.
 * 
 * Creates a new Corn instance with CornVisualStrategy for rendering.
 * Corn dimensions: 20x55 pixels (tall grain crop)
 * 
 * @return Pointer to newly allocated Corn with CornVisualStrategy
 * @see Corn
 * @see CornVisualStrategy
 */
Plant* CornFactory::produce() {
    return new Corn(new CornVisualStrategy(20.0f, 55.0f));
}

// ============================================================================
// PUMPKIN FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Produces a Pumpkin plant.
 * 
 * Creates a new Pumpkin instance with PumpkinVisualStrategy for rendering.
 * Pumpkin dimensions: 40x30 pixels (large plant)
 * 
 * @return Pointer to newly allocated Pumpkin with PumpkinVisualStrategy
 * @see Pumpkin
 * @see PumpkinVisualStrategy
 */
Plant* PumpkinFactory::produce() {
    return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
}

// ============================================================================
// RANDOM PLANT FACTORY IMPLEMENTATION
// ============================================================================

/**
 * @brief Gets the static random number generator instance.
 * 
 * Returns a reference to a static Mersenne Twister RNG that is shared
 * across all RandomPlantFactory instances. The RNG is seeded once with
 * std::random_device to ensure randomness.
 * 
 * @return Reference to the static std::mt19937 RNG engine
 * 
 * @details
 * The RNG is created as a static variable within this function, ensuring:
 * - Only one instance is created (lazy initialization)
 * - The same RNG is used for all RandomPlantFactory instances
 * - Thread-safe in single-threaded contexts
 * - Seeded with random_device for unpredictable sequences
 */
std::mt19937& RandomPlantFactory::rng() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

/**
 * @brief Produces a random plant type.
 * 
 * Generates a random number (0-10) and creates the corresponding plant type.
 * Uses uniform distribution to ensure each plant type has equal probability.
 * 
 * @return Pointer to randomly chosen Plant type with appropriate visual strategy
 * 
 * @details
 * Distribution (11 outcomes):
 * - 0: Carrot
 * - 1: Tomato
 * - 2: Sunflower
 * - 3: Lettuce
 * - 4: Potato
 * - 5: Cucumber
 * - 6: Pepper
 * - 7: Strawberry
 * - 8: Corn
 * - 9: Pumpkin
 * - 10: Pumpkin (re-rolls to case 9)
 * 
 * Each call generates a fresh random value for variety.
 * 
 * @example
 * @code
 * RandomPlantFactory factory;
 * Plant* randomPlant = factory.produce();
 * // Could be any of 10 plant types with equal probability
 * @endcode
 * 
 * @see RandomFactory (for customer types)
 */
Plant* RandomPlantFactory::produce() {
    std::uniform_int_distribution<int> dist(0, 10);
    
    switch (dist(rng())) {
        case 0:
            return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
        case 1:
            return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
        case 2:
            return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
        case 3:
            return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
        case 4:
            return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
        case 5:
            return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
        case 6:
            return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
        case 7:
            return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
        case 8:
            return new Corn(new CornVisualStrategy(20.0f, 55.0f));
        default:
            return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
    }
}