#include "Game.h"

Game* Game::uniqueInstance = nullptr;

Game::Game() : player() {}

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
