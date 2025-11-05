#pragma once
#include <string>

class Memento 
{
public:
    Memento(const std::string& inv, const std::string& work, const std::string& gh, float m, int r, int d, int h, int min);
    ~Memento();
    
    const std::string& getInventoryData() const;
    const std::string& getWorkerData() const;
    const std::string& getGreenhouseData() const;
    
    float getMoney() const;
    int getRating() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;

    private:
    std::string inventoryData;
    std::string workerData;
    std::string greenhouseData;
    
    float money;
    int rating;
    int day;
    int hour;
    int minute;
};