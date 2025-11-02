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
class Worker: public Observer {
public:
Worker();
Worker(const Worker& worker);
~Worker();
void setLevel(int level);
void executeCommand();
void addCommand(Command* command);
void setSubject(Plant* plant);
virtual void update() override ;
void stop();
protected:
void startPatrol();
void endPatrol();

std::mutex mtx;
std::condition_variable condition;
std::atomic<bool> running{true};
std::thread workerThread;
std::queue<Command*> commandQueue;
// not responsible for  memory
Plant* subject;
PlantState* subjectState;
int level=0;


};

class WaterWorker:public Worker{
    void update() override;
};

class FertiliserWorker:public Worker{
    void update() override;
};

class HarvestWorker:public Worker{
    void update() override;
};

