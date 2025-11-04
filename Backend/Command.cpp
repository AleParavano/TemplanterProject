#include "Command.h"
#include "Player.h"
#include "Game.h"
#include <iostream>


WaterCommand::WaterCommand(Plant *plant, Greenhouse *gh)
: targetPlant(plant), subject(gh)
{
}


FertilizeCommand::FertilizeCommand(Plant *plant, Greenhouse *gh)
: targetPlant(plant), subject(gh)
{
}


HarvestCommand::HarvestCommand(Plant* plant, Greenhouse* gh)
: targetPlant(plant), subject(gh)
{
}

void WaterCommand::execute()
{
    if (!targetPlant) return;

    if (!subject || subject->getPlantByPointer(targetPlant) == nullptr) {
        return; 
    }

    if (targetPlant->isDead()) {
        return;
    }

}
void FertilizeCommand::execute()
{
    
    if (!targetPlant) return;
    if (!subject || subject->getPlantByPointer(targetPlant) == nullptr) {
        return; 
    }
    if (targetPlant->isDead()) {
        return;
    }
    this->targetPlant->fertilize(50.0f);
}
void HarvestCommand::execute()
{
    if (!targetPlant) return;
    if (!subject || subject->getPlantByPointer(targetPlant) == nullptr) {
        return; 
    }

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

ServeCommand::ServeCommand(Customer *cust)
:target(cust)
{
}

