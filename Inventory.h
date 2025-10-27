#pragma once
#include "Composite.h"
#include <vector>
#include "Plant.h"
class Inventory{
    public:
    Inventory(){}
    ~Inventory(){}
    bool addPlant(Plant* plant,int quantity);
    bool addStack(ItemStack* stack);
    bool removeStack(int index);
    bool sellStack(int index);
    ItemStack* getStack(int index);
    int getSize();
    int getCapacity();
    private:
    int money=0;
    std::vector<ItemStack*> slots;
    int size;
    int capacity=32;

};

