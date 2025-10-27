#pragma once
#include "Plant.h"
#include <string>
#include <vector>
class ItemComponent {
    public:
    virtual ~ItemComponent() {}
    virtual int getQuantity() const = 0;
    virtual void sellOne();
    virtual void sellAll();

};

class ItemStack : public ItemComponent {
    public:
    ItemStack(Plant* plant, int quantity);
    ~ItemStack();
    int getQuantity() const override;
    bool addChild(ItemComponent* item);
    bool removeChild(ItemComponent* item);
    
    
    private:
    std::string plantType;
    int quantity;
    std::vector<SingleItem*> items;
};

class SingleItem: public ItemComponent {
    public:
    SingleItem(Plant* plant);
    ~SingleItem();
    int getQuantity() const override;
    private:
    Plant* plantType;
};