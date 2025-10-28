#include "Observer.h"

Observer::Observer()
{
    id=ObserverCount++;
}

bool Observer::operator==(Observer *observer)
{
   return this->id==observer->id;
}
