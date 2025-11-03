/**
 * @file Observer.h
 * @brief Observer pattern interface for plant monitoring
 *
 * Defines the Observer base class used to monitor plant state changes
 * and trigger worker actions.
 *
 * @pattern Observer - Monitors plant state changes
 */

#pragma once

// Forward declarations
class Greenhouse;

/**
 * @class Observer
 * @brief Abstract base class for the Observer pattern
 *
 * Provides interface for objects that need to monitor greenhouse state.
 * Used primarily by Worker classes to respond to plant state changes.
 */
class Observer {
public:
    Observer();
    virtual ~Observer() = default;
    
    virtual void update() = 0;
    virtual void setSubject(Greenhouse* greenhouse) = 0;
    
    bool operator==(Observer* observer);
    
protected:
    int id;
    
private:
    static int ObserverCount;
};