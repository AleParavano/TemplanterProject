/**
 * @file Worker.h
 * @brief Worker entities that manage plant care through the Observer and Command patterns.
 * @details Defines worker types (WaterWorker, FertiliserWorker, HarvestWorker) that
 *          monitor plants and queue tasks through a command queue with threading.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Observer
 * @see Command
 * @see Greenhouse
 */

#pragma once
#include "Observer.h"
#include <queue>
#include "Command.h"
#include "Plant.h"
#include "PlantState.h"
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <atomic>
#include <vector>

// Forward declaration
/**
 * @class Greenhouse
 * @brief Forward declaration of Greenhouse class.
 */
class Greenhouse;

/**
 * @class Worker
 * @brief Base class for plant care workers with threading and command queueing.
 * 
 * Worker implements both the Observer pattern (to receive plant notifications)
 * and uses the Command pattern (to queue and execute tasks).
 * 
 * @par Design Pattern: Observer
 * Workers inherit from Observer and receive update() notifications from the
 * Greenhouse whenever plant states change.
 * 
 * @par Design Pattern: Command
 * Workers queue Command objects (WaterCommand, FertilizeCommand, etc.) and
 * execute them on a separate thread.
 * 
 * @par Threading
 * Each worker runs on its own thread with a command queue. Commands are
 * processed one at a time as they're queued.
 * 
 * @par Worker Types
 * Three specialized worker types are defined:
 * - WaterWorker: Monitors water levels, queues WaterCommand
 * - FertiliserWorker: Monitors nutrients, queues FertilizeCommand
 * - HarvestWorker: Monitors ripeness, queues HarvestCommand
 * 
 * @par Performance
 * Workers operate independently on threads, allowing efficient parallel task
 * execution without blocking the main game loop.
 * 
 * @see WaterWorker
 * @see FertiliserWorker
 * @see HarvestWorker
 * @see Command
 * @see Observer
 */
class Worker : public Observer
{
public:
    /**
     * @brief Constructor.
     * @details Creates a worker and starts its command execution thread.
     *         Worker starts in "running" state ready to accept commands.
     */
    Worker();

    /**
     * @brief Copy constructor.
     * @param worker Reference to another Worker to copy from
     * 
     * @note Worker type is copied but command queue is not
     */
    Worker(const Worker &worker);

    /**
     * @brief Destructor.
     * @details Stops the worker thread and cleans up resources.
     *         Calls stop() to ensure proper shutdown.
     */
    virtual ~Worker();

    /**
     * @brief Sets the worker's skill level.
     * @param level Worker level (1-3)
     * 
     * @details Higher levels may affect efficiency or task quality.
     *         Levels are clamped to valid range [1-3].
     */
    void setLevel(int level);

    /**
     * @brief Executes queued commands on the worker thread.
     * @details Internal method run on the worker's thread.
     *         Waits for commands to be queued, executes them, then waits again.
     *         Continues until stop() is called.
     * 
     * @note This method runs continuously in a separate thread
     */
    void executeCommand();

    /**
     * @brief Adds a command to the worker's queue.
     * @param command Pointer to a Command to execute
     * 
     * @details Commands are executed FIFO (first-in, first-out).
     *         Thread-safe with mutex protection.
     * 
     * @post Command is queued and condition variable is signaled
     */
    void addCommand(Command *command);

    /**
     * @brief Sets the subject (Greenhouse) being observed.
     * @param greenhouse Pointer to the Greenhouse to work with
     * 
     * @details Called when worker is attached to a greenhouse.
     *         Worker uses this reference to query plant states.
     * 
     * @override
     */
    void setSubject(Greenhouse* greenhouse) override;

    /**
     * @brief Called when the observed greenhouse changes.
     * @details Pure virtual method that derived classes implement.
     *         Called by Greenhouse::notify() when plant states change.
     * 
     * @override
     */
    void update() override;

    /**
     * @brief Stops the worker and its execution thread.
     * @details Sets running flag to false and waits for thread to join.
     *         After calling this, no more commands will be processed.
     * 
     * @post Worker thread is terminated and joined
     */
    void stop();

