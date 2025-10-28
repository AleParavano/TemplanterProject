#include "Greenhouse.h"

Greenhouse::Greenhouse()
{
    size=0;
    capacity=16;
    plots.resize(capacity,nullptr);
    inventory=nullptr;
}

Greenhouse::Greenhouse(Inventory *inv)
{
    size=0;
    capacity=16;
    plots.resize(capacity,nullptr);
    inventory=inv;
}

Greenhouse::~Greenhouse()
{
    for(auto plant:plots){
        if(plant){
            delete plant;
        }
    }
}
bool Greenhouse::addPlant(Plant* plant,int position)
{
    if(position>=0 && position<capacity && plots[position]==nullptr){
        plots[position]=plant;
        size++;
        return true;
    }
    return false;
}

bool Greenhouse::addPlant(Plant *plant)
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

bool Greenhouse::removePlant(int position)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr){
        delete plots[position];
        plots[position]=nullptr;
        size--;
        return true;
    }
    return false;
}

bool Greenhouse::harvestPlant(int position)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr && inventory!=nullptr){
        Plant* plant=plots[position];
        plots[position]=nullptr;
        size--;

        inventory->add(plant);
        return true;
    }
    return false;
}

Plant* Greenhouse::getPlant(int position)
{
    return plots[position];
}

std::string Greenhouse::getPlot(int position)
{
    if(position>=0 && position<capacity && plots[position]!=nullptr){
        return plots[position]->getType();
    }
    return "Empty";
}

int Greenhouse::getSize()
{
    return size;
}

int Greenhouse::getCapacity()
{
    return capacity;
}

bool Greenhouse::increaseCapacity(int amount)
{
    if(amount>0&& capacity+amount<=128){
        capacity+=amount;
        plots.resize(capacity,nullptr);
        return true;
    }
    return false;
}

void Greenhouse::setInventory(Inventory *inv)
{
    inventory=inv;
}
