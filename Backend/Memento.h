/**
 * @file Memento.h
 * @brief Game state snapshot system using the Memento pattern
 *
 * Implements the Memento pattern to capture and restore game state including
 * inventory, greenhouse, workers, and player attributes.
 *
 * @pattern Memento - Captures game state for save/restore
 */

#pragma once
#include <string>

/**
 * @class Memento
 * @brief Stores a snapshot of the game state
 *
 * Contains serialized data for all major game components and player stats.
 * Used in conjunction with Caretaker for save/load functionality.
 */
class Memento 
{
public:
    Memento(const std::string& inv, const std::string& work, const std::string& gh, float m, int r, int d, int h, int min);
    ~Memento();
    
    const std::string& getInventoryData() const;
    const std::string& getWorkerData() const;
    const std::string& getGreenhouseData() const;
    
    float getMoney() const;
    int getRating() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;

    private:
    std::string inventoryData;
    std::string workerData;
    std::string greenhouseData;
    
    float money;
    int rating;
    int day;
    int hour;
    int minute;
};