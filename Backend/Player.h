#pragma once

#include <string>
#include <vector>
#include "Inventory.h"
#include "Greenhouse.h"
#include "Worker.h"
#include "Memento.h"
#include "../Frontend/InventoryUI.h" // <<< Final Check: InventoryUI included >>>

/**
 * @class Player
 * @brief The central class representing the player and managing the entire game state.
 * * This class acts as the **Originator** in the Memento pattern, capable of creating a snapshot 
 * (Memento) of its internal state and restoring it from a Memento.
 * * It handles finances, game time, worker management, and holds references to key components 
 * like Inventory and Greenhouse.
 */
class Player 
{
public:
    /**
     * @brief Constructs a new Player object, initializing game components and starting state.
     */
    Player();
    
    /**
     * @brief Destructor for the Player class, responsible for cleaning up dynamically allocated resources (e.g., workers, inventory, plot).
     */
    ~Player();
    
    // --- Money Management ---
    /**
     * @brief Gets the current amount of money the player has.
     * @return The current money as a float.
     */
    float getMoney() const;
    
    /**
     * @brief Sets the player's money to a specific amount.
     * @param amount The new money amount.
     */
    void setMoney(float amount);
    
    /**
     * @brief Adds a specified amount of money to the player's balance.
     * @param amount The amount to add.
     */
    void addMoney(float amount);
    
    /**
     * @brief Subtracts a specified amount of money from the player's balance.
     * @param amount The amount to subtract.
     */
    void subtractMoney(float amount);
    
    // --- Rating Management ---
    /**
     * @brief Gets the player's current rating/reputation.
     * @return The current rating as a float.
     */
    float getRating() const;
    
    /**
     * @brief Sets the player's rating to a specific value.
     * @param r The new rating value.
     */
    void setRating(float r);
    
    /**
     * @brief Increases the player's rating by a specified amount.
     * @param r The amount to add to the rating.
     */
    void addRating(float r);
    
    /**
     * @brief Decreases the player's rating by a specified amount.
     * @param r The amount to subtract from the rating.
     */
    void subtractRating(float r);
    
    // --- Time Management ---
    /**
     * @brief Gets the current in-game day.
     * @return The current day number.
     */
    int getDay() const;
    
    /**
     * @brief Gets the current in-game hour (0-23).
     * @return The current hour.
     */
    int getHour() const;
    
    /**
     * @brief Gets the current in-game minute (0-59).
     * @return The current minute.
     */
    int getMinute() const;
    
    /**
     * @brief Sets the game time to a specific day, hour, and minute.
     * @param d The new day.
     * @param h The new hour.
     * @param m The new minute.
     */
    void setTime(int d, int h, int m);
    
    /**
     * @brief Advances the game time by a specified number of minutes.
     * @param minutes The number of minutes to advance.
     */
    void advanceTime(int minutes);
    
    /**
     * @brief Updates the game time based on real-world delta time, accumulating minutes.
     * @param dt The delta time (time passed since the last frame) in seconds.
     */
    void UpdateGameTime(float dt); // <<< UpdateGameTime added >>>

    // --- Component Getters ---
    /**
     * @brief Gets the InventoryUI component associated with the player's inventory (Frontend element).
     * @return A pointer to the InventoryUI object.
     */
    InventoryUI* getInventoryUI() const { return inventoryUI; }
    
    /**
     * @brief Gets the player's Inventory object.
     * @return A pointer to the Inventory object.
     */
    Inventory* getInventory() const;
    
    /**
     * @brief Gets the player's Greenhouse object (plot of land).
     * @return A pointer to the Greenhouse object.
     */
    Greenhouse* getPlot() const;
    
    // --- Worker Management ---
    /**
     * @brief Adds a new worker to the player's team.
     * @param worker A pointer to the Worker object to add.
     */
    void addWorker(Worker* worker); // <<< addWorker added >>>
    
    /**
     * @brief Fires (removes and deletes) a worker at a specific index.
     * @param index The index of the worker in the worker vector.
     */
    void fireWorker(int index);
    
    /**
     * @brief Gets a worker by their index in the vector.
     * @param index The index of the worker.
     * @return A pointer to the Worker object.
     */
    Worker* getWorker(int index) const;
    
    /**
     * @brief Gets the total number of workers the player employs.
     * @return The count of workers.
     */
    int getWorkerCount() const;
    
    /**
     * @brief Pauses all workers, preventing them from performing automated actions.
     */
    void pauseWorkers();
    
    /**
     * @brief Resumes all workers, allowing them to perform automated actions.
     */
    void startWorkers() ;
    
    /**
     * @brief Gets a constant reference to the vector of workers.
     * @return A constant reference to the worker vector.
     */
    const std::vector<Worker*>& getWorkers() ;
    
    /**
     * @brief Generates a formatted string representation of the current game time (e.g., "Day 1, 09:30").
     * @return A string representing the current time.
     */
    std::string getTimeString() const; // <<< getTimeString added >>>
    
    // --- Protection (Safety) Management ---
    /**
     * @brief Sets the 'safe' status of the game (e.g., against random events).
     * @param prot Boolean flag where true means protected/safe.
     */
    void setProtected(bool prot);
    
    /**
     * @brief Checks if the player's game state is currently protected/safe.
     * @return true if protected, false otherwise.
     */
    bool isProtected();

    // --- Memento Pattern (Originator interface) ---
    /**
     * @brief Creates a Memento object containing a snapshot of the current game state (money, time, inventory, greenhouse, workers).
     * @return A pointer to the newly created Memento object.
     */
    Memento* createMemento() const;
    
    /**
     * @brief Restores the player's state from a provided Memento object.
     * @param memento A pointer to the Memento containing the saved state.
     */
    void setMemento(Memento* memento);

private:
    /** @brief The player's current money balance. */
    float money;
    
    /** @brief The player's current reputation or rating. */
    float rating;
    
    /** @brief The current day in the game. */
    int day;
    
    /** @brief The current hour (0-23) in the game. */
    int hour;
    
    /** @brief The current minute (0-59) in the game. */
    int minute;
    
    /** @brief Flag indicating if the game state is protected (e.g., against random negative events). */
    bool safe;
    
    /** @brief Accumulates delta time for smooth, frame-rate independent time updates. */
    float timeAccumulator; // <<< timeAccumulator added >>>
    
    /** @brief The player's inventory of seeds, fertilizer, and harvestable items. */
    Inventory* inventory;
    
    /** @brief The player's greenhouse or plot of land containing plants. */
    Greenhouse* plot;
    
    /** @brief A list of workers employed by the player. */
    std::vector<Worker*> workers;
    
    /** @brief A reference to the Inventory UI component for direct interaction with the frontend. */
    InventoryUI* inventoryUI; // <<< InventoryUI member added >>>
};