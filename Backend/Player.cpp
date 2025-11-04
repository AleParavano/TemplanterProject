#include "Player.h"
#include "Serializer.h"
#include <sstream>
#include <iomanip> 
#include <iostream>
#include "../Frontend/InventoryUI.h"

// bool Player::safe = true;

Player::Player()
    : money(100.0f), rating(0), day(1), hour(6), minute(0),
      inventory(nullptr), plot(nullptr), safe(false), timeAccumulator(0.0f)
{
    inventory = new Inventory(25); // Changed from 15 to 25 slots
    plot = new Greenhouse(inventory);
    inventoryUI = new InventoryUI(inventory);
}

Player::~Player()
{
    if (inventory)
    {
        delete inventory;
    if (plot)
        delete plot;
    for (auto worker : workers)
    {
        if (worker)
            delete worker;
    }
    workers.clear();
    }
    if (inventoryUI)
    {
        delete inventoryUI;
    }
}

Inventory *Player::getInventory() const
{
    return inventory;
}

Greenhouse *Player::getPlot() const
{
    return plot;
}

float Player::getMoney() const
{
    return money;
}

void Player::setMoney(float amount)
{
    money = amount;
}

void Player::addMoney(float amount)
{
    money += amount;
}

void Player::subtractMoney(float amount)
{
    money -= amount;
    if (money < 0)
        money = 0;
}

void Player::UpdateGameTime(float dt)
{
    const float REAL_SECONDS_PER_GAME_MINUTE = 1.0f;

    int speedMultiplier = 1;

    if (hour >= 20 || hour < 6 || isProtected())
    {
        speedMultiplier = 10;
    }
    else
    {
        speedMultiplier = 1;
    }
    timeAccumulator += dt * (float)speedMultiplier;
    if (timeAccumulator >= REAL_SECONDS_PER_GAME_MINUTE)
    {
        int minutesToAdvance = (int)(timeAccumulator / REAL_SECONDS_PER_GAME_MINUTE);
        if (minutesToAdvance > 0)
        {
            advanceTime(minutesToAdvance);
            timeAccumulator -= (float)minutesToAdvance * REAL_SECONDS_PER_GAME_MINUTE;
        }
    }
}

float Player::getRating() const
{
    return rating;
}

void Player::setRating(float r)
{
    rating = r;
}

void Player::addRating(float r)
{
    rating += r;
    if(rating > 5) rating = 5;
}

void Player::subtractRating(float r)
{
    rating -= r;
    if (rating < 0)
        rating = 0;
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

void Player::setTime(int d, int h, int m)
{
    day = d;
    hour = h;
    minute = m;
}

void Player::advanceTime(int minutes)
{
    minute += minutes;
    while (minute >= 60)
    {
        minute -= 60;
        hour++;
    }
    while (hour >= 24)
    {
        hour -= 24;
        day++;
    }
}





void Player::addWorker(Worker* worker) {
    if (worker) {
        workers.push_back(worker);
        if (plot) {
            plot->attach(worker); 
            worker->setSubject(plot); 
        }
    }
}

void Player::fireWorker(int index)
{
    if (index >= 0 && index < (int)workers.size())
    {
        if (workers[index])
        {
            if (plot){
                plot->detach(workers[index]);
            }
            delete workers[index];
        }
        workers.erase(workers.begin() + index);
    }
}

Worker *Player::getWorker(int index) const
{
    if (index >= 0 && index < (int)workers.size())
    {
        return workers[index];
    }
    return nullptr;
}

int Player::getWorkerCount() const
{
    return workers.size();
}

void Player::pauseWorkers()
{
    for (auto* worker : workers) {
        if (worker) {
            worker->stop(); 
        }
    }
}

void Player::startWorkers()
{

}

const std::vector<Worker *> &Player::getWorkers()
{
    return workers;
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
    std::string invData = Serializer::serializeInventory(inventory);
    std::string workersData = Serializer::serializeWorkers(workers);
    std::string ghData = Serializer::serializeGreenhouse(plot);

    return new Memento(invData, workersData, ghData, money, rating, day, hour, minute);
}

void Player::setMemento(Memento *memento)
{
    if (memento)
    {
        pauseWorkers();
        money = memento->getMoney();
        rating = memento->getRating();
        day = memento->getDay();
        hour = memento->getHour();
        minute = memento->getMinute();
        inventory->clear();

        Serializer::deserializeInventory(inventory, memento->getInventoryData());
        Serializer::deserializeGreenhouse(plot, memento->getGreenhouseData());

     

        Serializer::deserializeWorkers(workers, memento->getWorkerData());

        for (auto *worker : workers)
        {
            if (worker)
            {
                plot->attach(worker);
                worker->setSubject(plot);
            }
        }
    }
}


std::string Player::getTimeString() const {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hour << ":"
       << std::setw(2) << std::setfill('0') << minute;
       
    return ss.str();
}

