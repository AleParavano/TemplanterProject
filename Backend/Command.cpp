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
    Greenhouse* greenhouse= player->getPlot();
   greenhouse->harvestPlant(targetPlant);
}
void PatrolCommand::execute()
{
    Player::setProtected(true);
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

