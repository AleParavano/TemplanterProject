#pragma once
#include "Plant.h"
#include "Customer.h"
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class WaterCommand : public Command {
public:
    void execute() override;
    private:
    Plant* targetPlant;
};
class FertilizeCommand : public Command {
public:
    void execute() override;
    private:
    Plant* targetPlant;

};

class HarvestCommand : public Command {
public:
    void execute() override;
    private:
    Plant* targetPlant;
};

class PatrolCommand : public Command {
public:
    void execute() override;
    private:
    Plant* targetPlant;
};

class ServeCommand : public Command {
public:
    void execute() override;

private:
    Customer* target;
};