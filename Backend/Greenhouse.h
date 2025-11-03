/**
 * @file Greenhouse.h
 * @brief Plant growth environment management system
 *
 * @pattern Observer - Notifies workers of plant state changes
 * @pattern Composite - Manages collection of plants
 */

#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @class Greenhouse
 * @brief Manages plant placement, growth and harvesting
 */
class Greenhouse : public Subject {
public:
    /**
     * @brief Construct with inventory reference
     * @param inv Pointer to inventory for harvested plants
     */
    Greenhouse(Inventory* inv);

    /**
     * @brief Default constructor
     */
    Greenhouse();

    /**
     * @brief Destroy and cleanup all plants
     */
    ~Greenhouse();
    
    /**
     * @brief Add plant at specific position
     * @param plant Plant to add
     * @param position Target position
     * @return true if added successfully
     */
    bool addPlant(Plant* plant, int position);

    /**
     * @brief Add plant to first available position
     * @param plant Plant to add
     * @return true if added successfully
     */
    bool addPlant(Plant* plant);

    /**
     * @brief Remove plant at position
     * @param position Position to clear
     * @return true if removed successfully
     */
    bool removePlant(int position);

    /**
     * @brief Harvest plant to inventory
     * @param position Position to harvest
     * @return true if harvested successfully
     */
    bool harvestPlant(int position);

    /**
     * @brief Harvest specific plant to inventory
     * @param plant Plant pointer to harvest
     * @return true if harvested successfully
     */
    bool harvestPlant(Plant* plant);
    
    /**
     * @brief Get plant at position
     * @param position Position to check
     * @return Plant* Pointer to plant or nullptr
     */
    Plant* getPlant(int position);

    /**
     * @brief Get plant type at position
     * @param position Position to check
     * @return std::string Plant type or "Empty"
     */
    std::string getPlot(int position);

    /**
     * @brief Get number of plants
     * @return int Current plant count
     */
    int getSize();

    /**
     * @brief Get max plant capacity
     * @return int Maximum number of plants
     */
    int getCapacity();

    /**
     * @brief Increase max capacity
     * @param amount Amount to increase
     * @return true if increased successfully
     */
    bool increaseCapacity(int amount);

    /**
     * @brief Set inventory reference
     * @param inv Pointer to inventory
     */
    void setInventory(Inventory* inv);
    
    // Observer pattern methods
    void notify() override;
    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    
    /**
     * @brief Update single plant
     * @param position Plant position to tick
     */
    void tickPlant(int position);

    /**
     * @brief Update all plants
     */
    void tickAllPlants();
    
private:
    int size;
    std::vector<Plant*> plots;
    int capacity;
    Inventory* inventory;
};