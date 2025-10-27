#include "Command.h"

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
    // add target plant to shop and remove from garden
}
void PatrolCommand::execute()
{
    targetPlant->Protected=true;
}
void ServeCommand::execute()
{
    // Implementation for serving action
}