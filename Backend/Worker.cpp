#include "Worker.h"
#include <iostream>
#include "Command.h"
#include "Player.h"
#include "Game.h"
Worker::Worker(): Observer()
{
    workerThread=std::thread(&Worker::executeCommand,this);
}

Worker::Worker(const Worker &worker)
{
    this->level=worker.level;
    this->subject=worker.subject;
    this->subjectState=worker.subjectState;
    workerThread=std::thread(&Worker::executeCommand,this);
    //queue does not get copied over
}

Worker::~Worker()
{
    stop();
}

void Worker::executeCommand()
{
   while (running){
    std::unique_lock<std::mutex> lock(mtx);
    condition.wait(lock,[&]{return !commandQueue.empty()||!running;});
    if(!running&&commandQueue.empty()){
        break;
    }
    Command* command=commandQueue.front();
    commandQueue.pop();
    lock.unlock();
    command->execute();
    if (!command->isPatrol()) {
            endPatrol();
    }
    
    std::cout<<"Executing command"<<std::endl;
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
{   {
    std::lock_guard<std::mutex> lock(mtx);
    commandQueue.push(command);
    }
    condition.notify_one();
}

void Worker::setSubject(Plant *plant)
{
    this->subject=plant;
}

void Worker::update(Plant *changedPlant)
{
    return;
}

void Worker::stop()
{
    if(running){
        running=false;
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
 Player* player=Game::getInstance()->getPlayerPtr();
 if(player)
 player->setProtected(true);
}

void Worker::endPatrol()
{   Player* player=Game::getInstance()->getPlayerPtr();
    if(player)
    player->setProtected(false);
}

void Worker::setLevel(int level)
{
    if(level>=1&&level<=3){
        this->level=level;
    }
}

void Worker::attachToAllPlants(Plant *plant)
{
    if (!plant) return;   
    for (Worker* specializedWorker : hiredWorkers) {
        if (specializedWorker) {
            // The Plant (Subject) registers the specialized Worker (Observer)
            plant->attach(specializedWorker);
            std::cout << "WORKER MANAGER: Attached plant to " << specializedWorker->type() << " worker." << std::endl;
        }
    }
}

void WaterWorker::update(Plant* plantToTend)
{
    if (!plantToTend) return;
    PlantState* plantState = plantToTend->getPlantState();
    
    if (plantState)
    {
       
        if (plantState->getWater() <= 30.0f) 
        {
            addCommand(new WaterCommand(plantToTend)); 
            
            std::cout << "WORKER SCHEDULE: " << type() << " detected low water (" 
                      << plantState->getWater() << "%) for plant "
                      << plantToTend->getType() << " and queued WaterCommand." << std::endl;
        }
    }
}

void FertiliserWorker::update(Plant* changedPlant)
{
    if (!changedPlant) return;

    PlantState* plantState = changedPlant->getPlantState();
    
    if (plantState)
    {
        // FIX: Check if Nutrients is below 30% threshold
        if (plantState->getNutrients() <= 30.0f) 
        {
            addCommand(new FertilizeCommand(changedPlant));
            std::cout << "WORKER SCHEDULE: " << type() << " detected low nutrients (" 
                      << subjectState->getNutrients() << "%) and queued FertilizeCommand." << std::endl;
        }
    }
}

void HarvestWorker::update(Plant* changedPlant)
{
    if (!changedPlant) return;
    if(subjectState){
    if(subjectState->getState()=="Ripe"){
        //harvest command
    }
}
}
