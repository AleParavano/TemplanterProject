#pragma once

#include <string>
#include <vector>
#include "Inventory.h"
#include "Greenhouse.h"
#include "Worker.h"
#include "Memento.h"

class Player 
{

public:
    Player();
    ~Player();
    
    float getMoney() const;
    void setMoney(float amount);
    void addMoney(float amount);
    void subtractMoney(float amount);
    void UpdateGameTime(float dt);
    
    int getRating() const;
    void setRating(int r);
    void addRating(int r);
    void subtractRating(int r);
    
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    void setTime(int d, int h, int m);
    void advanceTime(int minutes);
    
    Inventory* getInventory() const;
    Greenhouse* getPlot() const;
    
    void addWorker(Worker* worker);
    void fireWorker(int index);
    Worker* getWorker(int index) const;
    int getWorkerCount() const;
    const std::vector<Worker*>& getWorkers() const;
    
    
    void setProtected(bool prot);
    bool isProtected();

    Memento* createMemento() const;
    void setMemento(Memento* memento);
    std::string getTimeString() const;

    private:
    float money;
    int rating;
    int day;
    int hour;
    int minute;
    bool safe;

    float timeAccumulator = 0.0f;
    
    Inventory* inventory;
    Greenhouse* plot;
    std::vector<Worker*> workers;
};