#pragma once

#include "Player.h"
#include "Caretaker.h"

class Game
{
private:
    static Game *uniqueInstance;
    Player player;
    Caretaker caretaker;

public:
    Game();
    ~Game();
    static Game *getInstance();
    Player &getPlayer();
    Player *getPlayerPtr();

    void saveGame();
    void loadGame();

    static void cleanup()
    {
        if (uniqueInstance)
        {
            delete uniqueInstance;
            uniqueInstance = nullptr;
        }
    }
};
