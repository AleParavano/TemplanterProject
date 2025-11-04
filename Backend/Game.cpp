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