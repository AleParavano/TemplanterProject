#pragma once

#include <string>

class Memento {
private:
    float money;
    int rating;
    int hour;
    int minute;
    std::string inventoryState;

public:
    Memento(float m, int r, int h, int min);
    Memento(float m, int r, int h, int min, std::string invState);

    float getMoney() const;
    int getRating() const;
    int getHour() const;
    int getMinute() const;
    std::string getInventoryState() const;
};