/**
 * @file Command.h
 * @brief Command pattern implementation for encapsulating worker tasks.
 * @details Provides a set of command classes that encapsulate actions like watering,
 *          fertilizing, harvesting, and patrolling plants. Enables flexible task queuing
 *          and execution.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 * @see Customer
 * @see Greenhouse
 */

#pragma once
#include "Plant.h"
#include "Customer.h"
#include "Greenhouse.h"

/**
 * @class Command
 * @brief Abstract base class for all worker commands.
 * 
 * The Command pattern allows actions to be encapsulated as objects, enabling tasks
 * to be queued, logged, or executed in various orders. All concrete commands inherit
 * from this interface.
 * 
 * @par Design Pattern: Command
 * Encapsulates requests (actions) as objects, allowing them to be passed around,
 * queued, or executed later. Decouples the invoker (worker) from the receiver (plant/customer).
 * 
 * @see WaterCommand
 * @see FertilizeCommand
 * @see HarvestCommand
 * @see PatrolCommand
 * @see ServeCommand
 */
class Command {
public:
    /**
     * @brief Virtual destructor for safe polymorphic deletion.
     */
    virtual ~Command() {}

    /**
     * @brief Executes the command.
     * @details Pure virtual method that must be implemented by all subclasses.
     *          Performs the actual action encapsulated by the command.
     */
    virtual void execute() = 0;

    /**
     * @brief Checks if this command is a patrol command.
     * @return true if this is a PatrolCommand, false for all other commands.
     * 
     * @details This is a convenience method to identify patrol commands without RTTI.
     */
    virtual bool isPatrol() const { return false; }
};

/**
 * @class WaterCommand
 * @brief Command for watering a plant.
 * 
 * Encapsulates the action of watering a plant. Can be queued and executed
 * when a worker has time to perform the task.
 * 
 * @par Safety Checks
 * - Validates that the plant exists in the greenhouse
 * - Checks that the plant is not dead
 * 
 * @see Plant::water()
 * @see Greenhouse
 */
class WaterCommand : public Command {
public:
    /**
     * @brief Executes the water command.
     * @details Applies water to the target plant if all validation checks pass.
     * 
     * @post If successful, the plant receives water effect
     */
    void execute() override;

    /**
     * @brief Constructor for WaterCommand.
     * @param plant Pointer to the Plant to water.
     * @param gh Pointer to the Greenhouse containing the plant.
     */
    WaterCommand(Plant* plant, Greenhouse* gh); 

private:
    Plant* targetPlant;         ///< The plant to water
    Greenhouse* subject;        ///< The greenhouse containing the plant
};

/**
 * @class FertilizeCommand
 * @brief Command for fertilizing a plant.
 * 
 * Encapsulates the action of fertilizing a plant with nutrients.
 * Can be queued and executed when a worker has time to perform the task.
 * 
 * @par Safety Checks
 * - Validates that the plant exists in the greenhouse
 * - Checks that the plant is not dead
 * 
 * @see Plant::fertilize()
 * @see Greenhouse
 */
class FertilizeCommand : public Command {
public:
    /**
     * @brief Executes the fertilize command.
     * @details Applies 50.0f units of fertilizer to the target plant if validation passes.
     * 
     * @post If successful, the plant receives fertilizer
     */
    void execute() override;
   
    /**
     * @brief Constructor for FertilizeCommand.
     * @param plant Pointer to the Plant to fertilize.
     * @param gh Pointer to the Greenhouse containing the plant.
     */
    FertilizeCommand(Plant* plant, Greenhouse* gh);

private:
    Plant* targetPlant;         ///< The plant to fertilize
    Greenhouse* subject;        ///< The greenhouse containing the plant
};

/**
 * @class HarvestCommand
 * @brief Command for harvesting a ripe plant.
 * 
 * Encapsulates the action of harvesting a plant and moving it to the player's inventory.
 * This command can be queued and executed by a worker.
 * 
 * @par Safety Checks
 * - Validates that the plant exists in the greenhouse
 * - Retrieves the current player and greenhouse
 * 
 * @see Greenhouse::harvestPlant()
 * @see Player
 */
class HarvestCommand : public Command {
public:
    /**
     * @brief Executes the harvest command.
     * @details Removes the plant from the greenhouse and moves it to the player's inventory.
     * 
     * @post If successful, the plant is transferred to inventory and greenhouse is cleared
     */
    void execute() override;

    /**
     * @brief Constructor for HarvestCommand.
     * @param plant Pointer to the Plant to harvest.
     * @param gh Pointer to the Greenhouse containing the plant.
     */
    HarvestCommand(Plant* plant, Greenhouse* gh);

private:
    Plant* targetPlant;         ///< The plant to harvest
    Greenhouse* subject;        ///< The greenhouse containing the plant
};

/**
 * @class PatrolCommand
 * @brief Command for a worker to patrol the nursery.
 * 
 * Encapsulates the action of a worker patrolling the nursery.
 * This appears to protect against theft by setting a protected flag.
 * 
 * @see Player::setProtected()
 */
class PatrolCommand : public Command {
public:
    /**
     * @brief Executes the patrol command.
     * @details Sets the player's protected flag to true.
     * 
     * @post If successful, the player is marked as protected
     */
    void execute() override;

    /**
     * @brief Constructor for PatrolCommand.
     * @details No parameters needed as patrol is a global action.
     */
    PatrolCommand(){}

    /**
     * @brief Identifies this as a patrol command.
     * @return Always returns true for PatrolCommand.
     * 
     * @override
     */
    bool isPatrol() const override { return true; }

private:
};

/**
 * @class ServeCommand
 * @brief Command for serving a customer.
 * 
 * Encapsulates the action of a worker serving a customer.
 * This command handles customer interactions and potentially purchases.
 * 
 * @note The execute() method is not yet implemented (marked as TODO).
 * 
 * @see Customer
 */
class ServeCommand : public Command {
public:
    /**
     * @brief Executes the serve command.
     * @details TODO: Implementation pending. Should handle customer service interactions.
     * 
     * @note This method is not currently implemented.
     */
    void execute() override;

    /**
     * @brief Constructor for ServeCommand.
     * @param cust Pointer to the Customer to serve.
     */
    ServeCommand(Customer *cust);

private:
    Customer* target;           ///< The customer to serve
};