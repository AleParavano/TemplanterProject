#pragma once

class PlayerMemento 
{
private:
    float money;
    int rating;
    int hour;
    int minute;

public:
    PlayerMemento(float m, int r, int h, int min) : money(m), rating(r), hour(h), minute(min) {}

    float getMoney() const { return money; }
    int getRating() const { return rating; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
};
