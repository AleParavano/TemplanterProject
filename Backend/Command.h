#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class WaterCommand : public Command {
public:
    void execute() override;
    WaterCommand(Plant* plant);
    private:
    Plant* targetPlant;
};
class FertilizeCommand : public Command {
public:
    void execute() override;
    FertilizeCommand(Plant* plant);
    private:
    Plant* targetPlant;
    

};

class HarvestCommand : public Command {
public:
    void execute() override;
    HarvestCommand(int plant, Greenhouse* greenhouse);
    private:
    int targetPlant;
    Greenhouse* greenhouse;
};

class PatrolCommand : public Command {
public:
    void execute() override;
    PatrolCommand(Plant* plant);
    private:
    Plant* targetPlant;
};

class ServeCommand : public Command {
public:
    void execute() override;
    ServeCommand(Customer* cust);
private:
    Customer* target;
};