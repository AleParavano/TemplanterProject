/**
 * @file PlantFactory.h
 * @brief Factory pattern implementation for creating plant objects.
 * @details Provides factories for creating different plant types with visual strategies.
 *          Includes a RandomPlantFactory for spawning random varieties.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 * @see PlantVisualStrategy
 */

#pragma once

#include "Plant.h"
#include <random>
#include "../Frontend/PlantVisualStrategy.h"

/**
 * @class PlantFactory
 * @brief Abstract factory for plant creation.
 * 
 * Defines the interface for concrete plant factories.
 * Each factory creates a specific plant type with appropriate visual strategy.
 * 
 * @par Design Pattern: Factory
 * Encapsulates plant creation logic. Subclasses specify which plant type
 * to create and which visual strategy to use.
 */
class PlantFactory
{
public:
    /**
     * @brief Constructor.
     */
    PlantFactory() {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~PlantFactory() {}

    /**
     * @brief Creates and returns a plant.
     * @return Pointer to a newly allocated Plant subclass
     */
    virtual Plant *produce() = 0;
};

/**
 * @class CarrotFactory
 * @brief Factory for creating Carrot plants.
 * @details Creates Carrot with dimensions 15x30
 */
class CarrotFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Carrot plant.
     * @return Newly allocated Carrot with CarrotVisualStrategy
     */
    Plant* produce() override {
        return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
    }
};

/**
 * @class TomatoFactory
 * @brief Factory for creating Tomato plants.
 * @details Creates Tomato with dimensions 25x25
 */
class TomatoFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Tomato plant.
     * @return Newly allocated Tomato with TomatoVisualStrategy
     */
    Plant* produce() override {
        return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
    }
};

/**
 * @class LettuceFactory
 * @brief Factory for creating Lettuce plants.
 * @details Creates Lettuce with dimensions 20x15
 */
class LettuceFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Lettuce plant.
     * @return Newly allocated Lettuce with LettuceVisualStrategy
     */
    Plant* produce() override {
        return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
    }
};

/**
 * @class SunflowerFactory
 * @brief Factory for creating Sunflower plants.
 * @details Creates Sunflower with dimensions 25x50
 */
class SunflowerFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Sunflower plant.
     * @return Newly allocated Sunflower with SunflowerVisualStrategy
     */
    Plant* produce() override {
        return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
    }
};

/**
 * @class PotatoFactory
 * @brief Factory for creating Potato plants.
 * @details Creates Potato with dimensions 18x20
 */
class PotatoFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Potato plant.
     * @return Newly allocated Potato with PotatoVisualStrategy
     */
    Plant* produce() override {
        return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
    }
};

/**
 * @class CucumberFactory
 * @brief Factory for creating Cucumber plants.
 * @details Creates Cucumber with dimensions 20x35
 */
class CucumberFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Cucumber plant.
     * @return Newly allocated Cucumber with CucumberVisualStrategy
     */
    Plant* produce() override {
        return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
    }
};

/**
 * @class PepperFactory
 * @brief Factory for creating Pepper plants.
 * @details Creates Pepper with dimensions 25x30
 */
class PepperFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Pepper plant.
     * @return Newly allocated Pepper with PepperVisualStrategy
     */
    Plant* produce() override {
        return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
    }
};

/**
 * @class StrawberryFactory
 * @brief Factory for creating Strawberry plants.
 * @details Creates Strawberry with dimensions 25x15
 */
class StrawberryFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Strawberry plant.
     * @return Newly allocated Strawberry with StrawberryVisualStrategy
     */
    Plant* produce() override {
        return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
    }
};

/**
 * @class CornFactory
 * @brief Factory for creating Corn plants.
 * @details Creates Corn with dimensions 20x55
 */
class CornFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Corn plant.
     * @return Newly allocated Corn with CornVisualStrategy
     */
    Plant* produce() override {
        return new Corn(new CornVisualStrategy(20.0f, 55.0f));
    }
};

/**
 * @class PumpkinFactory
 * @brief Factory for creating Pumpkin plants.
 * @details Creates Pumpkin with dimensions 40x30
 */
class PumpkinFactory : public PlantFactory {
public:
    /**
     * @brief Produces a Pumpkin plant.
     * @return Newly allocated Pumpkin with PumpkinVisualStrategy
     */
    Plant* produce() override {
        return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
    }
};

/**
 * @class RandomPlantFactory
 * @brief Factory for creating random plant types.
 * 
 * Creates one of 11 plant types with equal probability.
 * Uses Mersenne Twister RNG for randomness.
 * 
 * @par Design Pattern: Factory
 * Extends the Factory pattern with randomization, allowing dynamic
 * creation of varied plant types without specifying exact type.
 * 
 * @par Probability Distribution
 * Each plant type has equal probability of being created:
 * - Carrot: ~9.1%
 * - Tomato: ~9.1%
 * - Sunflower: ~9.1%
 * - Lettuce: ~9.1%
 * - Potato: ~9.1%
 * - Cucumber: ~9.1%
 * - Pepper: ~9.1%
 * - Strawberry: ~9.1%
 * - Corn: ~9.1%
 * - Pumpkin: ~9.1%
 * - (repeats randomly)
 */
class RandomPlantFactory : public PlantFactory {
public:
    /**
     * @brief Produces a random plant.
     * @return Random plant type (0-10 equally distributed)
     * 
     * @details Generates random number 0-10 and creates corresponding plant.
     *         Uses static Mersenne Twister for consistent randomness.
     */
    Plant *produce() override;

private:
    /**
     * @brief Gets the static RNG instance.
     * @return Reference to the global Mersenne Twister engine
     * 
     * @details Static instance ensures same RNG across all calls.
     *         Seeded with random_device for variation.
     */
    static std::mt19937 &rng();
};