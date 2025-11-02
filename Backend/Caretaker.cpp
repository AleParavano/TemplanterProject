#include "Caretaker.h"
#include <fstream>
#include <sstream>
#include <filesystem>

Caretaker::Caretaker(const std::string& filename) : currentMemento(nullptr), saveFile(filename) 
{
    loadFromFile();
}

Caretaker::~Caretaker() 
{
    if (currentMemento) 
    {
        delete currentMemento;
    }
}

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

Memento* Caretaker::getMemento() const 
{
    return currentMemento;
}

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