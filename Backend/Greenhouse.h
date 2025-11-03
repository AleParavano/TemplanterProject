/**
 * @file Greenhouse.h
 * @brief Greenhouse management system declaration.
 * 
 * Defines the Greenhouse class which manages plant storage and growth.
 */

#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @class Greenhouse
 * @brief Manages plant storage and growth conditions.
 * 
 * Handles plant inventory, placement, and environmental conditions
 * affecting plant growth within the greenhouse structure.
 */
class Greenhouse : public Subject {
public:
    Greenhouse(Inventory* inv);
    Greenhouse();
    ~Greenhouse();
    
    bool addPlant(Plant* plant, int position);
    bool addPlant(Plant* plant);
    bool removePlant(int position);
    bool harvestPlant(int position);
    bool harvestPlant(Plant* plant);
    
    Plant* getPlant(int position);
    std::string getPlot(int position);
    int getSize();
    int getCapacity();
    bool increaseCapacity(int amount);
    void setInventory(Inventory* inv);
    
    // Subject pattern implementation
    void notify() override;
    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    
    // Called when a plant ticks
    void tickPlant(int position);
    void tickAllPlants();
    
private:
    int size;
    std::vector<Plant*> plots;
    int capacity;
    Inventory* inventory;
};