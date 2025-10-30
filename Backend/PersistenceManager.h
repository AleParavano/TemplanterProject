#pragma once

#include "Caretaker.h"
#include <string>

class PersistenceManager 
{
    public:
    PersistenceManager(const std::string& filename = "game_saves.txt");
    ~PersistenceManager();
    
    bool saveMementos(const Caretaker* caretaker);
    bool loadMementos(Caretaker* caretaker);
    
    bool saveFileExists() const;
    bool deleteSaveFile();
    void setFilename(const std::string& filename);
    
    std::string getFilename() const;

    private:
    std::string saveFilename;
    std::string encodeString(const std::string& str) const;
    std::string decodeString(const std::string& str) const;
};