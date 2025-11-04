/**
 * @file Memento.h
 * @brief Memento pattern implementation for capturing game state.
 * @details Provides a snapshot of the game state (plants, inventory, time, money)
 *          that can be saved and restored without exposing internal game structure.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Caretaker
 * @see Game
 */

#pragma once
#include <string>

/**
 * @class Memento
 * @brief Captures a snapshot of the game state at a specific moment.
 * 
 * The Memento class implements the Memento pattern to encapsulate all necessary
 * information for saving and restoring the game state. It stores:
 * - Inventory data (plant stacks)
 * - Greenhouse data (plant states and positions)
 * - Worker data
 * - Financial state (money)
 * - Reputation (rating)
 * - Time (day, hour, minute)
 * 
 * @par Design Pattern: Memento
 * Provides a way to capture and externalize an object's internal state without
 * violating encapsulation. The Caretaker manages the storage and restoration of
 * Memento objects.
 * 
 * @par Serialization
 * Game state is serialized into strings using a pipe-delimited format for simplicity.
 * This allows for easy file I/O through the Caretaker.
 * 
 * @par Thread Safety
 * This class is immutable after construction. Once created, Mementos are safe to
 * access from multiple threads without synchronization.
 * 
 * @example
 * @code
 * Memento* state = new Memento(
 *     "Lettuce:5|Tomato:3",  // inventory
 *     "2",                    // workers
 *     "plant_data...",        // greenhouse
 *     1500.50f,               // money
 *     85,                     // rating
 *     5,                      // day
 *     14,                     // hour
 *     30                      // minute
 * );
 * 
 * // Retrieve state information
 * float money = state->getMoney();
 * int day = state->getDay();
 * @endcode
 * 
 * @see Caretaker
 * @see Game::saveGame()
 */
class Memento 
{
public:
    /**
     * @brief Constructor capturing the current game state.
     * @param inv String representation of inventory state.
     *            Format: "Type1:count1|Type2:count2|..."
     * @param work String representation of worker data.
     *             Format: TBD (depends on worker serialization)
     * @param gh String representation of greenhouse data.
     *           Format: Contains plant states, health, position data
     * @param m Current player money.
     * @param r Current player rating (0-100).
     * @param d Current day number.
     * @param h Current hour (0-23).
     * @param min Current minute (0-59).
     * 
     * @details All parameters are stored as immutable member variables.
     */
    Memento(const std::string& inv, const std::string& work, const std::string& gh, 
            float m, int r, int d, int h, int min);

    /**
     * @brief Destructor.
     * @details Virtual to ensure proper cleanup in derived classes if needed.
     */
    ~Memento();
    
    /**
     * @brief Gets the captured inventory state.
     * @return Const reference to the inventory data string.
     *         Format: "PlantType:count|PlantType:count|..."
     */
    const std::string& getInventoryData() const;

    /**
     * @brief Gets the captured worker state.
     * @return Const reference to the worker data string.
     */
    const std::string& getWorkerData() const;

    /**
     * @brief Gets the captured greenhouse state.
     * @return Const reference to the greenhouse data string.
     *         Contains all plant states and their properties.
     */
    const std::string& getGreenhouseData() const;
    
    /**
     * @brief Gets the captured money value.
     * @return Player's money at the time of capture.
     */
    float getMoney() const;

    /**
     * @brief Gets the captured rating value.
     * @return Player's rating (typically 0-100) at the time of capture.
     */
    int getRating() const;

    /**
     * @brief Gets the captured day number.
     * @return Current day in the game world.
     */
    int getDay() const;

    /**
     * @brief Gets the captured hour value.
     * @return Current hour (0-23).
     */
    int getHour() const;

    /**
     * @brief Gets the captured minute value.
     * @return Current minute (0-59).
     */
    int getMinute() const;

private:
    std::string inventoryData;      ///< Serialized inventory state
    std::string workerData;         ///< Serialized worker state
    std::string greenhouseData;     ///< Serialized greenhouse state
    
    float money;                    ///< Player's money
    int rating;                     ///< Player's rating
    int day;                        ///< Current game day
    int hour;                       ///< Current game hour
    int minute;                     ///< Current game minute
};