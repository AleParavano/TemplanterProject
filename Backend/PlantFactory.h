#pragma once

#include "Plant.h"
#include <random>
#include "../Frontend/PlantVisualStrategy.h"

/**
 * @class PlantFactory
 * @brief The Abstract Factory (Creator) class in the Factory Method design pattern.
 * * It declares the interface for methods that return new Plant objects.
 */
class PlantFactory
{
public:
    /**
     * @brief Constructs a PlantFactory object.
     */
    PlantFactory() {}
    
    /**
     * @brief Virtual destructor for the PlantFactory class.
     */
    virtual ~PlantFactory() {}
    
    /**
     * @brief Pure virtual method for creating a Plant product.
     * * Concrete factories must implement this method to produce a specific plant type.
     * @return A pointer to the newly created Plant object.
     */
    virtual Plant *produce() = 0;
};

/**
 * @class CarrotFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Carrot.
 */
class CarrotFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Carrot plant with its corresponding CarrotVisualStrategy.
     * @return A pointer to a new Carrot object.
     */
    Plant* produce() override {
        return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
    }
};

/**
 * @class TomatoFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Tomato.
 */
class TomatoFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Tomato plant with its corresponding TomatoVisualStrategy.
     * @return A pointer to a new Tomato object.
     */
    Plant* produce() override {
        return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
    }
};

/**
 * @class LettuceFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Lettuce.
 */
class LettuceFactory : public PlantFactory {
public:
    /**
     * @brief Creates a new Lettuce plant with its corresponding LettuceVisualStrategy.
     * @return A pointer to a new Lettuce object.
     */
    Plant* produce() override {
        return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
    }
};

// --- You will need to complete the rest of these factories ---

/**
 * @class SunflowerFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Sunflower.
 */
class SunflowerFactory : public PlantFactory {
public:
    /**
     * @brief Creates a new Sunflower plant with its corresponding SunflowerVisualStrategy.
     * @return A pointer to a new Sunflower object.
     */
    Plant* produce() override {
        return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
    }
};

/**
 * @class PotatoFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Potato.
 */
class PotatoFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Potato plant with its corresponding PotatoVisualStrategy.
     * @return A pointer to a new Potato object.
     */
    Plant* produce() override {
        return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
    }
};

/**
 * @class CucumberFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Cucumber.
 */
class CucumberFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Cucumber plant with its corresponding CucumberVisualStrategy.
     * @return A pointer to a new Cucumber object.
     */
    Plant* produce() override {
        return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
    }
};

/**
 * @class PepperFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Pepper.
 */
class PepperFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Pepper plant with its corresponding PepperVisualStrategy.
     * @return A pointer to a new Pepper object.
     */
    Plant* produce() override {
        return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
    }
};

/**
 * @class StrawberryFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Strawberry.
 */
class StrawberryFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Strawberry plant with its corresponding StrawberryVisualStrategy.
     * @return A pointer to a new Strawberry object.
     */
    Plant* produce() override {
        return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
    }
};

/**
 * @class CornFactory
 * @brief A Concrete Factory that implements the Factory Method to produce Corn.
 */
class CornFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Corn plant with its corresponding CornVisualStrategy.
     * @return A pointer to a new Corn object.
     */
    Plant* produce() override {
        return new Corn(new CornVisualStrategy(20.0f, 55.0f));
    }
};

/**
 * @class PumpkinFactory
 * @brief A Concrete Factory that implements the Factory Method to produce a Pumpkin.
 */
class PumpkinFactory : public PlantFactory
{
public:
    /**
     * @brief Creates a new Pumpkin plant with its corresponding PumpkinVisualStrategy.
     * @return A pointer to a new Pumpkin object.
     */
    Plant* produce() override {
        return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
    }
};

/**
 * @class RandomPlantFactory
 * @brief A specialized Factory that randomly selects and produces one of the available plant types.
 */
class RandomPlantFactory : public PlantFactory
{
public:
    /**
     * @brief Randomly selects and produces a new Plant of a different type, each with its appropriate strategy.
     * @return A pointer to a randomly generated Plant object.
     */
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
    /**
     * @brief Returns a reference to the static random number generator engine.
     * @return A reference to the static std::mt19937 engine.
     */
    static std::mt19937 &rng()
    {
        static std::mt19937 engine{std::random_device{}()};
        return engine;
    }
};
