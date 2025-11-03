/**
 * @file Player.h
 * @brief Player state and resource management
 *
 * Manages player resources, inventory, workers, and game state.
 * Integrates with Memento pattern for save/load functionality.
 *
 * @pattern Memento - Player state storage
 * @pattern Facade - Centralizes game systems access
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
 * @brief Central player state manager
 *
 * Manages:
 * - Resources (money, rating)
 * - Game time
 * - Inventory
 * - Greenhouse
 * - Workers
 */
class Player {
public:
    /**
     * @brief Initialize player with default state
     */
    Player();

    /**
     * @brief Clean up owned resources
     */
    ~Player();
    
    // Resource getters/setters
    float getMoney() const;
    void setMoney(float amount);
    void addMoney(float amount);
    void subtractMoney(float amount);
    
    // Rating methods
    float getRating() const;
    void setRating(float r);
    void addRating(float r);
    void subtractRating(float r);
    
    // Time methods
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    void setTime(int d, int h, int m);
    void advanceTime(int minutes);
    void UpdateGameTime(float dt);

    // Inventory/plot methods
    InventoryUI* getInventoryUI() const { return inventoryUI; }
    
    Inventory* getInventory() const;
    Greenhouse* getPlot() const;
    
    // Worker methods
    void addWorker(Worker* worker);
    void fireWorker(int index);
    Worker* getWorker(int index) const;
    int getWorkerCount() const;
    const std::vector<Worker*>& getWorkers() ;
    
    // Time string methods
    std::string getTimeString() const;
    
    // Protection methods
    void setProtected(bool prot);
    bool isProtected();

    // Save/restore methods
    Memento* createMemento() const;
    void setMemento(Memento* memento);

private:
    float money;
    float rating;
    int day;
    int hour;
    int minute;
    bool safe;
    
    float timeAccumulator;
    
    Inventory* inventory;
    Greenhouse* plot;
    std::vector<Worker*> workers;
    InventoryUI* inventoryUI; 
};