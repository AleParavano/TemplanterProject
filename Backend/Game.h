#pragma once

#include "Player.h"
#include "Caretaker.h"

class Game {
private:
    static Game* uniqueInstance;
    Player player;
    Caretaker caretaker; 
    float timeAccumulator; 

public:
    Game();
    ~Game();
    static Game* getInstance();
    Player& getPlayer();
    Player* getPlayerPtr();
    void UpdateGameTime(float dt); 

    void saveGame();
    void loadGame();
};