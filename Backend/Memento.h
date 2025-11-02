#pragma once

#include <string>

class Inventory;
class Worker;
class Greenhouse;

class Memento 
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
    Memento(Inventory* inv, Worker* work, Greenhouse* gh, float m, int r, int d, int h, int min);
    ~Memento();

    Inventory* getInventory() const;
    Worker* getWorkers() const;
    Greenhouse* getPlot() const;
    float getMoney() const;
    int getRating() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
};