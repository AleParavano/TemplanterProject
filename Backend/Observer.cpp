/**
 * @file Observer.cpp
 * @brief Implementation of Observer base class
 */

#include "Observer.h"

/**
 * @brief Track observer instances with unique IDs
 */
int Observer::ObserverCount = 0;

/**
 * @brief Construct observer with unique ID
 */
Observer::Observer() {
    id = ObserverCount++;
}

/**
 * @brief Compare observers by ID
 * @param observer Observer to compare against
 * @return true if IDs match
 */
bool Observer::operator==(Observer* observer) {
    return this->id == observer->id;
}