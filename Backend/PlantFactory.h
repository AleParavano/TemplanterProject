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
class PlantFactory {
public:
    PlantFactory() {}
    virtual ~PlantFactory() {}
    virtual Plant *produce() = 0;
};

/**
 * @class CarrotFactory
 * @brief Factory for creating Carrot plants.
 * @details Creates Carrot with dimensions 15x30
 */
class CarrotFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class TomatoFactory
 * @brief Factory for creating Tomato plants.
 * @details Creates Tomato with dimensions 25x25
 */
class TomatoFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class LettuceFactory
 * @brief Factory for creating Lettuce plants.
 * @details Creates Lettuce with dimensions 20x15
 */
class LettuceFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class SunflowerFactory
 * @brief Factory for creating Sunflower plants.
 * @details Creates Sunflower with dimensions 25x50
 */
class SunflowerFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class PotatoFactory
 * @brief Factory for creating Potato plants.
 * @details Creates Potato with dimensions 18x20
 */
class PotatoFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class CucumberFactory
 * @brief Factory for creating Cucumber plants.
 * @details Creates Cucumber with dimensions 20x35
 */
class CucumberFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class PepperFactory
 * @brief Factory for creating Pepper plants.
 * @details Creates Pepper with dimensions 25x30
 */
class PepperFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class StrawberryFactory
 * @brief Factory for creating Strawberry plants.
 * @details Creates Strawberry with dimensions 25x15
 */
class StrawberryFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class CornFactory
 * @brief Factory for creating Corn plants.
 * @details Creates Corn with dimensions 20x55
 */
class CornFactory : public PlantFactory {
public:
    Plant* produce() override;
};

/**
 * @class PumpkinFactory
 * @brief Factory for creating Pumpkin plants.
 * @details Creates Pumpkin with dimensions 40x30
 */
class PumpkinFactory : public PlantFactory {
public:
    Plant* produce() override;
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
 */
class RandomPlantFactory : public PlantFactory {
public:
    Plant *produce() override;

private:
    static std::mt19937 &rng();
};