#include "Command.h"
#include "Player.h"
#include "Game.h"
void WaterCommand::execute()
{
    this->targetPlant->water(10.0f);
}
void FertilizeCommand::execute()
{
    this->targetPlant->fertilize(5.0f);
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

