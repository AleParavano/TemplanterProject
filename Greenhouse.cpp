#include "Greenhouse.h"

greenhouse::greenhouse()
{
    size=0;
    capacity=16;
    plots.resize(capacity,nullptr);
}

greenhouse::~greenhouse()
{
    for(auto plant:plots){
        if(plant){
            delete plant;
        }
    }
}
bool greenhouse::addPlant(Plant* plant,int position)
{
    if(position>=0 && position<capacity && plots[position]==nullptr){
        plots[position]=plant;
        size++;
        return true;
    }
    return false;
}

bool greenhouse::addPlant(Plant *plant)
{
    for(int i=0;i<capacity;i++){
        if(plots[i]==nullptr){
            plots[i]=plant;
            size++;
            return true;
        }
    }
    return false;
}

bool greenhouse::removePlant(int position)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr){
        delete plots[position];
        plots[position]=nullptr;
        size--;
        return true;
    }
    return false;
}

bool greenhouse::harvestPlant(int position, Inventory* inventory)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr){
        Plant* plant=plots[position];
        plots[position]=nullptr;
        size--;
        // transfer ownership to inventory
        inventory->addPlant(plant);
        return true;
    }
    return false
}

Plant* greenhouse::getPlant(int position)
{
    return plots[position];
}

std::string greenhouse::getPlot(int position)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr){
        return plots[position]->getType();
    }
    return "Empty";
}

int greenhouse::getSize()
{
    return size;
}

int greenhouse::getCapacity()
{
    return capacity;
}

bool greenhouse::increaseCapacity(int amount)
{
    if(amount>0&& capacity+amount<=128){
        capacity+=amount;
        plots.resize(capacity,nullptr);
        return true;
    }
    return false;
}
