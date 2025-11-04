#pragma once
#include <string>

/**
 * @class Memento
 * @brief The Memento class stores the state of an Originator object (e.g., a game state) 
 * at a particular time, preventing direct access to the state data by other objects.
 * * This class is part of the Memento design pattern. It encapsulates data 
 * related to the game's inventory, workers, greenhouse, finances, rating, and time.
 */
class Memento 
{
public:
    /**
     * @brief Constructs a Memento object with the full state data.
     * * @param inv The serialized data for the inventory state.
     * @param work The serialized data for the worker state.
     * @param gh The serialized data for the greenhouse state.
     * @param m The current amount of money.
     * @param r The current rating.
     * @param d The current day.
     * @param h The current hour.
     * @param min The current minute.
     */
    Memento(const std::string& inv, const std::string& work, const std::string& gh, float m, int r, int d, int h, int min);
    
    /**
     * @brief Destroys the Memento object.
     */
    ~Memento();
    
    /**
     * @brief Gets the inventory state data.
     * @return A constant reference to the inventory data string.
     */
    const std::string& getInventoryData() const;
    
    /**
     * @brief Gets the worker state data.
     * @return A constant reference to the worker data string.
     */
    const std::string& getWorkerData() const;
    
    /**
     * @brief Gets the greenhouse state data.
     * @return A constant reference to the greenhouse data string.
     */
    const std::string& getGreenhouseData() const;
    
    /**
     * @brief Gets the current money amount.
     * @return The current money amount as a float.
     */
    float getMoney() const;
    
    /**
     * @brief Gets the current rating.
     * @return The current rating as an integer.
     */
    int getRating() const;
    
    /**
     * @brief Gets the current day.
     * @return The current day as an integer.
     */
    int getDay() const;
    
    /**
     * @brief Gets the current hour.
     * @return The current hour as an integer.
     */
    int getHour() const;
    
    /**
     * @brief Gets the current minute.
     * @return The current minute as an integer.
     */
    int getMinute() const;

private:
    /** @brief Serialized string containing the state of the inventory. */
    std::string inventoryData;
    
    /** @brief Serialized string containing the state of the workers. */
    std::string workerData;
    
    /** @brief Serialized string containing the state of the greenhouse. */
    std::string greenhouseData;
    
    /** @brief The current amount of money in the game. */
    float money;
    
    /** @brief The current game rating/reputation. */
    int rating;
    
    /** @brief The current in-game day. */
    int day;
    
    /** @brief The current in-game hour. */
    int hour;
    
    /** @brief The current in-game minute. */
    int minute;
};
