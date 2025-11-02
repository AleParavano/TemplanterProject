#pragma once

#include "Player.h"

class Game {
private:
    static Game* uniqueInstance;
    Player player;

public:
    Game();
    ~Game();
    static Game* getInstance();
    Player& getPlayer();
    Player* getPlayerPtr();
};