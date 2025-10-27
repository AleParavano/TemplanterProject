#pragma once

#include "Plant.h"

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
        return new Carrot();
    }
};

class TomatoFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Tomato();
    }
};

class SunflowerFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Sunflower();
    }
};

class LettuceFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Lettuce();
    }
};

class PotatoFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Potato();
    }
};

class CucumberFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Cucumber();
    }
};

class PepperFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Pepper();
    }
};

class StrawberryFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Strawberry();
    }
};

class CornFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Corn();
    }
};

class PumpkinFactory : public PlantFactory {
public:
    Plant* produce() override {
        return new Pumpkin();
    }
};
