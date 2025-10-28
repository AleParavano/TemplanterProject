#include "Worker.h"

Worker::Worker(): Observer()
{
}

Worker::~Worker()
{
}

void Worker::executeCommand()
{
    for(auto command : commandQueue){
        command->execute();
        delete command;
    }
    commandQueue.clear();
}
void Worker::addCommand(Command* command)
{
    commandQueue.push_back(command);
}
void Worker::addPlant(Plant* plant)
{
    plants.push_back(plant);
}
void Worker::update(Plant* subject)
{
    //not sure what to do here
    
}
