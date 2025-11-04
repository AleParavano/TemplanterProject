/**
 * @file Subject.h
 * @brief Subject interface for the Observer pattern.
 * @details Defines the Subject (Observable) role that notifies observers of state changes.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Observer
 * @see Greenhouse
 */

#pragma once

#include "Observer.h"
#include <vector>

// Forward declaration
class Observer;

/**
 * @class Subject
 * @brief Abstract subject interface for the Observer pattern.
 * 
 * Subject defines the interface for objects that manage observers and send
 * notifications. Greenhouse implements this interface.
 * 
 * @par Design Pattern: Observer
 * Subject is the "Observable" in the Observer pattern. It maintains a list
 * of observers and notifies them when state changes.
 * 
 * @see Greenhouse
 * @see Observer
 */
class Subject
{
public:
    /**
     * @brief Virtual destructor for safe polymorphic deletion.
     */
    virtual ~Subject() = default;

    /**
     * @brief Notifies all attached observers of state changes.
     * @details Pure virtual method. Called when subject state changes.
     * 
     * @post All observers receive an update() call
     */
    virtual void notify() = 0;

    /**
     * @brief Attaches an observer to be notified of changes.
     * @param observer Pointer to an Observer to attach
     * 
     * @post Observer is added to notification list
     */
    virtual void attach(Observer* observer) = 0;

    /**
     * @brief Detaches an observer from notifications.
     * @param observer Pointer to an Observer to remove
     * 
     * @post Observer is removed from notification list
     */
    virtual void detach(Observer* observer) = 0;
    
protected:
    std::vector<Observer*> observers;  ///< List of attached observers
};