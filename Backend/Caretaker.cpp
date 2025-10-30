#include "Caretaker.h"

Caretaker::Caretaker() : currentIndex(-1) {}

Caretaker::~Caretaker() {
    for (auto memento : mementos) {
        delete memento;
    }
}

void Caretaker::addMemento(Memento* memento) 
{
    while (mementos.size() > currentIndex + 1) 
    {
        delete mementos.back();
        mementos.pop_back();
    }
    
    if (mementos.size() >= MAX_MEMENTOS) 
    {
        delete mementos.front();
        mementos.erase(mementos.begin());
        if (currentIndex > 0) 
        {
            currentIndex--;
        }
    }
    
    mementos.push_back(memento);
    currentIndex++;
}

Memento* Caretaker::getMemento(int index) const 
{
    if (index >= 0 && index < mementos.size()) 
    {
        return mementos[index];
    }

    return nullptr;
}

Memento* Caretaker::undo() 
{
    if (currentIndex > 0) 
    {
        currentIndex--;
        return mementos[currentIndex];
    }

    return nullptr;
}

Memento* Caretaker::redo() 
{
    if (currentIndex < mementos.size() - 1) 
    {
        currentIndex++;
        return mementos[currentIndex];
    }

    return nullptr;
}

bool Caretaker::canUndo() const 
{
    return currentIndex > 0;
}

bool Caretaker::canRedo() const 
{
    return currentIndex < mementos.size() - 1;
}

int Caretaker::getMementoCount() const 
{
    return mementos.size();
}

int Caretaker::getCurrentIndex() const 
{
    return currentIndex;
}

int Caretaker::getMaxMementos() const 
{
    return MAX_MEMENTOS;
}