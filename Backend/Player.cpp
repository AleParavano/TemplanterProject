#include "Player.h"
#include "Serializer.h"

Player::Player()
    : money(0.0f), rating(0), day(1), hour(6), minute(0),
      inventory(nullptr), plot(nullptr)
{
    inventory = new Inventory();
    plot = new Greenhouse();
}

Player::~Player() {
    if (inventory) delete inventory;
    if (plot) delete plot;
    for (auto worker : workers) {
        if (worker) delete worker;
    }
    workers.clear();
}

float Player::getMoney() const {
    return money;
}

void Player::setMoney(float amount) {
    money = amount;
}

void Player::addMoney(float amount) {
    money += amount;
}

void Player::subtractMoney(float amount) {
    money -= amount;
    if (money < 0) money = 0;
}

int Player::getRating() const {
    return rating;
}

void Player::setRating(int r) {
    rating = r;
}

void Player::addRating(int r) {
    rating += r;
}

void Player::subtractRating(int r) {
    rating -= r;
    if (rating < 0) rating = 0;
}

int Player::getDay() const {
    return day;
}

int Player::getHour() const {
    return hour;
}

int Player::getMinute() const {
    return minute;
}

void Player::setTime(int d, int h, int m) {
    day = d;
    hour = h;
    minute = m;
}

void Player::advanceTime(int minutes) {
    minute += minutes;
    while (minute >= 60) {
        minute -= 60;
        hour++;
    }
    while (hour >= 24) {
        hour -= 24;
        day++;
    }
}

Inventory* Player::getInventory() const {
    return inventory;
}

Greenhouse* Player::getPlot() const {
    return plot;
}

void Player::hireWorker() {
    Worker* newWorker = new Worker();
    workers.push_back(newWorker);
}

void Player::fireWorker(int index) {
    if (index >= 0 && index < (int)workers.size()) {
        if (workers[index]) {
            delete workers[index];
        }
        workers.erase(workers.begin() + index);
    }
}

Worker* Player::getWorker(int index) const {
    if (index >= 0 && index < (int)workers.size()) {
        return workers[index];
    }
    return nullptr;
}

int Player::getWorkerCount() const {
    return workers.size();
}

const std::vector<Worker*>& Player::getWorkers() const {
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

Memento* Player::createMemento() const {
    std::string invData = Serializer::serializeInventory(inventory);
    std::string workersData = Serializer::serializeWorkers(workers);
    std::string ghData = Serializer::serializeGreenhouse(plot);
    
    return new Memento(invData, workersData, ghData, money, rating, day, hour, minute);
}

void Player::setMemento(Memento* memento) {
    if (memento) {
        money = memento->getMoney();
        rating = memento->getRating();
        day = memento->getDay();
        hour = memento->getHour();
        minute = memento->getMinute();
        
        Serializer::deserializeInventory(inventory, memento->getInventoryData());
        Serializer::deserializeGreenhouse(plot, memento->getGreenhouseData());
        Serializer::deserializeWorkers(workers, memento->getWorkerData());
    }
}