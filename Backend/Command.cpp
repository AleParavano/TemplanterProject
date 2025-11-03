/**
 * @file Command.cpp
 * @brief Implementation of concrete Command classes for worker actions.
 * 
 * This file implements various commands that workers can execute on plants and customers.
 * Each command encapsulates a specific action (water, fertilize, harvest, patrol, serve)
 * as an object, enabling queuing, scheduling, and execution of worker tasks.
 * 
 * @pattern Command - Encapsulates requests as objects
 */

#include "Command.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

/**
 * @brief Executes the water command on the target plant.
 * 
 * Waters the target plant by adding 50% to its water level. Outputs debug
 * messages showing the plant's water level before and after watering.
 */
void WaterCommand::execute()
{
    std::cout << "COMMAND EXECUTION: WaterCommand started. Target water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
    this->targetPlant->water(50.0f);
    std::cout << "COMMAND EXECUTION: WaterCommand completed. New water: " 
              << this->targetPlant->getWater() << "%." << std::endl;
}

/**
 * @brief Executes the fertilize command on the target plant.
 * 
 * Fertilizes the target plant by adding 50% to its nutrient level.
 */
void FertilizeCommand::execute()
{
    this->targetPlant->fertilize(50.0f);
}

/**
 * @brief Executes the harvest command on the target plant.
 * 
 * Retrieves the player's greenhouse from the Game singleton and attempts
 * to harvest the target plant, moving it to the player's inventory.
 */
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

/**
 * @brief Executes the patrol command to protect the nursery.
 * 
 * Sets the player's protected status to true, preventing robberies and
 * speeding up time during night hours.
 */
void PatrolCommand::execute()
{ Player* player=Game::getInstance()->getPlayerPtr();
    if(player)
    player->setProtected(true);
}

/**
 * @brief Executes the serve command for a customer.
 * 
 * @note Currently not implemented - marked as TODO
 */
void ServeCommand::execute()
{
    //TODO implement this code
}

/**
 * @brief Constructs a WaterCommand targeting the specified plant.
 * 
 * @param plant Pointer to the plant to be watered
 */
WaterCommand::WaterCommand(Plant *plant)
:targetPlant(plant)
{
}

/**
 * @brief Constructs a FertilizeCommand targeting the specified plant.
 * 
 * @param plant Pointer to the plant to be fertilized
 */
FertilizeCommand::FertilizeCommand(Plant *plant)
:targetPlant(plant)
{
}

/**
 * @brief Constructs a HarvestCommand targeting the specified plant.
 * 
 * @param plant Pointer to the plant to be harvested
 */
HarvestCommand::HarvestCommand(Plant* plant)
:targetPlant(plant)
{
}

/**
 * @brief Constructs a ServeCommand targeting the specified customer.
 * 
 * @param cust Pointer to the customer to be served
 */
ServeCommand::ServeCommand(Customer *cust)
:target(cust)
{
}

