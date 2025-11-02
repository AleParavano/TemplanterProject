#pragma once

#include "Plant.h"
#include "../PlantVisualStrategy.h"

class PlantFactory
{
public:
    PlantFactory() {}
    virtual ~PlantFactory() {}
    virtual Plant* produce() = 0;
};

class CarrotFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
    }
};

class TomatoFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
    }
};

class LettuceFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
    }
};

// --- You will need to complete the rest of these factories ---

class SunflowerFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
    }
};

class PotatoFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
    }
};

class CucumberFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
    }
};

class PepperFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Pepper(new PepperVisualStrategy(25.0f, 30.0f));
    }
};

class StrawberryFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
    }
};

class CornFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Corn(new CornVisualStrategy(20.0f, 55.0f));
    }
};

class PumpkinFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
    }
};