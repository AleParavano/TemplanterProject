#include "Player.h"
#include <chrono>
#include <cstdio>
#include <iostream>

Player::Player()
    : inventory(nullptr), workers(nullptr), plot(nullptr),
      money(1000.0f), rating(0),
      day(1), hour(6), minute(0)
{
    inventory = new Inventory();
    workers = new Worker();
    plot = new Greenhouse();
}

Player::~Player()
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

Inventory *Player::getInventory() const
{
    return inventory;
}

Worker *Player::getWorkers() const
{
    return workers;
}

Greenhouse *Player::getPlot() const
{
    return plot;
}

float Player::getMoney() const
{
    return money;
}

int Player::getRating() const
{
    return rating;
}

int Player::getDay() const
{
    return day;
}

int Player::getHour() const
{
    return hour;
}

int Player::getMinute() const
{
    return minute;
}

std::string Player::getTimeString() const
{
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);

    return std::string(buffer);
}

std::string Player::getFullTimeString() const
{
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "Day %d, %02d:%02d", day, hour, minute);

    return std::string(buffer);
}

void Player::setInventory(Inventory *inv)
{
    if (inventory != inv)
    {
        if (inventory)
        {
            delete inventory;
        }
        inventory = inv;
    }
}

void Player::setWorkers(Worker *w)
{
    if (workers != w)
    {
        if (workers)
        {
            delete workers;
        }
        workers = w;
    }
}

void Player::setPlot(Greenhouse *gh)
{
    if (plot != gh)
    {
        if (plot)
        {
            delete plot;
        }
        plot = gh;
    }
}

void Player::setMoney(float m)
{
    money = m;
}

void Player::setRating(int r)
{
    rating = r;
}

void Player::setDay(int d)
{
    if (d > 0)
    {
        day = d;
    }
}

void Player::setHour(int h)
{
    if (h >= 0 && h < 24)
    {
        hour = h;
    }
}

void Player::setMinute(int m)
{
    if (m >= 0 && m < 60)
    {
        minute = m;
    }
}

bool Player::isNewDay() const
{
    return hour == 6 && minute == 0;
}

void Player::setProtected(bool prot)
{
    safe = prot;
}

bool Player::isProtected()
{
    return safe;
}

Memento *Player::createMemento() const
{
    return new Memento(inventory, workers, plot, money, rating, day, hour, minute);
}

void Player::setMemento(Memento *memento)
{
    if (memento)
    {
        money = memento->getMoney();
        rating = memento->getRating();
        day = memento->getDay();
        hour = memento->getHour();
        minute = memento->getMinute();

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

        inventory = memento->getInventory() ? new Inventory(*memento->getInventory()) : nullptr;
        workers = memento->getWorkers() ? new Worker(*memento->getWorkers()) : nullptr;
        plot = memento->getPlot() ? new Greenhouse(*memento->getPlot()) : nullptr;
    }
}