    /**
     * @brief Gets the worker's type as a string.
     * @return Worker type ("Manager/Generic Worker", "Water Worker", etc.)
     * 
     * @virtual
     */
    virtual const char *type() const { return "Manager/Generic Worker"; }

    /**
     * @brief Clears all pending commands from the queue.
     * @details Deletes all queued commands without executing them.
     *         Thread-safe with mutex protection.
     * 
     * @post Command queue is empty
     * @post All command objects are deleted
     */
    void clearCommandQueue();

protected:
    /**
     * @brief Starts patrol mode (sets player as protected).
     * @details Called when a PatrolCommand is queued.
     * 
     * @see endPatrol()
     */
    void startPatrol();

    /**
     * @brief Ends patrol mode (removes player protection).
     * @details Called when patrol is complete.
     * 
     * @see startPatrol()
     */
    void endPatrol();

    std::string currentTaskDescription;          ///< Description of current task
    std::mutex mtx;                              ///< Mutex for thread-safe queue access
    std::condition_variable condition;           ///< Signal for new commands
    std::atomic<bool> running{true};             ///< Flag to control thread execution
    std::thread workerThread;                    ///< Worker's execution thread
    std::queue<Command *> commandQueue;          ///< Queue of commands to execute
    Greenhouse *subject;                         ///< Reference to observed greenhouse
    int level;                                   ///< Worker skill level (1-3)
};

/**
 * @class WaterWorker
 * @brief Specialist worker that monitors and manages plant watering.
 * 
 * WaterWorker observes plants and automatically queues WaterCommand when
 * a plant's water level falls below 20%.
 * 
 * @par Behavior
 * - Triggered by Greenhouse notifications
 * - Scans all plants for water < 20%
 * - Clears previous commands to avoid redundancy
 * - Queues WaterCommand for each thirsty plant
 * 
 * @see WaterCommand
 */
class WaterWorker : public Worker
{
public:
    /**
     * @brief Called when greenhouse plants change.
     * @details Scans for plants needing water and queues WaterCommand.
     * 
     * @override
     */
    void update() override;

    /**
     * @brief Returns "Water Worker".
     * 
     * @override
     */
    const char *type() const override { return "Water Worker"; }
};

/**
 * @class FertiliserWorker
 * @brief Specialist worker that monitors and manages plant fertilization.
 * 
 * FertiliserWorker observes plants and automatically queues FertilizeCommand when
 * a plant's nutrient level falls below 20%.
 * 
 * @par Behavior
 * - Triggered by Greenhouse notifications
 * - Scans all plants for nutrients < 20%
 * - Clears previous commands to avoid redundancy
 * - Queues FertilizeCommand for each malnourished plant
 * 
 * @see FertilizeCommand
 */
class FertiliserWorker : public Worker
{
public:
    /**
     * @brief Called when greenhouse plants change.
     * @details Scans for plants needing fertilizer and queues FertilizeCommand.
     * 
     * @override
     */
    void update() override;

    /**
     * @brief Returns "Fertiliser Worker".
     * 
     * @override
     */
    const char *type() const override { return "Fertiliser Worker"; }
};

/**
 * @class HarvestWorker
 * @brief Specialist worker that monitors and manages plant harvesting.
 * 
 * HarvestWorker observes plants and automatically queues HarvestCommand when
 * a plant reaches the Ripe state and is ready for harvest.
 * 
 * @par Behavior
 * - Triggered by Greenhouse notifications
 * - Scans all plants for ripe status
 * - Clears previous commands to avoid redundancy
 * - Queues HarvestCommand for each ripe plant
 * 
 * @see HarvestCommand
 */
class HarvestWorker : public Worker
{
public:
    /**
     * @brief Called when greenhouse plants change.
     * @details Scans for ripe plants and queues HarvestCommand.
     * 
     * @override
     */
    void update() override;

    /**
     * @brief Returns "Harvest Worker".
     * 
     * @override
     */
    const char *type() const override { return "Harvest Worker"; }
};