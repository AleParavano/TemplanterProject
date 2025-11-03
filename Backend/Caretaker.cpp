/**
 * @file Caretaker.cpp
 * @brief Handles saving and loading game state to keep your progress safe.
 * 
 * The Caretaker takes care of your game saves by managing Memento objects and writing
 * them to disk. It's like your game's memory keeper - it remembers where you left off
 * so you can pick up right where you stopped playing.
 * 
 * @pattern Memento - Acts as the caretaker who stores mementos without peeking inside
 */

#include "Caretaker.h"
#include <fstream>
#include <sstream>
#include <filesystem>

/**
 * @brief Constructs a Caretaker with the specified save file.
 * 
 * Initializes the Caretaker and attempts to load any existing save data
 * from the specified file. If no file exists, the Caretaker starts with
 * no stored Memento.
 * 
 * @param filename The name of the file to use for save/load operations (default: "game_state.txt")
 */
Caretaker::Caretaker(const std::string& filename) : currentMemento(nullptr), saveFile(filename) 
{
    loadFromFile();
}

/**
 * @brief Destructor that cleans up the stored Memento.
 * 
 * Deallocates the current Memento if one exists. Does not delete the save file.
 */
Caretaker::~Caretaker() 
{
    if (currentMemento) 
    {
        delete currentMemento;
    }
}

/**
 * @brief Stores a new Memento and automatically saves it to file.
 * 
 * Replaces the current Memento with the new one (deleting the old Memento if it exists)
 * and immediately writes the new state to the save file. This ensures game progress
 * is not lost.
 * 
 * @param memento Pointer to the Memento to store (ownership transferred to Caretaker)
 * 
 * @note Does nothing if memento is nullptr
 * @note Automatically calls saveToFile() after storing
 */
void Caretaker::addMemento(Memento* memento) 
{
    if (!memento) return;
    
    if (currentMemento) 
    {
        delete currentMemento;
    }
    
    currentMemento = memento;
    saveToFile();
}

/**
 * @brief Retrieves the currently stored Memento.
 * 
 * Returns a pointer to the Memento without transferring ownership.
 * The Caretaker retains ownership and will delete the Memento when destroyed.
 * 
 * @return Memento* Pointer to the current Memento, or nullptr if none exists
 */
Memento* Caretaker::getMemento() const 
{
    return currentMemento;
}

/**
 * @brief Saves the current Memento to disk in text format.
 * 
 * Writes all game state data from the current Memento to the save file.
 * The format includes inventory data, greenhouse data, workers, money, rating,
 * and time information. Each field is written on a separate line with a key-value format.
 * 
 * @note Does nothing if no Memento is currently stored
 * @note Does nothing if file cannot be opened for writing
 * @note This is a private helper method called automatically by addMemento()
 */
void Caretaker::saveToFile() 
{
    if (!currentMemento) return;
    
    std::ofstream file(saveFile);
    if (!file.is_open()) return;
    
    file << "INVENTORY:" << currentMemento->getInventoryData() << "\n";
    file << "GREENHOUSE:" << currentMemento->getGreenhouseData() << "\n";
    file << "WORKERS:" << currentMemento->getWorkerData() << "\n";
    file << "MONEY:" << currentMemento->getMoney() << "\n";
    file << "RATING:" << currentMemento->getRating() << "\n";
    file << "DAY:" << currentMemento->getDay() << "\n";
    file << "HOUR:" << currentMemento->getHour() << "\n";
    file << "MINUTE:" << currentMemento->getMinute() << "\n";
    
    file.close();
}

/**
 * @brief Loads game state from the save file and creates a Memento.
 * 
 * Reads the save file and parses the stored game state data. Creates a new Memento
 * object containing the loaded state. If the file doesn't exist or cannot be read,
 * the Caretaker remains empty.
 * 
 * @note Called automatically by the constructor
 * @note Handles parsing errors gracefully by skipping invalid lines
 */
void Caretaker::loadFromFile() 
{
    std::ifstream file(saveFile);
    if (!file.is_open()) return;
    
    std::string line;
    std::string inv, gh, workers;
    float money = 0.0f;
    int rating = 0, day = 1, hour = 6, minute = 0;
    
    while (std::getline(file, line)) 
    {
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;
        
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);
        
        try 
        {
            if (key == "INVENTORY") {
                inv = value;
            } else if (key == "GREENHOUSE") {
                gh = value;
            } else if (key == "WORKERS") {
                workers = value;
            } else if (key == "MONEY") {
                money = std::stof(value);
            } else if (key == "RATING") {
                rating = std::stoi(value);
            } else if (key == "DAY") {
                day = std::stoi(value);
            } else if (key == "HOUR") {
                hour = std::stoi(value);
            } else if (key == "MINUTE") {
                minute = std::stoi(value);
            }
        } 
        catch (...) 
        {
            continue;
        }
    }
    
    file.close();
    
    if (!inv.empty() || !gh.empty() || !workers.empty()) 
    {
        currentMemento = new Memento(inv, workers, gh, money, rating, day, hour, minute);
    }
}

/**
 * @brief Deletes all saved game data from memory and disk.
 * 
 * Removes the current Memento from memory and deletes the save file from disk.
 * This operation cannot be undone. Used for clearing save data or resetting the game.
 * 
 * @note Handles file system errors gracefully
 */
void Caretaker::deleteData() 
{
    if (currentMemento) 
    {
        delete currentMemento;
        currentMemento = nullptr;
    }
    
    try 
    {
        if (std::filesystem::exists(saveFile)) 
        {
            std::filesystem::remove(saveFile);
        }
    } 
    catch (...) {}
}