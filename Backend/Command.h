#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"

/**
 * @class Command
 * @brief The abstract base class for the Command design pattern.
 * * Defines the interface for all concrete command objects.
 */
class Command {
public:
    /**
     * @brief Virtual destructor for the base class.
     */
    virtual ~Command() {}
    
    /**
     * @brief The core operation that executes the request.
     * * This is a pure virtual function and must be implemented by concrete commands.
     */
    virtual void execute() = 0;
    
    /**
     * @brief A flag to identify if a command is a 'Patrol' command.
     * @return true if the command is a PatrolCommand, false otherwise (default).
     */
    virtual bool isPatrol() const { return false; }
};

// --- Concrete Commands ---

/**
 * @class WaterCommand
 * @brief A concrete command to water a specific Plant.
 */
class WaterCommand : public Command {
public:
    /**
     * @brief Executes the watering action on the target plant.
     */
    void execute() override;
    
    /**
     * @brief Constructs a WaterCommand.
     * @param plant The Plant object to be watered.
     * @param gh The Greenhouse context needed for the operation.
     */
    WaterCommand(Plant* plant, Greenhouse* gh); 
private:
    /** @brief The specific plant to apply the action to. */
    Plant* targetPlant;
    
    /** @brief The greenhouse providing context or resources. */
    Greenhouse* subject; 
};

/**
 * @class FertilizeCommand
 * @brief A concrete command to fertilize a specific Plant.
 */
class FertilizeCommand : public Command {
public:
    /**
     * @brief Executes the fertilizing action on the target plant.
     */
    void execute() override;
   
    /**
     * @brief Constructs a FertilizeCommand.
     * @param plant The Plant object to be fertilized.
     * @param gh The Greenhouse context needed for the operation.
     */
    FertilizeCommand(Plant* plant, Greenhouse* gh);
private:
    /** @brief The specific plant to apply the action to. */
    Plant* targetPlant;
    
    /** @brief The greenhouse providing context or resources. */
    Greenhouse* subject; 
};

/**
 * @class HarvestCommand
 * @brief A concrete command to harvest a specific Plant.
 */
class HarvestCommand : public Command {
public:
    /**
     * @brief Executes the harvesting action on the target plant.
     */
    void execute() override;
    
    /**
     * @brief Constructs a HarvestCommand.
     * @param plant The Plant object to be harvested.
     * @param gh The Greenhouse context needed for the operation.
     */
    HarvestCommand(Plant* plant, Greenhouse* gh);
private:
    /** @brief The specific plant to apply the action to. */
    Plant* targetPlant;
    
    /** @brief The greenhouse providing context or resources. */
    Greenhouse* subject;
};

/**
 * @class PatrolCommand
 * @brief A concrete command representing a general patrolling or checking action.
 */
class PatrolCommand : public Command {
public:
    /**
     * @brief Executes the patrolling action (e.g., checks the greenhouse status).
     */
    void execute() override;
    
    /**
     * @brief Constructs a PatrolCommand.
     */
    PatrolCommand(){}
    
    /**
     * @brief Overrides the base method to confirm this is a patrol command.
     * @return true always.
     */
    bool isPatrol() const override { return true; }
private:
    // No specific member variables needed for a general patrol command.
};

/**
 * @class ServeCommand
 * @brief A concrete command to serve a specific Customer.
 */
class ServeCommand : public Command {
public:
    /**
     * @brief Executes the serving action for the target customer.
     */
    void execute() override;
    
    /**
     * @brief Constructs a ServeCommand.
     * @param cust The Customer object to be served.
     */
    ServeCommand(Customer* cust);
private:
    /** @brief The specific customer to apply the action to. */
    Customer* target;
};