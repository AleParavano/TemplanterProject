#pragma once

#include <memory>
#include "Plant.h"

class PlantFactory
{
    public:
    PlantFactory();
    virtual ~PlantFactory();
    virtual std::unique_ptr<Plant> produce() = 0;
};

class CarrotFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Carrot>();
    }
};

class TomatoFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Tomato>();
    }
};

class SunflowerFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Sunflower>();
    }
};

class LettuceFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Lettuce>();
    }
};

class PotatoFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Potato>();
    }
};

class CucumberFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Cucumber>();
    }
};

class PepperFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Pepper>();
    }
};

class StrawberryFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Strawberry>();
    }
};

class CornFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Corn>();
    }
};

class PumpkinFactory : public PlantFactory {
public:
    std::unique_ptr<Plant> produce() override {
        return std::make_unique<Pumpkin>();
    }
};
