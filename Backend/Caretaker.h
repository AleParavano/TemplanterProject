/**
 * @file Caretaker.h
 * @brief Declaration of the Caretaker class for managing Memento persistence.
 * 
 * The Caretaker is responsible for storing and retrieving Memento objects,
 * as well as managing their persistence to disk. It provides automatic save/load
 * functionality for game state management.
 * 
 * @pattern Memento - Caretaker role in the Memento pattern
 */
#pragma once

#include "Memento.h"
#include <string>

/**
 * @class Caretaker
 * @brief Manages Memento objects and handles game state persistence.
 * 
 * The Caretaker stores a single Memento representing the current saved game state.
 * It automatically saves to disk when a new Memento is added and can load from disk
 * on construction. This class never accesses the internal state of Mementos.
 * 
 * @pattern Memento - Caretaker component
 */
class Caretaker {
private:
    Memento* currentMemento;
    std::string saveFile;

public:
    Caretaker(const std::string& filename = "game_state.txt");
    ~Caretaker();

    // Add memento - automatically saves to file
    void addMemento(Memento* memento);
    
    // Get current memento
    Memento* getMemento() const;
    
    // Load from file
    void loadFromFile();
    
    // Delete all saved data from file
    void deleteData();

private:
    void saveToFile();
};