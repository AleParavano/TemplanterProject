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
    int day;
    int hour;
    int minute;

public:
    Player();
    ~Player();

    Inventory* getInventory() const;
    Worker* getWorkers() const;
    Greenhouse* getPlot() const;
    float getMoney() const;
    int getRating() const;

    int getDay() const;
    int getHour() const;
    int getMinute() const;
    std::string getTimeString() const;
    std::string getFullTimeString() const;

    void setInventory(Inventory* inv);
    void setWorkers(Worker* w);
    void setPlot(Greenhouse* gh);
    void setMoney(float m);
    void setRating(int r);

    void setDay(int d);
    void setHour(int h);
    void setMinute(int m);
    bool isNewDay() const;

    Memento* createMemento() const;
    void setMemento(Memento* memento);
};