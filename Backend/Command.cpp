#include "Command.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
<<<<<<< HEAD
void WaterCommand::execute()
{
    std::cout << "COMMAND EXECUTION: WaterCommand started. Target water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
    this->targetPlant->water(50.0f);
=======


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

    std::cout << "COMMAND EXECUTION: WaterCommand started. Target water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
              this->targetPlant->water(50.0f);

>>>>>>> origin/Frontend
    std::cout << "COMMAND EXECUTION: WaterCommand completed. New water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
}
void FertilizeCommand::execute()
{
<<<<<<< HEAD
=======
    
    if (!targetPlant) return;
    if (!subject || subject->getPlantByPointer(targetPlant) == nullptr) {
        return; 
    }
    if (targetPlant->isDead()) {
        return;
    }
>>>>>>> origin/Frontend
    this->targetPlant->fertilize(50.0f);
}
void HarvestCommand::execute()
{
<<<<<<< HEAD
    Game* game= Game::getInstance();
    Player* player= game->getPlayerPtr();
=======
    if (!targetPlant) return;
    if (!subject || subject->getPlantByPointer(targetPlant) == nullptr) {
        return; 
    }

    Game* game= Game::getInstance();
    Player* player= game->getPlayerPtr();

>>>>>>> origin/Frontend
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

<<<<<<< HEAD
WaterCommand::WaterCommand(Plant *plant)
:targetPlant(plant)
{
}

FertilizeCommand::FertilizeCommand(Plant *plant)
:targetPlant(plant)
{
}

HarvestCommand::HarvestCommand(Plant* plant)
:targetPlant(plant)
{
}


=======
>>>>>>> origin/Frontend
ServeCommand::ServeCommand(Customer *cust)
:target(cust)
{
}

