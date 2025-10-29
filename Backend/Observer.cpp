#include "Observer.h"

// Initialize static member
int Observer::ObserverCount = 0;

Observer::Observer() {
    id = ObserverCount++;
}

bool Observer::operator==(Observer* observer) {
    return this->id == observer->id;
}