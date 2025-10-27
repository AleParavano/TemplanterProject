#include "Player.h"
#include <chrono>
#include <cstdio>

Player::Player() : inventory(nullptr), workers(nullptr), plot(nullptr), money(1000.0f), rating(0), hour(0), minute(0), running(false), clockThread(nullptr) 
{
    inventory = new Inventory();
    workers = new Worker();
    plot = new Greenhouse();
}

Player::~Player() 
{
    stopClock();
    
    if (clockThread) 
    {
        if (clockThread->joinable()) 
        {
            clockThread->join();
        }
        delete clockThread;
    }

    if (inventory) {
        delete inventory;
    }
    if (workers) {
        delete workers;
    }
    if (plot) {
        delete plot;
    }
}

Inventory* Player::getInventory() const 
{
    return inventory;
}

Worker* Player::getWorkers() const 
{
    return workers;
}

Greenhouse* Player::getPlot() const 
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

std::string Player::getTimeString() const 
{
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    return std::string(buffer);
}

void Player::setInventory(Inventory* inv) 
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

void Player::setWorkers(Worker* w) 
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

void Player::setPlot(Greenhouse* gh) 
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

void Player::setMoney(float m) {
    money = m;
}

void Player::setRating(int r) {
    rating = r;
}

void Player::runClock() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        minute++;

        if (minute >= 60) {
            minute = 0;
            hour++;
        }
        if (hour >= 24) {
            hour = 0;
        }
    }
}

void Player::startClock() {
    if (!running) {
        running = true;
        if (clockThread) {
            if (clockThread->joinable()) {
                clockThread->join();
            }
            delete clockThread;
        }
        clockThread = new std::thread(&Player::runClock, this);
    }
}

void Player::stopClock() {
    running = false;
    if (clockThread && clockThread->joinable()) {
        clockThread->join();
    }
}

Memento* Player::createMemento() const 
{
    return new Memento(inventory, workers, plot, money, rating, hour, minute);
}

void Player::setMemento(Memento* memento) 
{
    if (memento) 
    {
        money = memento->getMoney();
        rating = memento->getRating();
        hour = memento->getHour();
        minute = memento->getMinute();
        
        if (inventory) {
            delete inventory;
        }
        if (workers) {
            delete workers;
        }
        if (plot) {
            delete plot;
        }
        
        inventory = memento->getInventory() ? memento->getInventory()->clone() : nullptr;
        workers = memento->getWorkers() ? memento->getWorkers()->clone() : nullptr;
        plot = memento->getPlot() ? memento->getPlot()->clone() : nullptr;
    }
}