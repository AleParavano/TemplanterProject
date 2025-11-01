#pragma once

#include "Plant.h"
#include <random>

class PlantFactory
{
public:
    PlantFactory() {}
    virtual ~PlantFactory() {}
    virtual Plant *produce() = 0;
};

class CarrotFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Carrot();
    }
};

class TomatoFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Tomato();
    }
};

class SunflowerFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Sunflower();
    }
};

class LettuceFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Lettuce();
    }
};

class PotatoFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Potato();
    }
};

class CucumberFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Cucumber();
    }
};

class PepperFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Pepper();
    }
};

class StrawberryFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Strawberry();
    }
};

class CornFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Corn();
    }
};

class PumpkinFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        return new Pumpkin();
    }
};

class RandomPlantFactory : public PlantFactory
{
public:
    Plant *produce() override
    {
        std::uniform_int_distribution<int> dist(0, 10);

        switch (dist(rng()))
        {
        case 0:
            return new Carrot();
            break;
        case 1:
            return new Tomato();
            break;
        case 2:
            return new Sunflower();
            break;
        case 3:
            return new Lettuce();
            break;
        case 4:
            return new Potato();
            break;
        case 5:
            return new Cucumber();
            break;
        case 6:
            return new Pepper();
            break;
        case 7:
            return new Strawberry();
            break;
        case 8:
            return new Corn();
            break;
        default:
            return new Pumpkin();
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