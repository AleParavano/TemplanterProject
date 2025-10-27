#pragma once

#include "Inventory.h"
#include "Worker.h"
#include "Greenhouse.h"
#include "Memento.h"
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

class Player 
{
private:
    Inventory* inventory;
    Worker* workers;
    Greenhouse* plot;
    float money;
    int rating;
    int hour;
    int minute;
    std::atomic<bool> running;
    std::thread* clockThread;
    void runClock();

public:
    Player();
    ~Player();

    Inventory* getInventory() const;
    Worker* getWorkers() const;
    Greenhouse* getPlot() const;
    float getMoney() const;
    int getRating() const;
    std::string getTimeString() const;

    void setInventory(Inventory* inv);
    void setWorkers(Worker* w);
    void setPlot(Greenhouse* gh);
    void setMoney(float m);
    void setRating(int r);

    void startClock();
    void stopClock();

    Memento* createMemento() const;
    void setMemento(Memento* memento);
};