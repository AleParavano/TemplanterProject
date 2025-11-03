/**
 * @file Game.cpp
 * @brief Implementation of Game class singleton and core game loop.
 */

#include "Game.h"

// Initialize static singleton instance
Game* Game::uniqueInstance = nullptr;

/**
 * @brief Construct game state with default player and caretaker
 */
Game::Game() : player(), caretaker("game_state.txt") {}

/**
 * @brief Clean up game resources
 */
Game::~Game() {}

/**
 * @brief Get or create singleton game instance
 * @return Pointer to singleton game instance
 */
Game* Game::getInstance()
{
    if (uniqueInstance == nullptr)
    {
        uniqueInstance = new Game();
    }
    return uniqueInstance;
}

/**
 * @brief Update game time based on real time delta
 * @param dt Delta time in seconds
 *
 * Updates game time accounting for day/night cycles and protection status.
 * Time advances faster at night (20:00-06:00) or when protected.
 */
void Game::UpdateGameTime(float dt)
{
    const float REAL_SECONDS_PER_GAME_MINUTE = 1.0f;
    int speedMultiplier = 1;
    int currentHour = player.getHour();

    if (currentHour >= 20 || currentHour < 6 || player.isProtected())
    {
        speedMultiplier = 10;
    }
    else
    {
        speedMultiplier = 1;
    }

    timeAccumulator += dt * (float)speedMultiplier;

    if (timeAccumulator >= REAL_SECONDS_PER_GAME_MINUTE)
    {
        int minutesToAdvance = (int)(timeAccumulator / REAL_SECONDS_PER_GAME_MINUTE);

        if (minutesToAdvance > 0)
        {
            player.advanceTime(minutesToAdvance);
            timeAccumulator -= (float)minutesToAdvance * REAL_SECONDS_PER_GAME_MINUTE;
        }
    }
}

/**
 * @brief Save current game state using Memento pattern
 */
void Game::saveGame()
{

    Memento *memento = player.createMemento();

    caretaker.addMemento(memento);
}

/**
 * @brief Load saved game state if available
 */
void Game::loadGame()
{

    Memento *memento = caretaker.getMemento();
    if (memento)
    {
        player.setMemento(memento);
    }
}