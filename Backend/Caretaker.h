/**
 * @file Caretaker.h
 * @brief Caretaker for managing game state persistence with Memento pattern.
 * @details Handles saving and loading of game state to/from disk files.
 *          Provides automatic file persistence whenever state is updated.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Memento
 * @see Game
 */

#pragma once

#include "Memento.h"
#include <string>

/**
 * @class Caretaker
 * @brief Manages persistence of game state using Memento objects.
 * 
 * The Caretaker class implements the Caretaker role in the Memento pattern.
 * It:
 * - Stores the current game state Memento
 * - Automatically saves state to disk when updated
 * - Loads state from disk during initialization
 * - Provides cleanup and deletion functionality
 * 
 * The Caretaker uses a file-based storage system with a simple text format:
 * ```
 * INVENTORY:Lettuce:5|Tomato:3
 * GREENHOUSE:plant_data...
 * WORKERS:worker_data...
 * MONEY:1500.50
 * RATING:85
 * DAY:5
 * HOUR:14
 * MINUTE:30
 * ```
 * 
 * @par Design Pattern: Memento
 * Acts as the Caretaker, managing storage and restoration of Memento objects
 * without exposing the internal details of game state.
 * 
 * @par File Persistence
 * - Automatically saves to file when addMemento() is called
 * - Automatically loads from file during construction
 * - Supports manual file deletion via deleteData()
 * 
 * @par Memory Management
 * The Caretaker owns the Memento object. When a new Memento is added, the
 * previous one is deleted. The destructor also cleans up the current Memento.
 * 
 * @example
 * @code
 * // Create caretaker with auto-load from file
 * Caretaker caretaker("game_state.txt");
 * 
 * // Create and save a new memento
 * Memento* state = new Memento(...);
 * caretaker.addMemento(state);  // Automatically saves to file
 * 
 * // Retrieve saved state
 * Memento* loaded = caretaker.getMemento();
 * float money = loaded->getMoney();
 *
 * // Clean up (deletes from memory and disk)
 * caretaker.deleteData();
 * @endcode
 * 
 * @see Memento
 * @see Game
 */
class Caretaker {
private:
    Memento* currentMemento;        ///< The current saved state
    std::string saveFile;           ///< Path to the save file

public:
    /**
     * @brief Constructor with optional save file path.
     * @param filename Path to the save file (default: "game_state.txt").
     * 
     * @details Upon construction:
     *         - Attempts to load existing save file if it exists
     *         - Creates a new empty Caretaker if file doesn't exist
     *         - Uses loadFromFile() to restore previous state
     */
    Caretaker(const std::string& filename = "game_state.txt");

    /**
     * @brief Destructor.
     * @details Cleans up the current Memento if one exists.
     *          Does not delete the save file.
     */
    ~Caretaker();

    /**
     * @brief Adds a new memento and saves it to disk.
     * @param memento Pointer to the Memento to store.
     * 
     * @details If a Memento already exists, it is deleted before storing the new one.
     *         Automatically calls saveToFile() to persist the state.
     * 
     * @pre memento must not be nullptr (checked internally)
     * @post The memento is stored and saved to disk
     * @post Any previous memento is deleted
     */
    void addMemento(Memento* memento);
    
    /**
     * @brief Retrieves the current memento.
     * @return Pointer to the current Memento, or nullptr if none exists.
     * 
     * @note The returned Memento is owned by the Caretaker and should not be deleted
     *       by the caller.
     */
    Memento* getMemento() const;
    
    /**
     * @brief Loads game state from disk file.
     * @details Parses the save file and creates a new Memento with the loaded data.
     *          Called automatically during construction.
     * 
     * @details File format (one key-value pair per line):
     *         KEY:value format, where value may contain colons for nested data
     *         Expected keys: INVENTORY, GREENHOUSE, WORKERS, MONEY, RATING, 
     *                       DAY, HOUR, MINUTE
     * 
     * @note If file doesn't exist, this method does nothing silently.
     * @post If successful, currentMemento is set with loaded data
     */
    void loadFromFile();
    
    /**
     * @brief Deletes all saved data from memory and disk.
     * @details Removes the save file and clears the current Memento.
     * 
     * @post currentMemento is deleted and set to nullptr
     * @post Save file is removed from disk (if it exists)
     * @post Exceptions during file deletion are silently ignored
     */
    void deleteData();

private:
    /**
     * @brief Saves the current memento to disk file.
     * @details Writes the memento's data to the save file in key-value format.
     * 
     * @details Output format:
     *         Each line contains "KEY:value" pair
     *         Lines: INVENTORY, GREENHOUSE, WORKERS, MONEY, RATING, DAY, HOUR, MINUTE
     * 
     * @note Does nothing if currentMemento is nullptr
     * @post Save file is written and closed
     */
    void saveToFile();
};