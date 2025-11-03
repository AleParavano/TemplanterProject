/**
 * @file Game.h
 * @brief Main game controller class declaration.
 * 
 * @pattern Singleton - Single game instance manager
 */

#pragma once

#include "Player.h"
#include "Caretaker.h"

/**
 * @class Game
 * @brief Central controller managing game state and systems
 *
 * Implements Singleton pattern to maintain single source of truth for game state.
 * Manages player, time progression, and save/load functionality.
 */
class Game {
private:
    static Game* uniqueInstance;
    Player player;
    Caretaker caretaker; 
    float timeAccumulator;

public:
    /**
     * @brief Construct a new Game object
     * Initializes player and caretaker systems
     */
    Game();

    /**
     * @brief Destroy the Game object
     */
    ~Game();

    /**
     * @brief Get the singleton Game instance
     * @return Game* Pointer to the singleton instance
     */
    static Game* getInstance();

    /**
     * @brief Get player reference
     * @return Player& Reference to current player
     */
    Player& getPlayer();

    /**
     * @brief Get player pointer
     * @return Player* Pointer to current player
     */
    Player* getPlayerPtr();

    /**
     * @brief Update game time based on real time delta
     * @param dt Delta time since last update (seconds)
     */
    void UpdateGameTime(float dt);

    /**
     * @brief Save current game state via Memento pattern
     */
    void saveGame();

    /**
     * @brief Load last saved game state
     */
    void loadGame();
};