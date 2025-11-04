/**
 * @file Observer.h
 * @brief Observer pattern interface for the nursery system.
 * @details Defines the Observer interface that workers implement to receive notifications
 *          when plant states change in the greenhouse.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Subject
 * @see Greenhouse
 * @see Worker
 */

#pragma once

// Forward declarations
/**
 * @class Greenhouse
 * @brief Forward declaration of Greenhouse class.
 */
class Greenhouse;

/**
 * @class Observer
 * @brief Abstract base class defining the Observer interface.
 * 
 * The Observer class implements the Observer role in the Observer pattern.
 * Observers are notified by a Subject (Greenhouse) whenever plant-related
 * state changes occur. Each observer has a unique ID for identification.
 * 
 * @par Design Pattern: Observer
 * Implements the Observer side of the one-to-many dependency. Multiple workers
 * (observers) can be attached to a greenhouse (subject) and will receive update
 * notifications automatically.
 * 
 * @par Usage
 * Workers inherit from Observer and override:
 * - update() - Called when the subject state changes
 * - setSubject() - Sets the greenhouse being observed
 * 
 * @par Thread Safety
 * The base Observer class is not thread-safe. Derived classes (Workers) may
 * implement thread-safety in their update() methods.
 * 
 * @see Greenhouse
 * @see Subject
 * @see Worker
 */
class Observer {
public:
    /**
     * @brief Constructor.
     * @details Increments the global ObserverCount and assigns a unique ID to this observer.
     *         Useful for tracking and identifying observers.
     */
    Observer();

    /**
     * @brief Virtual destructor.
     * @details Ensures proper cleanup of derived observer objects.
     * @details Default implementation allows destruction of derived types.
     */
    virtual ~Observer() = default;
    
    /**
     * @brief Called when the observed subject changes state.
     * @details Pure virtual method that derived classes must implement.
     *         Called automatically by the Subject when notify() is invoked.
     * 
     * @par Implementation Notes
     * Derived classes should:
     * - Check plant conditions (water, nutrients, health)
     * - Queue appropriate commands (water, fertilize, harvest)
     * - Ensure thread-safety if updating from multiple threads
     * 
     * @see Subject::notify()
     */
    virtual void update() = 0;

    /**
     * @brief Sets the subject (Greenhouse) being observed.
     * @param greenhouse Pointer to the Greenhouse to observe.
     * 
     * @details Called when the observer is attached to a subject.
     *         The observer uses this reference to query plant states
     *         and perform operations on plants.
     * 
     * @pre greenhouse should not be nullptr
     */
    virtual void setSubject(Greenhouse* greenhouse) = 0;
    
    /**
     * @brief Compares two observers by ID.
     * @param observer Pointer to another Observer to compare with.
     * @return true if both observers have the same ID, false otherwise.
     * 
     * @details Uses the unique ID assigned at construction for comparison.
     *         Useful for finding specific observers in a collection.
     */
    bool operator==(Observer* observer);
    
protected:
    int id;  ///< Unique identifier for this observer (assigned at construction)
    
private:
    static int ObserverCount;  ///< Class-level counter for generating unique IDs
};