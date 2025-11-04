#pragma once

#include "Memento.h"
#include <string>

/**
 * @class Caretaker
 * @brief Manages the stored Mementos, acting as a save-game manager.
 * * The Caretaker is responsible for keeping the Memento objects safe,
 * but it never operates on or examines the content of the Mementos.
 * In this implementation, it manages a single "current" Memento and
 * handles its persistence by saving and loading it from a file.
 */
class Caretaker {
private:
    /**
     * @brief Pointer to the currently managed Memento object.
     */
    Memento* currentMemento;
    
    /**
     * @brief The filename used for saving and loading the game state.
     */
    std::string saveFile;

public:
    /**
     * @brief Constructor for the Caretaker.
     * @param filename The name of the file to use for persistence (default is "game_state.txt").
     */
    Caretaker(const std::string& filename = "game_state.txt");
    
    /**
     * @brief Destructor for the Caretaker.
     */
    ~Caretaker();

    /**
     * @brief Stores a new Memento and automatically saves it to the designated file.
     * * If there was an existing Memento, it is deleted before the new one is stored.
     * @param memento A pointer to the Memento object to be stored.
     */
    void addMemento(Memento* memento);
    
    /**
     * @brief Retrieves the currently managed Memento.
     * @return A pointer to the current Memento.
     */
    Memento* getMemento() const;
    
    /**
     * @brief Loads the last saved Memento state from the file.
     * * If a Memento is successfully loaded, the existing currentMemento is replaced.
     */
    void loadFromFile();
    
    /**
     * @brief Deletes the persistent save file and clears the current Memento.
     */
    void deleteData();

private:
    /**
     * @brief Internal method to save the current Memento to the designated file.
     * @details This function is automatically called by addMemento().
     */
    void saveToFile();
};