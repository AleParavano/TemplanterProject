#include "Player.h"
#include "PlayerMemento.h"

std::unique_ptr<Player> Player::instance = nullptr;
std::mutex Player::mtx;

Player::Player()
    : money(1000.0f), rating(0), hour(0), minute(0), running(false) {}

Player::~Player() {
    stopClock();
    if (clockThread.joinable())
        clockThread.join();
}

Player& Player::getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!instance)
        instance = std::unique_ptr<Player>(new Player());
    return *instance;
}

void Player::setMoney(float m) { money = m; }
void Player::setRating(int r) { rating = r; }
float Player::getMoney() const { return money; }
int Player::getRating() const { return rating; }

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
        clockThread = std::thread(&Player::runClock, this);
    }
}

void Player::stopClock() {
    running = false;
}

std::string Player::getTimeString() const {
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    return std::string(buffer);
}

std::unique_ptr<PlayerMemento> Player::saveState() const {
    return std::make_unique<PlayerMemento>(money, rating, hour, minute);
}

void Player::restoreState(const PlayerMemento& memento) {
    money = memento.getMoney();
    rating = memento.getRating();
    hour = memento.getHour();
    minute = memento.getMinute();
}
