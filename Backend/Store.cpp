#include "Store.h"
#include "Plant.h"
#include "Inventory.h"

Store::Store()
{
}

Store::~Store()
{
    for (auto *item : items)
    {
        delete item;
    }
}

void Store::addItem(StoreItem *item)
{
    if (item)
    {
        items.push_back(item);
    }
}

bool Store::purchaseItem(size_t index, Player *player)
{
    if (!player || index >= items.size())
    {
        return false;
    }

    StoreItem *item = items[index];
    float price = item->getPrice();

    // Check how much money
    if (player->getMoney() < price)
    {
        return false;
    }

    // Check if inv is full
    Inventory *inventory = player->getInventory();

    if (!inventory || inventory->isFull())
    {
        return false;
    }

    // Request item
    void *purchasedItem = item->request();
    Plant *plant = static_cast<Plant *>(purchasedItem);

    if (!plant)
    {
        return false;
    }

    // Add Plant to inv
    if (!inventory->add(plant))
    {
        delete plant;
        return false;
    }

    // Remove cost from money
    player->setMoney(player->getMoney() - price);

    return true;
}

size_t Store::getItemCount() const
{
    return items.size();
}

StoreItem *Store::getItem(size_t index) const
{
    if (index >= items.size())
    {
        return nullptr;
    }

    return items[index];
}