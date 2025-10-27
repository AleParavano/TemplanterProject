#pragma once

#include "Observer.h"
#include <vector>
class Subject{
public:
virtual void notify()=0;
virtual void attach()=0;
virtual void detach()=0;
protected:

std::vector<Observer*> observers;
};