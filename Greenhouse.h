#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
class Inventory;
class greenhouse {
    public:
    greenhouse();
    ~greenhouse();
    bool addPlant(Plant* plant,int position);
    bool addPlant(Plant* plant);
    bool removePlant(int position);
    bool harvestPlant(int position,Inventory* inventory);
    Plant* getPlant(int position);
    std::string getPlot(int position);
    int getSize();
    int getCapacity();
    bool increaseCapacity(int amount);

    private:
    int size;
    std::vector<Plant*> plots;
    int capacity;
};