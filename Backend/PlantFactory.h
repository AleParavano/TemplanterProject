/**
 * @file PlantFactory.h
 * @brief Factory classes for producing Plant instances
 *
 * Provides concrete factories for creating specific plant types with
 * appropriate visual strategies.
 *
 * @pattern Factory Method - Plant creation
 * @pattern Strategy - Visual rendering
 */

#pragma once

#include "Plant.h"
#include <random>
#include "../Frontend/PlantVisualStrategy.h"

/**
 * @class PlantFactory
 * @brief Abstract base factory for creating plants
 */
class PlantFactory
{
public:
    PlantFactory() {}
    virtual ~PlantFactory() {}
    virtual Plant *produce() = 0;
};

/**
 * @class CarrotFactory
 * @brief Creates Carrot plants with appropriate visual strategy
 */
class CarrotFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
    }
};

/**
 * @class TomatoFactory
 * @brief Creates Tomato plants with appropriate visual strategy
 */
class TomatoFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
    }
};

/**
 * @class LettuceFactory
 * @brief Creates Lettuce plants with appropriate visual strategy
 */
class LettuceFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
    }
};

// --- You will need to complete the rest of these factories ---

/**
 * @class SunflowerFactory
 * @brief Creates Sunflower plants with appropriate visual strategy
 */
class SunflowerFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
    }
};

/**
 * @class PotatoFactory
 * @brief Creates Potato plants with appropriate visual strategy
 */
class PotatoFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
    }
};

/**
 * @class CucumberFactory
 * @brief Creates Cucumber plants with appropriate visual strategy
 */
class CucumberFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
    }
};

/**
 * @class PepperFactory
 * @brief Creates Pepper plants with appropriate visual strategy
 */
class PepperFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
    }
};

/**
 * @class StrawberryFactory
 * @brief Creates Strawberry plants with appropriate visual strategy
 */
class StrawberryFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
    }
};

/**
 * @class CornFactory
 * @brief Creates Corn plants with appropriate visual strategy
 */
class CornFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Corn(new CornVisualStrategy(20.0f, 55.0f));
    }
};

/**
 * @class PumpkinFactory
 * @brief Creates Pumpkin plants with appropriate visual strategy
 */
class PumpkinFactory : public PlantFactory
{
public:
    Plant* produce() override {
        return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
    }
};

/**
 * @class RandomPlantFactory
 * @brief Creates random plant types with weighted distribution
 *
 * Randomly selects and creates plants with appropriate visual strategies.
 * Uses seeded RNG for reproducible results.
 */
class RandomPlantFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        std::uniform_int_distribution<int> dist(0, 10);

        switch (dist(rng()))
        {
        case 0:
            return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
            break;
        case 1:
            return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
            break;
        case 2:
            return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
            break;
        case 3:
            return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
            break;
        case 4:
            return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
            break;
        case 5:
            return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
            break;
        case 6:
            return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
            break;
        case 7:
            return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
            break;
        case 8:
            return new Corn(new CornVisualStrategy(20.0f, 55.0f));
            break;
        default:
            return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
            break;
        }
    }

private:
    static std::mt19937 &rng()
    {
        static std::mt19937 engine{std::random_device{}()};
        return engine;
    }
};