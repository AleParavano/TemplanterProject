#include "Memento.h"

Memento::Memento(const std::string& inv, const std::string& work, 
                 const std::string& gh, float m, int r, int d, int h, int min)
    : inventoryData(inv), 
      workerData(work), 
      greenhouseData(gh), 
      money(m), 
      rating(r), 
      day(d), 
      hour(h), 
      minute(min)
{}

Memento::~Memento() {}

const std::string& Memento::getInventoryData() const 
{
    return inventoryData;
}

const std::string& Memento::getWorkerData() const 
{
    return workerData;
}

const std::string& Memento::getGreenhouseData() const 
{
    return greenhouseData;
}

float Memento::getMoney() const 
{
    return money;
}

int Memento::getRating() const 
{
    return rating;
}

int Memento::getDay() const 
{
    return day;
}

int Memento::getHour() const 
{
    return hour;
}

int Memento::getMinute() const 
{
    return minute;
}