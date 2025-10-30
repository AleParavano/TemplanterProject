#pragma once

#include "Memento.h"
#include <vector>

class Caretaker {
private:
    std::vector<Memento*> mementos;
    int currentIndex;
    static const int MAX_MEMENTOS = 3;

public:
    Caretaker();
    ~Caretaker();

    void addMemento(Memento* memento);
    Memento* getMemento(int index) const;
    Memento* undo();
    Memento* redo();
    bool canUndo() const;
    bool canRedo() const;
    int getMementoCount() const;
    int getCurrentIndex() const;
    int getMaxMementos() const;
};