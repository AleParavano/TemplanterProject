#pragma once
#include "Observer.h"
#include <vector>
#include "Command.h"
#include "Plant.h"
class Worker: public Observer {
public:
void executeCommand();
protected:
std::vector<Command*> commandQueue;
std::vector<Plant*> plants;
};