#include "Game.h"

Game *Game::uniqueInstance = nullptr;

Game::Game() : player(), caretaker("game_state.txt") {}
Game::~Game() {}
Game *Game::getInstance()
{
    if (uniqueInstance == nullptr)
    {
        uniqueInstance = new Game();
    }
    return uniqueInstance;
}
Player &Game::getPlayer()
{
    return player;
}
Player *Game::getPlayerPtr()
{
    return &player;
}

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

void Game::saveGame()
{

    Memento *memento = player.createMemento();

    caretaker.addMemento(memento);
}

void Game::loadGame()
{

    Memento *memento = caretaker.getMemento();
    if (memento)
    {
        player.setMemento(memento);
    }
}