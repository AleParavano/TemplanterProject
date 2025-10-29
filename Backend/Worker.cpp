#include "Worker.h"
#include <iostream>
#include "Player.h"
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

void Worker::update()
{
    if(subject){
    this->subjectState=subject->getPlantState();
    }
    // based on state information generate commands
    if(subjectState){
    if(subjectState->getNutrients()<=20.0f ){
        addCommand(new FertilizeCommand(this->subject));

    }else if(subjectState->getWater() <= 20.0f){
        addCommand(new WaterCommand(this->subject));

    }else if(subjectState->getState()=="Ripe"){
        //make new harvest command
    }
    else{
        addCommand(new PatrolCommand);

    }
    


}
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

void Worker::startPatrol()
{
    Player::setProtected(true);
}

void Worker::endPatrol()
{
    Player::setProtected(false);
}

void Worker::setLevel(int level)
{
    if(level>=1&&level<=3){
        this->level=level;
    }
}

void WaterWorker::update()
{
    if(subject){
    this->subjectState=subject->getPlantState();
    }
    if(subjectState){
    if(subjectState->getWater() <= 20.0f){
        addCommand(new WaterCommand(this->subject));
    }
}
}

void FertiliserWorker::update()
{
    if(subject){
    this->subjectState=subject->getPlantState();
    }
    if(subjectState){
    if(subjectState->getNutrients() <= 20.0f){
        addCommand(new FertilizeCommand(this->subject));
    }
}
}

void HarvestWorker::update()
{
        if(subject){
    this->subjectState=subject->getPlantState();
    }
    if(subjectState){
    if(subjectState->getState()=="Ripe"){
        //harvest command
    }
}
}
