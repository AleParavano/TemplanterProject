/**
 * @file Player.h
 * @brief Player entity managing inventory, staff, and game progression.
 * @details The Player class manages all player-owned resources including inventory,
 *          greenhouse, workers, money, rating, and time progression.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Inventory
 * @see Greenhouse
 * @see Worker
 * @see Memento
 */

#pragma once

#include <string>
#include <vector>
#include "Inventory.h"
#include "Greenhouse.h"
#include "Worker.h"
#include "Memento.h"
#include "../Frontend/InventoryUI.h"

/**
 * @class Player
 * @brief Central player state manager for the nursery business.
 * 
 * The Player class represents the player's nursery business and manages:
 * - Financial state (money, rating/reputation)
 * - Game time (day, hour, minute progression)
 * - Inventory of harvested plants
 * - Greenhouse operations
 * - Staff management (workers)
 * - Protection status (against robbery)
 * 
 * @par Features
 * - Real-time game clock with day/night cycle speed variation
 * - Worker management and command queueing
 * - Save/load via Memento pattern
 * - Money and rating tracking
 * - Time acceleration during night (safe) hours
 * 
 * @par Time System
 * Game time progresses at different speeds:
 * - Day (6:00-20:00): 1x speed (player active, customers visiting)
 * - Night (20:00-6:00): 10x speed (accelerated growth, patrols)
 * - Protected periods: 10x speed (worker patrols active)
 * 
 * @par Worker Management
 * Players can hire workers (WaterWorker, FertiliserWorker, HarvestWorker).
 * Each worker monitors specific plant conditions and automatically queues
 * appropriate care commands.
 * 
 * @example
 * @code
 * Player player;
 * player.addMoney(100);
 * player.addWorker(new WaterWorker());
 * player.UpdateGameTime(0.016f);  // Update with frame delta
 * @endcode
 * 
 * @see Inventory
 * @see Greenhouse
 * @see Worker
 * @see Memento
 */
class Player 
{
public:
    /**
     * @brief Constructor.
     * @details Initializes player with:
     *         - 100 starting money
     *         - 0 rating
     *         - Day 1, 6:00 AM (morning start)
     *         - New Inventory (25 slots)
     *         - New Greenhouse
     *         - New InventoryUI
     *         - Not protected status
     */
    Player();

    /**
     * @brief Destructor.
     * @details Cleans up inventory, greenhouse, workers, and UI.
     */
    ~Player();
    
    // Financial management
    
    /**
     * @brief Gets the current money amount.
     * @return Current funds in currency units
     */
    float getMoney() const;

    /**
     * @brief Sets money to a specific amount.
     * @param amount New money value (replaces current)
     */
    void setMoney(float amount);

    /**
     * @brief Adds money to the player's account.
     * @param amount Amount to add (typically from plant sales)
     * 
     * @post Money increases by amount
     */
    void addMoney(float amount);

    /**
     * @brief Removes money from the player's account.
     * @param amount Amount to remove (typically for purchases)
     * 
     * @post Money decreases by amount (minimum 0)
     */
    void subtractMoney(float amount);
    
    // Reputation management
    
    /**
     * @brief Gets the current player rating.
     * @return Rating (typically 0-5)
     */
    float getRating() const;

    /**
     * @brief Sets rating to a specific value.
     * @param r New rating value
     */
    void setRating(float r);

    /**
     * @brief Increases player rating.
     * @param r Rating increase amount
     * 
     * @post Rating increases (capped at 5.0)
     */
    void addRating(float r);

    /**
     * @brief Decreases player rating.
     * @param r Rating decrease amount
     * 
     * @post Rating decreases (minimum 0)
     */
    void subtractRating(float r);
    
    // Time management
    
    /**
     * @brief Gets the current game day number.
     * @return Day number (starts at 1)
     */
    int getDay() const;

    /**
     * @brief Gets the current game hour.
     * @return Hour (0-23)
     */
    int getHour() const;

    /**
     * @brief Gets the current game minute.
     * @return Minute (0-59)
     */
    int getMinute() const;

    /**
     * @brief Sets the game time to a specific moment.
     * @param d Day number
     * @param h Hour (0-23)
     * @param m Minute (0-59)
     * 
     * @post Game time is set to the specified values
     */
    void setTime(int d, int h, int m);

    /**
     * @brief Advances game time by specified minutes.
     * @param minutes Number of minutes to advance
     * 
     * @details Handles overflow: minutes wrap to hours, hours wrap to days.
     * @post Time is advanced with proper hour/day wraparound
     */
    void advanceTime(int minutes);

