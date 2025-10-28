#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
class Greenhouse {
    public:
    Greenhouse(Inventory* inv);
    Greenhouse();
    ~Greenhouse();
    bool addPlant(Plant* plant,int position);
    bool addPlant(Plant* plant);
    bool removePlant(int position);
    bool harvestPlant(int position);
    Plant* getPlant(int position);
    std::string getPlot(int position);
    int getSize();
    int getCapacity();
    bool increaseCapacity(int amount);
    void setInventory(Inventory* inv);
    private:
    int size;
    std::vector<Plant*> plots;
    int capacity;
    Inventory* inventory;
};