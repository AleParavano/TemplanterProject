#pragma once

#include "Memento.h"
#include <string>

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