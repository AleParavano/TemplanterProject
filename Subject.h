#pragma once

#include "Observer.h"
#include <vector>

class Subject
{
public:
virtual void notify()=0;
virtual void attach(Observer* observer) = 0;
virtual void detach(Observer* observer) = 0;
protected:

std::vector<Observer*> observers;
};