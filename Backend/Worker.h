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

// Forward declaration
class Greenhouse;

class Worker: public Observer {
public:
    Worker();
    Worker(const Worker& worker);
    virtual ~Worker();
    
    void setLevel(int level);
    void executeCommand();
    void addCommand(Command* command);
    void setSubject(Greenhouse* greenhouse) override;
    virtual void update() override;
    void stop();
    
protected:
    void startPatrol();
    void endPatrol();

    std::mutex mtx;
    std::condition_variable condition;
    std::atomic<bool> running{true};
    std::thread workerThread;
    std::queue<Command*> commandQueue;
    
    Greenhouse* subject;
    int level = 0;
};

class WaterWorker : public Worker {
public:
    void update() override;
};

class FertiliserWorker : public Worker {
public:
    void update() override;
};

class HarvestWorker : public Worker {
public:
    void update() override;
};