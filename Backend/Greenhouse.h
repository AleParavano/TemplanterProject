#pragma once
#include <vector>
#include <string> // Added include for std::string return type in getPlot
#include "Plant.h"
#include "Inventory.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @class Greenhouse
 * @brief Manages a collection of Plant objects and acts as the central Subject
 * * in the Observer pattern for state changes.
 * * It handles plant management (adding, removing, ticking) and capacity.
 */
class Greenhouse : public Subject {
public:
    /**
     * @brief Constructor for Greenhouse with an existing Inventory.
     * @param inv Pointer to the Inventory object used for storing harvested items.
     */
    Greenhouse(Inventory* inv);
    
    /**
     * @brief Default constructor for Greenhouse.
     */
    Greenhouse();
    
    /**
     * @brief Destructor for the Greenhouse. Responsible for cleaning up plant pointers.
     */
    ~Greenhouse();
    
    /**
     * @brief Adds a plant to a specific plot position if the plot is empty and within capacity.
     * @param plant Pointer to the Plant object to add.
     * @param position The 0-indexed plot position where the plant should be placed.
     * @return true if the plant was successfully added, false otherwise.
     */
    bool addPlant(Plant* plant, int position);
    
    /**
     * @brief Adds a plant to the first available plot position.
     * @param plant Pointer to the Plant object to add.
     * @return true if the plant was successfully added, false otherwise.
     */
    bool addPlant(Plant* plant);
    
    /**
     * @brief Removes a plant at a specific position, clearing the plot.
     * @param position The 0-indexed plot position to clear.
     * @return true if a plant was removed, false if the position was empty or invalid.
     */
    bool removePlant(int position);
    
    /**
     * @brief Harvests the plant at a specific position, adding its yield to the Inventory.
     * @param position The 0-indexed plot position to harvest from.
     * @return true if the plant was successfully harvested, false otherwise.
     */
    bool harvestPlant(int position);
    
    /**
     * @brief Finds and harvests a plant based on its pointer, adding its yield to the Inventory.
     * @param plant Pointer to the Plant object to harvest.
     * @return true if the plant was successfully harvested, false otherwise.
     */
    bool harvestPlant(Plant* plant);
    
    /**
     * @brief Gets the Plant object at a specific plot position.
     * @param position The 0-indexed plot position.
     * @return A pointer to the Plant object, or nullptr if the plot is empty or invalid.
     */
    Plant* getPlant(int position);
    
    /**
     * @brief Finds and returns a plant based on its pointer in the plots vector.
     * @param p Pointer to the Plant object to search for.
     * @return A pointer to the Plant if found, or nullptr otherwise.
     */
    Plant* getPlantByPointer(Plant* p) ;
    
    /**
     * @brief Gets a descriptive string representation of the plot content at a position.
     * @param position The 0-indexed plot position.
     * @return A string describing the plot content (e.g., plant type or "empty").
     */
    std::string getPlot(int position);
    
    /**
     * @brief Gets the current number of plants in the greenhouse.
     * @return The count of occupied plots (current size).
     */
    int getSize();
    
    /**
     * @brief Gets the total capacity of the greenhouse (number of available plots).
     * @return The maximum number of plants the greenhouse can hold.
     */
    int getCapacity();
    
    /**
     * @brief Increases the total capacity of the greenhouse.
     * @param amount The number of new plots to add.
     * @return true if capacity was successfully increased, false otherwise.
     */
    bool increaseCapacity(int amount);
    
    /**
     * @brief Sets or updates the Inventory object associated with the greenhouse.
     * @param inv Pointer to the Inventory object.
     */
    void setInventory(Inventory* inv);
    
    // Subject pattern implementation
    
    /**
     * @brief Notifies all attached Observer objects about a state change.
     * * This implementation is inherited from Subject.
     */
    void notify() override;
    
    /**
     * @brief Attaches a new Observer to the Greenhouse (Subject).
     * @param observer Pointer to the Observer object to attach.
     */
    void attach(Observer* observer) override;
    
    /**
     * @brief Detaches an Observer from the Greenhouse (Subject).
     * @param observer Pointer to the Observer object to detach.
     */
    void detach(Observer* observer) override;
    
    // Called when a plant ticks
    
    /**
     * @brief Advances the state (e.g., growth) of the plant at a specific position.
     * * Notifies Observers if the plant's state changes significantly.
     * @param position The 0-indexed plot position of the plant to tick.
     */
    void tickPlant(int position);
    
    /**
     * @brief Advances the state (e.g., growth) of all plants currently in the greenhouse.
     */
    void tickAllPlants();
    
private:
    /**
     * @brief The current number of plants occupying the plots.
     */
    int size;
    
    /**
     * @brief A vector representing the plots, holding pointers to Plant objects.
     */
    std::vector<Plant*> plots;
    
    /**
     * @brief The maximum number of plants the greenhouse can hold (size of the vector).
     */
    int capacity;
    
    /**
     * @brief Pointer to the Inventory system used to store harvested goods.
     */
    Inventory* inventory;

    
};