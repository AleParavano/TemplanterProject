#pragma once
#include <vector>
#include "Plant.h"
#include "Inventory.h"
#include "Subject.h"
#include "Observer.h"

class Greenhouse : public Subject {
public:
    Greenhouse(Inventory* inv);
    Greenhouse();
    ~Greenhouse();
    
    bool addPlant(Plant* plant, int position);
    bool addPlant(Plant* plant);
    bool removePlant(int position);
    bool harvestPlant(int position);
    bool harvestPlant(Plant* plant);
    
    Plant* getPlant(int position);
<<<<<<< HEAD
=======
    Plant* getPlantByPointer(Plant* p) ;
>>>>>>> origin/Frontend
    std::string getPlot(int position);
    int getSize();
    int getCapacity();
    bool increaseCapacity(int amount);
    void setInventory(Inventory* inv);
    
    // Subject pattern implementation
    void notify() override;
    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    
    // Called when a plant ticks
    void tickPlant(int position);
    void tickAllPlants();
    
private:
    int size;
    std::vector<Plant*> plots;
    int capacity;
    Inventory* inventory;
};