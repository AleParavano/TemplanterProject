#pragma once

// Forward declarations
/**
 * @class Greenhouse
 * @brief Forward declaration for the Subject class in the Observer pattern.
 */
class Greenhouse;

/**
 * @class Observer
 * @brief The Observer interface (Abstract Observer) defines an updating interface 
 * for objects that should be notified of changes in a Subject.
 * * This class is the abstract base for all concrete observer components (e.g., UI elements, 
 * logging systems) that need to react when the state of the Greenhouse (the Subject) changes.
 */
class Observer {
public:
    /**
     * @brief Constructs an Observer object.
     * * Assigns a unique ID to the observer.
     */
    Observer();
    
    /**
     * @brief Virtual destructor.
     */
    virtual ~Observer() = default;
    
    /**
     * @brief Pure virtual method called by the Subject to notify the Observer of a state change.
     * * Concrete Observers implement this method to retrieve and process the updated information.
     */
    virtual void update() = 0;
    
    /**
     * @brief Pure virtual method to set the Subject (Greenhouse) this Observer is watching.
     * @param greenhouse A pointer to the Greenhouse object to be observed.
     */
    virtual void setSubject(Greenhouse* greenhouse) = 0;
    
    /**
     * @brief Overloads the equality operator to compare two Observer pointers based on their ID.
     * @param observer A pointer to the Observer to compare against.
     * @return true if the observers have the same ID, false otherwise.
     */
    bool operator==(Observer* observer);
    
protected:
    /** @brief A unique identifier for the observer object. */
    int id;
    
private:
    /** @brief Static counter used to assign unique IDs to new Observer instances. */
    static int ObserverCount;
};
