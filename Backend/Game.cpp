#include "Game.h"
#include "Memento.h"
#include <iostream>

// Note: Using the time constants defined in OutdoorScene.h for consistency
#define GAME_MINUTE_PER_SECOND 1.0f 
#define NIGHT_START_HOUR 19
#define NIGHT_END_HOUR 7

Game* Game::uniqueInstance = nullptr;

Game::Game() 
    : player(), 
      // Initialize time state in Game
      gameMinute(0), gameHour(7), gameDay(1), timeAccumulator(0.0f) 
{}

Game::~Game() {}

Game* Game::getInstance() 
{
    if (uniqueInstance == nullptr) 
    {
        uniqueInstance = new Game();
    }
    return uniqueInstance;
}

Player& Game::getPlayer() 
{
    return player;
}

Player *Game::getPlayerPtr()
{
  
    return &player;
}

void Game::UpdateGameTime(float dt) {
    // Determine the acceleration multiplier
    float timeMultiplier = GAME_MINUTE_PER_SECOND; // Day speed: 1 real second = 1 game minute
    
    // Check for night cycle (19:00 to 07:00)
    if (gameHour >= NIGHT_START_HOUR || gameHour < NIGHT_END_HOUR) {
        // Night speed: 6x faster than day speed (compresses 12 hours into 2 real minutes)
        timeMultiplier = 6.0f; 
    }
    
    // Accumulate time
    timeAccumulator += dt * timeMultiplier;
    
    // Process full game minutes
    while (timeAccumulator >= 1.0f) {
        timeAccumulator -= 1.0f;
        gameMinute++;

        if (gameMinute >= 60) {
            gameMinute = 0;
            gameHour++;

            if (gameHour >= 24) {
                gameHour = 0;
                gameDay++;
            }
        }
    }
    
    // Update the Player's state (Originator for Memento, the final source of truth)
    player.setDay(gameDay);
    player.setHour(gameHour);
    player.setMinute(gameMinute);
}

void Game::saveGame()
{
    //Originator (Player) to create a Memento
    Memento* memento = player.createMemento();

    //Store the Memento in the Caretaker
    caretaker.addMemento(memento);

    std::cout << "[GAME] State saved! Total saves: " << caretaker.getMementoCount() << std::endl;
}

void Game::loadGame()
{
    //Used to get the most recent state
    Memento* memento = caretaker.undo();

    if (memento) {
        //Restore the Originator (Player) state from the Memento
        player.setMemento(memento);

        //Synchronize the global time state with the loaded Memento data
        gameDay = player.getDay();
        gameHour = player.getHour();
        gameMinute = player.getMinute();

        std::cout << "[GAME] State loaded successfully! Day: " << gameDay 
                  << ", Time: " << player.getTimeString() << std::endl;
    }else {
        std::cout << "[GAME] ERROR: No saved state found to load." << std::endl;
    }

}
