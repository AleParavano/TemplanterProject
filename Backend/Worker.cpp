#include "Worker.h"
#include "Greenhouse.h"
#include <iostream>
#include "Command.h"
#include "Player.h"
#include "Game.h"

Worker::Worker() : Observer()
{
    subject = nullptr;
    workerThread = std::thread(&Worker::executeCommand, this);
}

Worker::Worker(const Worker& worker)
{
    this->level = worker.level;
    this->subject = worker.subject;
    workerThread = std::thread(&Worker::executeCommand, this);
    // queue does not get copied over
}

Worker::~Worker()
{
    stop();
}

void Worker::executeCommand()
{
    while(running){
        std::unique_lock<std::mutex> lock(mtx);
        condition.wait(lock, [&]{return !commandQueue.empty() || !running;});
        if(!running && commandQueue.empty()){
            break;
        }
        Command* command = commandQueue.front();
        commandQueue.pop();
        lock.unlock();
        command->execute();
        if(!command->isPatrol()){
            endPatrol();
        }
        
        std::cout << "Executing command" << std::endl;
        switch(level){
            case 1:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case 2:
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
                break;
            case 3:
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
        }
        delete command;
    }
}

void Worker::addCommand(Command* command)
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        commandQueue.push(command);
    }
    condition.notify_one();
}

void Worker::setSubject(Greenhouse* greenhouse)
{
    this->subject = greenhouse;
}



void Worker::stop()
{
    if(running){
        running = false;
        condition.notify_all();
        if(workerThread.joinable()){
            workerThread.join();
        }
    }
}

void Worker::addWorker(Worker *worker)
{
    if (worker) {
        hiredWorkers.push_back(worker);
        std::cout << "WORKER MANAGER: New " << worker->type() << " hired." << std::endl;
    }
}

void Worker::startPatrol()
{
    Player* player = Game::getInstance()->getPlayerPtr();
    if(player)
        player->setProtected(true);
}

void Worker::endPatrol()
{
    Player* player = Game::getInstance()->getPlayerPtr();
    if(player)
        player->setProtected(false);
}

void Worker::setLevel(int level)
{
    if(level >= 1 && level <= 3){
        this->level = level;
    }
}
void Worker::update()
{
    return;
}

void WaterWorker::update()
{
    if(subject){
        for(int i = 0; i < subject->getCapacity(); i++){
            Plant* plant = subject->getPlant(i);
            if(plant && plant->getWater() <= 20.0f){
                addCommand(new WaterCommand(plant));
            }
        }
    }
}

void FertiliserWorker::update()
{
    if(subject){
        for(int i = 0; i < subject->getCapacity(); i++){
            Plant* plant = subject->getPlant(i);
            if(plant && plant->getNutrients() <= 20.0f){
                addCommand(new FertilizeCommand(plant));
            }
        }
    }
}

void HarvestWorker::update()
{
    if(subject){
        for(int i = 0; i < subject->getCapacity(); i++){
            Plant* plant = subject->getPlant(i);
            if(plant && plant->isRipe()){
                addCommand(new HarvestCommand(plant));
            }
        }
    }
}
