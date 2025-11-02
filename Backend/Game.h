#pragma once

#include "Player.h"
#include "Caretaker.h"

class Game {
private:
    static Game* uniqueInstance;
    Player player;
    Caretaker caretaker ;

    // --- NEW GLOBAL TIME STATE ---
    int gameMinute;
    int gameHour;
    int gameDay;
    float timeAccumulator;

public:
    Game();
    ~Game();
    static Game* getInstance();
    Player& getPlayer();
    Player* getPlayerPtr();
  
};