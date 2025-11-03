#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"
<<<<<<< HEAD
=======

>>>>>>> origin/Frontend
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual bool isPatrol() const { return false; }
};

class WaterCommand : public Command {
public:
    void execute() override;
<<<<<<< HEAD
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
    

=======
    WaterCommand(Plant* plant, Greenhouse* gh); 
private:
    Plant* targetPlant;
    Greenhouse* subject; 
};

class FertilizeCommand : public Command {
public:
    void execute() override;
   
    FertilizeCommand(Plant* plant, Greenhouse* gh);
private:
    Plant* targetPlant;
    Greenhouse* subject; 
>>>>>>> origin/Frontend
};

class HarvestCommand : public Command {
public:
    void execute() override;
<<<<<<< HEAD
    HarvestCommand(Plant* plant);
    private:
    Plant* targetPlant;
=======
    HarvestCommand(Plant* plant, Greenhouse* gh);
private:
    Plant* targetPlant;
    Greenhouse* subject;
>>>>>>> origin/Frontend
};

class PatrolCommand : public Command {
public:
    void execute() override;
    PatrolCommand(){}
    bool isPatrol() const override { return true; }
<<<<<<< HEAD
    private:
=======
private:
>>>>>>> origin/Frontend
};

class ServeCommand : public Command {
public:
    void execute() override;
    ServeCommand(Customer* cust);
private:
    Customer* target;
};