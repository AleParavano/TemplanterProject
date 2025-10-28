#pragma once
#include "Observer.h"
#include <vector>
#include "Command.h"
#include "Plant.h"
class Worker: public Observer {
public:
Worker();
~Worker();
void executeCommand();
void addCommand(Command* command);
void addPlant(Plant* plant);
void update(Plant* subject) override ;
protected:

std::vector<Command*> commandQueue;
// not responsible for  memory
std::vector<Plant*> plants;
};