#pragma once
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

class PlayerMemento;

class Player {
private:
    static std::unique_ptr<Player> instance;
    static std::mutex mtx;

    float money;
    int rating;
    int hour;
    int minute;

    std::atomic<bool> running;
    std::thread clockThread;

    Player();

    void runClock();

public:
    ~Player();

    static Player& getInstance();

    void setMoney(float m);
    void setRating(int r);
    float getMoney() const;
    int getRating() const;

    void startClock();
    void stopClock();
    std::string getTimeString() const;

    std::unique_ptr<PlayerMemento> saveState() const;
    void restoreState(const PlayerMemento& memento);
};
