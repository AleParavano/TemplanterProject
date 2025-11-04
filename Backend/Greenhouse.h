/**
 * @file Greenhouse.h
 * @brief Core greenhouse management system using Observer pattern.
 * @details Manages plant storage, growth ticking, and notifies observers of state changes.
 *          Implements the Subject role in the Observer pattern for plant care notifications.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Plant
 * @see Inventory
 * @see Subject
 * @see Observer
 */

#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @class Greenhouse
 * @brief Central hub for managing plant storage and growth in the nursery.
 * 
 * The Greenhouse class manages a collection of plants stored in plots and acts as
 * the Subject in the Observer pattern. It:
 * - Stores plants in a fixed or expandable number of plots
 * - Manages plant lifecycle (addition, removal, harvesting)
 * - Tracks plant growth through tick operations
 * - Notifies observers (workers) when plants need attention
 * - Connects to an Inventory for harvested plants
 * 
 * @par Design Pattern: Observer
 * Implements the Subject interface, allowing Workers to observe plant state changes
 * and be notified when plants need care.
 * 
 * @par Thread Safety
 * This class is not thread-safe. Concurrent access from multiple threads should be
 * protected with external synchronization.
 * 
 * @par Example Usage
 * @code
 * Inventory inv(10);
 * Greenhouse gh(&inv);
 * 
 * Plant* tomato = new Tomato();
 * gh.addPlant(tomato);
 * 
 * gh.tickAllPlants();  // Advance plant growth
 * gh.harvestPlant(0);  // Move plant to inventory
 * @endcode
 * 
 * @see Inventory
 * @see Plant
 * @see Observer
 */
class Greenhouse : public Subject {
public:
    /**
     * @brief Default constructor.
     * @details Creates a greenhouse with default capacity (56 plots) and no inventory.
     * 
     * @warning The inventory should be set using setInventory() before harvesting plants.
     */
    Greenhouse();

    /**
     * @brief Constructor with inventory.
     * @param inv Pointer to an Inventory instance for storing harvested plants.
     * @details Creates a greenhouse with default capacity (56 plots) and the provided inventory.
     * 
     * @pre inv should not be null for harvesting operations.
     */
    Greenhouse(Inventory* inv);

    /**
     * @brief Destructor.
     * @details Deletes all plants remaining in the greenhouse. Does not delete the
     *          inventory as it may be used elsewhere.
     */
    ~Greenhouse();
    
    /**
     * @brief Adds a plant to a specific plot position.
     * @param plant Pointer to the Plant to add.
     * @param position The plot index (0 to capacity-1).
     * @return true if the plant was successfully added, false if the position is invalid
     *         or already occupied.
     * 
     * @pre plant must not be nullptr
     * @pre position must be within [0, capacity)
     * @post If successful, size is incremented
     */
    bool addPlant(Plant* plant, int position);

    /**
     * @brief Adds a plant to the first available plot.
     * @param plant Pointer to the Plant to add.
     * @return true if the plant was successfully added, false if all plots are full.
     * 
     * @pre plant must not be nullptr
     * @post If successful, size is incremented
     */
    bool addPlant(Plant *plant);

    /**
     * @brief Removes and deletes a plant at the specified position.
     * @param position The plot index (0 to capacity-1).
     * @return true if a plant was successfully removed, false if the position is invalid
     *         or empty.
     * 
     * @post If successful, the plant is deleted and observers are notified
     * @post If successful, size is decremented
     */
    bool removePlant(int position);

    /**
     * @brief Harvests a plant at the specified position to inventory.
     * @param position The plot index (0 to capacity-1).
     * @return true if the plant was successfully harvested, false if:
     *         - Position is invalid
     *         - Plot is empty
     *         - Inventory is nullptr
     * 
     * @pre Inventory must be set before harvesting
     * @post If successful, the plant is moved to inventory and plot is cleared
     * @post If successful, observers are notified
     * @post If successful, size is decremented
     */
    bool harvestPlant(int position);

    /**
     * @brief Harvests a specific plant to inventory.
     * @param plant Pointer to the Plant to harvest.
     * @return true if the plant was found and harvested, false otherwise.
     * 
     * @pre Inventory must be set before harvesting
     * @post If successful, the plant is moved to inventory
     * @post If successful, observers are notified
     */
    bool harvestPlant(Plant *plant);
    
    /**
     * @brief Gets the plant at a specific position.
     * @param position The plot index (0 to capacity-1).
     * @return Pointer to the Plant at the position, or nullptr if empty or invalid.
     */
    Plant* getPlant(int position);

    /**
     * @brief Finds and returns a plant by pointer.
     * @param p Pointer to the Plant to locate.
     * @return The plant pointer if found in the greenhouse, nullptr otherwise.
     */
    Plant *getPlantByPointer(Plant *p) ;

    /**
     * @brief Gets the type of plant at a position as a string.
     * @param position The plot index (0 to capacity-1).
     * @return The plant type (e.g., "Tomato") or "Empty" if the plot is empty/invalid.
     */
    std::string getPlot(int position);

    /**
     * @brief Gets the current number of occupied plots.
     * @return Number of plants currently in the greenhouse.
     */
    int getSize();

    /**
     * @brief Gets the total number of available plots.
     * @return Maximum number of plants that can be stored.
     */
    int getCapacity();

    /**
     * @brief Increases the greenhouse capacity.
     * @param amount Number of plots to add.
     * @return true if capacity was increased, false if:
     *         - amount <= 0
     *         - New capacity would exceed 128 plots
     * 
     * @post If successful, capacity and plots vector are resized
     */
    bool increaseCapacity(int amount);

    /**
     * @brief Sets the inventory for harvested plants.
     * @param inv Pointer to an Inventory instance.
     * 
     * @note Call this before harvesting plants, or harvest operations will fail.
     */
    void setInventory(Inventory *inv);

    // Observer pattern implementation
    
    /**
     * @brief Attaches an observer (typically a worker) to this greenhouse.
     * @param observer Pointer to an Observer to attach.
     * 
     * @pre observer must not be nullptr
     * @post Observer is added to the list and will receive notifications
     */
    void attach(Observer* observer) override;

    /**
     * @brief Detaches an observer from this greenhouse.
     * @param observer Pointer to the Observer to remove.
     * 
     * @post If found, observer is removed and will no longer receive notifications
     */
    void detach(Observer* observer) override;

    /**
     * @brief Notifies all attached observers of state changes.
     * @details Called after plant operations to alert workers of changes.
     * 
     * @post All attached observers receive the update() call
     */
    void notify() override;
    
    /**
     * @brief Advances the growth of a plant at a specific position by one tick.
     * @param position The plot index (0 to capacity-1).
     * 
     * @post If successful, the plant's tick() method is called and observers are notified
     */
    void tickPlant(int position);

    /**
     * @brief Advances the growth of all plants in the greenhouse by one tick.
     * @details This is typically called once per game cycle to update all plant states.
     * 
     * @post All plants receive a tick() call and observers are notified once
     */
    void tickAllPlants();
    
private:
    int size;                           ///< Current number of occupied plots
    std::vector<Plant*> plots;          ///< Vector storing plant pointers or nullptr
    int capacity;                       ///< Maximum number of plots available
    Inventory* inventory;               ///< Pointer to inventory for harvested plants
};