/**
 * @file Subject.h
 * @brief Defines the abstract base class for the Subject role in the Observer pattern.
 */

#pragma once

#include "Observer.h"
#include <vector>

class Observer; // Forward declaration (although included above, good practice for pattern)

/**
 * @class Subject
 * @brief An abstract base class that represents an object being observed (the "Publisher").
 *
 * The Subject maintains a list of dependents (Observers) and notifies them
 * automatically of any state changes, usually by calling their update method.
 */
class Subject
{
public:
    /**
     * @brief Virtual destructor for the base class.
     *
     * Ensures proper cleanup of derived Subject objects.
     */
    virtual ~Subject() = default;

    /**
     * @brief Notifies all attached Observer objects of a change in the Subject's state.
     *
     * This is typically the method that initiates the update process for all listeners.
     */
    virtual void notify() = 0;

    /**
     * @brief Attaches an Observer to the Subject's list of dependents.
     * @param observer A pointer to the Observer object to be registered.
     */
    virtual void attach(Observer* observer) = 0;

    /**
     * @brief Detaches an Observer from the Subject's list of dependents.
     * @param observer A pointer to the Observer object to be unregistered.
     */
    virtual void detach(Observer* observer) = 0;
    
protected:
    /**
     * @brief A collection of pointers to the Observers currently registered to this Subject.
     */
    std::vector<Observer*> observers;
};