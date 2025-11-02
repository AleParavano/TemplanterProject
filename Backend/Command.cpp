#include "Command.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
void WaterCommand::execute()
{
    std::cout << "COMMAND EXECUTION: WaterCommand started. Target water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
    this->targetPlant->water(50.0f);
    std::cout << "COMMAND EXECUTION: WaterCommand completed. New water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
}
void FertilizeCommand::execute()
{
    this->targetPlant->fertilize(50.0f);
}
void HarvestCommand::execute()
{
    Game* game= Game::getInstance();
    Player* player= game->getPlayerPtr();
    if(player){
    Greenhouse* greenhouse= player->getPlot();
    if(greenhouse)
   greenhouse->harvestPlant(targetPlant);
    }
}
void PatrolCommand::execute()
{ Player* player=Game::getInstance()->getPlayerPtr();
    if(player)
    player->setProtected(true);
}
void ServeCommand::execute()
{
    //TODO implement this code
}

WaterCommand::WaterCommand(Plant *plant)
:targetPlant(plant)
{
}

FertilizeCommand::FertilizeCommand(Plant *plant)
:targetPlant(plant)
{
}

HarvestCommand::HarvestCommand(int plant)
:targetPlant(plant)
{
}


ServeCommand::ServeCommand(Customer *cust)
:target(cust)
{
}

