/**
 * @file Worker.h
 * @brief Worker system for automated plant maintenance
 *
 * Defines worker classes that observe and maintain plants automatically.
 * Implements threaded command processing for autonomous operation.
 *
 * @pattern Observer - Monitors plant state changes
 * @pattern Command - Encapsulates maintenance actions
 * @pattern Template Method - Defines worker behavior framework
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

class Greenhouse;

/**
 * @class Worker
 * @brief Base worker class with command queue processing
 */
class Worker : public Observer
{

public:
    
    Worker();
    Worker(const Worker& worker);

    /**
     * @brief Stop thread and cleanup
     */
    virtual ~Worker();

    /**
     * @brief Set worker efficiency level
     * @param level Level 1-3 affecting work speed
     */
    void setLevel(int level);

    /**
     * @brief Main command processing loop
     * Runs on worker thread, processes command queue
     */
    void executeCommand();

    /**
     * @brief Add command to processing queue
     * @param command Command to execute (takes ownership)
     */
    void addCommand(Command* command);

    /**
     * @brief Set greenhouse to monitor
     * @param greenhouse Greenhouse to observe
     */
    void setSubject(Greenhouse* greenhouse) override;

    /**
     * @brief Handle plant state updates
     * Called when greenhouse notifies changes
     */
    void update() override;

    /**
     * @brief Stop worker thread
     */
    void stop();

    /**
     * @brief Get worker type string
     * @return Worker type identifier
     */
    virtual const char* type() const { return "Manager/Generic Worker"; }

    /**
     * @brief Clear pending commands
     */
    void clearCommandQueue();

protected:
    /**
     * @brief Enable player protection
     */
    void startPatrol();

    /**
     * @brief Disable player protection
     */
    void endPatrol();

    std::string currentTaskDescription;
    std::mutex mtx;
    std::condition_variable condition;
    std::atomic<bool> running{true};
    std::thread workerThread;
    std::queue<Command *> commandQueue;
    Greenhouse *subject;
    int level = 1;
};

/**
 * @class WaterWorker
 * @brief Specialized worker for watering plants
 *
 * Monitors water levels and automatically waters plants below threshold
 */
class WaterWorker : public Worker
{
    void update() override;
    const char *type() const override { return "Water Worker"; }
};

class FertiliserWorker : public Worker
{
    void update() override;
    const char *type() const override { return "Fertiliser Worker"; }
};

class HarvestWorker : public Worker
{
    void update() override;
    const char *type() const override { return "Harvest Worker"; }
};
