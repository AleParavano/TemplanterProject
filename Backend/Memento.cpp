#include "Memento.h"
#include "Inventory.h"
#include "Worker.h"
#include "Greenhouse.h"

Memento::Memento(Inventory* inv, Worker* work, Greenhouse* gh, float m, int r, int d, int h, int min) : inventory(nullptr), workers(nullptr), plot(nullptr), money(m), rating(r), day(d), hour(h), minute(min) 
{
    inventory = inv ? new Inventory(*inv) : nullptr;
    workers = work ? new Worker(*work) : nullptr;
    plot = gh ? new Greenhouse(*gh) : nullptr;
}

Memento::~Memento() 
{
    if (inventory) 
    {
        delete inventory;
    }
    if (workers) 
    {
        delete workers;
    }
    if (plot) 
    {
        delete plot;
    }
}

Inventory* Memento::getInventory() const {
    return inventory;
}

Worker* Memento::getWorkers() const {
    return workers;
}

Greenhouse* Memento::getPlot() const {
    return plot;
}

float Memento::getMoney() const {
    return money;
}

int Memento::getRating() const {
    return rating;
}

int Memento::getDay() const {
    return day;
}

int Memento::getHour() const {
    return hour;
}

int Memento::getMinute() const {
    return minute;
}