    /**
     * @brief Updates game time based on real elapsed time.
     * @param dt Delta time in real seconds (frame time)
     * 
     * @details Time progression varies by game period:
     *         - Daytime (6:00-20:00): Normal speed (1x)
     *         - Nighttime (20:00-6:00): Fast speed (10x)
     *         - Protected: Fast speed (10x)
     * 
     * @par Usage
     * Call each frame with the delta time to progress game time:
     * @code
     * player.UpdateGameTime(16.0f / 1000.0f);  // 16ms frame time
     * @endcode
     * 
     * @post Game time may advance by several minutes
     */
    void UpdateGameTime(float dt);

    /**
     * @brief Gets current time as a formatted string.
     * @return Time string (format: "HH:MM")
     * 
     * @example
     * Returns "14:30" for 2:30 PM
     */
    std::string getTimeString() const;

    /**
     * @brief Gets the player's inventory UI.
     * @return Pointer to the InventoryUI object
     */
    InventoryUI* getInventoryUI() const { return inventoryUI; }
    
    // Greenhouse and inventory access
    
    /**
     * @brief Gets the player's inventory.
     * @return Pointer to the Inventory object
     */
    Inventory* getInventory() const;

    /**
     * @brief Gets the player's greenhouse.
     * @return Pointer to the Greenhouse object
     */
    Greenhouse* getPlot() const;
    
    // Worker management
    
    /**
     * @brief Hires a worker and adds them to the player's staff.
     * @param worker Pointer to a Worker to hire
     * 
     * @details Worker is automatically attached to the greenhouse
     *         and begins observing plant states.
     * 
     * @post Worker is added to staff and attached to greenhouse
     */
    void addWorker(Worker* worker);

    /**
     * @brief Fires a worker, removing them from staff.
     * @param index Index in the worker list (0-based)
     * 
     * @details Worker is detached from greenhouse and deleted.
     * @post Worker is removed and memory is freed
     */
    void fireWorker(int index);

    /**
     * @brief Gets a specific worker by index.
     * @param index Index in the worker list (0-based)
     * @return Pointer to the Worker, or nullptr if index is invalid
     */
    Worker* getWorker(int index) const;

    /**
     * @brief Gets the total number of hired workers.
     * @return Count of current staff
     */
    int getWorkerCount() const;

    /**
     * @brief Pauses all workers (stops command processing).
     * @details Calls stop() on all workers
     * 
     * @post All workers stop accepting new commands
     */
    void pauseWorkers();

    /**
     * @brief Resumes all workers.
     * @details Currently not fully implemented
     */
    void startWorkers();

    /**
     * @brief Gets the list of all workers.
     * @return Reference to the worker vector
     */
    const std::vector<Worker *> &getWorkers();
    
    // Protection status (vs robbers)
    
    /**
     * @brief Sets whether the player is protected from theft.
     * @param prot true to enable protection, false to disable
     * 
     * @details Protection is typically active during patrols or night hours.
     * @post Protection status is updated
     */
    void setProtected(bool prot);

    /**
     * @brief Checks if the player is currently protected.
     * @return true if protected from robbery, false otherwise
     */
    bool isProtected();
    
    // Save/load via Memento
    
    /**
     * @brief Creates a Memento of the current player state.
     * @return Pointer to a new Memento object
     * 
     * @details Serializes all player data:
     *         - Inventory contents
     *         - Worker list
     *         - Greenhouse state
     *         - Money and rating
     *         - Current time
     * 
     * @see Memento
     * @see Game::saveGame()
     */
    Memento* createMemento() const;

    /**
     * @brief Restores player state from a Memento.
     * @param memento Pointer to a Memento to restore from
     * 
     * @details Deserializes all player data from the memento.
     *         Workers are paused during restore, then re-attached to greenhouse.
     * 
     * @pre memento should not be nullptr
     * @post Player state is restored to saved state
     * 
     * @see Memento
     * @see Game::loadGame()
     */
    void setMemento(Memento* memento);

private:
    float money;                    ///< Current player funds
    float rating;                   ///< Player reputation (0-5)
    int day;                        ///< Current game day
    int hour;                       ///< Current game hour (0-23)
    int minute;                     ///< Current game minute (0-59)
    bool safe;                      ///< Protection status
    
    float timeAccumulator;          ///< Accumulates real time for game time conversion
    
    Inventory* inventory;           ///< Player's plant inventory
    Greenhouse* plot;               ///< Player's greenhouse
    std::vector<Worker*> workers;   ///< Hired workers list
    InventoryUI* inventoryUI;       ///< UI for inventory display
};