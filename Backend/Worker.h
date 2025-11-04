/**
 * @file Worker.h
 * @brief Defines the Worker abstract base class and specialized worker types for task execution.
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
class Greenhouse;

/**
 * @class Worker
 * @brief An abstract base class representing an autonomous unit that executes commands.
 *
 * Worker objects run on their own threads, process a queue of Command objects,
 * and act as an Observer to a Greenhouse, receiving updates when the Greenhouse state changes.
 */
class Worker : public Observer
{

public:
    /**
     * @brief Constructs a new Worker object.
     *
     * Initializes the worker thread and internal state.
     */
    Worker();

    /**
     * @brief Copy constructor for the Worker class.
     * @param worker The Worker object to copy from.
     */
    Worker(const Worker &worker);

    /**
     * @brief Virtual destructor for the Worker base class.
     *
     * Ensures the worker thread is properly joined and resources are released.
     */
    virtual ~Worker();

    /**
     * @brief Sets the worker's proficiency level.
     *
     * Higher levels may correspond to faster execution or better results.
     * @param level The new integer level for the worker (e.g., 1, 2, 3).
     */
    void setLevel(int level);

    /**
     * @brief Executes the next command in the command queue.
     *
     * This method is typically called by the internal worker thread.
     */
    void executeCommand();

    /**
     * @brief Adds a command to the worker's execution queue.
     * @param command A pointer to the Command object to be executed. The worker takes ownership of the command.
     */
    void addCommand(Command *command);

    /**
     * @brief Sets the Greenhouse object this Worker observes.
     * @param greenhouse A pointer to the Greenhouse that acts as the Subject.
     */
    void setSubject(Greenhouse* greenhouse) override;

    /**
     * @brief Called by the Subject (Greenhouse) when its state changes.
     *
     * Derived classes must implement this to react to changes, typically by adding
     * new Commands to the queue (e.g., a WaterWorker adding a WaterCommand).
     */
    void update() override;

    /**
     * @brief Signals the worker thread to stop execution and attempts to join the thread.
     */
    void stop();

    /**
     * @brief Returns the type description of the worker.
     * @return A constant character pointer to the worker type string.
     */
    virtual const char *type() const { return "Manager/Generic Worker"; }

    /**
     * @brief Clears all pending commands from the worker's queue and handles their memory cleanup.
     */
    void clearCommandQueue();

protected:
    /**
     * @brief Initiates the worker's thread activity, often referred to as 'patrolling' or 'monitoring'.
     */
    void startPatrol();

    /**
     * @brief Stops the worker's thread activity and attempts to join the thread.
     */
    void endPatrol();

    /**
     * @brief A string describing the worker's current activity or command being executed.
     */
    std::string currentTaskDescription;

    /**
     * @brief Mutex used to protect shared resources, particularly the command queue, from concurrent access.
     */
    std::mutex mtx;

    /**
     * @brief Condition variable used to signal the worker thread when a new command is available.
     */
    std::condition_variable condition;

    /**
     * @brief Atomic flag indicating whether the worker thread should continue running.
     */
    std::atomic<bool> running{true};

    /**
     * @brief The thread on which the worker executes its commands.
     */
    std::thread workerThread;

    /**
     * @brief Queue of commands to be executed by the worker thread.
     */
    std::queue<Command *> commandQueue;

    /**
     * @brief Pointer to the Greenhouse object being observed. The Worker is not responsible for its memory.
     */
    Greenhouse *subject;

    /**
     * @brief The proficiency level of the worker. Default is 1.
     */
    int level = 1;
};

/**
 * @class WaterWorker
 * @brief Specialized Worker responsible for watering plants.
 */
class WaterWorker : public Worker
{
    /**
     * @brief Implementation of the Observer update logic for a WaterWorker.
     *
     * Typically checks the Greenhouse state for plants needing water and adds WaterCommand objects.
     */
    void update() override;

    /**
     * @brief Returns the specific type of this worker.
     * @return "Water Worker"
     */
    const char *type() const override { return "Water Worker"; }
};

/**
 * @class FertiliserWorker
 * @brief Specialized Worker responsible for applying fertilizer to plants.
 */
class FertiliserWorker : public Worker
{
    /**
     * @brief Implementation of the Observer update logic for a FertiliserWorker.
     *
     * Typically checks the Greenhouse state for plants needing fertilizer and adds FertiliseCommand objects.
     */
    void update() override;

    /**
     * @brief Returns the specific type of this worker.
     * @return "Fertiliser Worker"
     */
    const char *type() const override { return "Fertiliser Worker"; }
};

/**
 * @class HarvestWorker
 * @brief Specialized Worker responsible for harvesting mature plants.
 */
class HarvestWorker : public Worker
{
    /**
     * @brief Implementation of the Observer update logic for a HarvestWorker.
     *
     * Typically checks the Greenhouse state for plants ready for harvest and adds HarvestCommand objects.
     */
    void update() override;

    /**
     * @brief Returns the specific type of this worker.
     * @return "Harvest Worker"
     */
    const char *type() const override { return "Harvest Worker"; }
};