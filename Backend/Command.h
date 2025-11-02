#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual bool isPatrol() const { return false; }
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
    HarvestCommand(Plant* plant);
    private:
    Plant* targetPlant;
};

class PatrolCommand : public Command {
public:
    void execute() override;
    PatrolCommand(){}
    bool isPatrol() const override { return true; }
    private:
};

class ServeCommand : public Command {
public:
    void execute() override;
    ServeCommand(Customer* cust);
private:
    Customer* target;
};