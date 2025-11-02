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

class Worker : public Observer
{

public:
    Worker();
    Worker(const Worker &worker);
    virtual ~Worker();

    void setLevel(int level);
    void executeCommand();
    void addCommand(Command *command);
    void setSubject(Greenhouse* greenhouse) override;
    void update() override;
    void stop();
    std::vector<Worker *> hiredWorkers;
    void addWorker(Worker *worker);
    virtual const char *type() const { return "Manager/Generic Worker"; }

protected:
    void startPatrol();
    void endPatrol();
    std::string currentTaskDescription;
    std::mutex mtx;
    std::condition_variable condition;
    std::atomic<bool> running{true};
    std::thread workerThread;
    std::queue<Command *> commandQueue;
    // not responsible for  memory
    Greenhouse *subject;
    int level = 0;
};

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
