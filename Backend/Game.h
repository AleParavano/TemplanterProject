/**
 * @file Game.h
 * @brief Main game controller class declaration.
 * 
 * This file contains the Game class which acts as the central controller
 * for the plant nursery simulation game.
 */

#pragma once

#include "Player.h"
#include "Caretaker.h"

/**
 * @class Game
 * @brief Main game controller class.
 * 
 * Controls the game loop, manages game state, and coordinates interactions
 * between greenhouse, customers, and other game systems.
 */
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