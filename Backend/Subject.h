/**
 * @file Subject.h
 * @brief Subject interface for Observer pattern
 *
 * Defines the interface for objects that can be observed.
 * Used primarily by Greenhouse to notify Workers of plant state changes.
 *
 * @pattern Observer - Subject interface
 */

#pragma once

#include "Observer.h"
#include <vector>

class Observer;

/**
 * @class Subject
 * @brief Observable interface that maintains a list of observers
 *
 * Base class for objects that can be observed. Maintains collection of
 * observers and provides notification mechanism.
 */
class Subject
{
public:
    virtual ~Subject() = default;
    virtual void notify() = 0;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    
protected:
    std::vector<Observer*> observers;
};