/**
 * @file Command.h
 * @brief Declaration of Command interface and concrete command classes.
 * 
 * This file defines the Command interface and various concrete commands for worker actions.
 * Commands encapsulate requests as objects, allowing workers to queue and execute tasks
 * on plants and customers in the nursery simulation.
 * 
 * @pattern Command - Encapsulates actions as objects for delayed or queued execution
 */
#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"

/**
 * @class Command
 * @brief Abstract base class for all worker commands.
 * 
 * The Command interface defines a common execute() method that all concrete
 * commands must implement. This enables polymorphic handling of different
 * worker actions.
 * 
 * @pattern Command - Command interface
 */
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual bool isPatrol() const { return false; }
};

/**
 * @class WaterCommand
 * @brief Command to water a plant.
 * 
 * Encapsulates the action of watering a plant, adding 50% to its water level.
 * Workers execute this command when plants need watering.
 * 
 * @pattern Command - Concrete command
 */ 
class WaterCommand : public Command {
public:
    void execute() override;
    WaterCommand(Plant* plant);
    private:
    Plant* targetPlant;
};

/**
 * @class FertilizeCommand
 * @brief Command to fertilize a plant.
 * 
 * Encapsulates the action of fertilizing a plant, adding 50% to its nutrient level.
 * Workers execute this command when plants need nutrients.
 * 
 * @pattern Command - Concrete command
 */
class FertilizeCommand : public Command {
public:
    void execute() override;
    FertilizeCommand(Plant* plant);
    private:
    Plant* targetPlant;
    

};

/**
 * @class HarvestCommand
 * @brief Command to harvest a plant.
 * 
 * Encapsulates the action of harvesting a ripe plant and moving it to the player's inventory.
 * Workers execute this command when plants are ready for harvest.
 * 
 * @pattern Command - Concrete command
 */
class HarvestCommand : public Command {
public:
    void execute() override;
    HarvestCommand(Plant* plant);
    private:
    Plant* targetPlant;
};

/**
 * @class PatrolCommand
 * @brief Command to patrol the nursery.
 * 
 * Encapsulates the action of patrolling the nursery to prevent robberies and
 * speed up time during night hours.
 * 
 * @pattern Command - Concrete command
 */
class PatrolCommand : public Command {
public:
    void execute() override;
    PatrolCommand(){}
    bool isPatrol() const override { return true; }
    private:
};

/**
 * @class ServeCommand
 * @brief Command to serve a customer.
 * 
 * Encapsulates the action of serving a customer at the storefront.
 * Handles customer interactions and transactions.
 * 
 * @pattern Command - Concrete command
 * @note Implementation currently incomplete
 */
class ServeCommand : public Command {
public:
    void execute() override;
    ServeCommand(Customer* cust);
private:
    Customer* target;
};