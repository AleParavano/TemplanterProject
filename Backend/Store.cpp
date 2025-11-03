/**
 * @file Store.cpp
 * @brief Implementation of Store class purchase mechanics
 */

#include "Store.h"
#include "Plant.h"
#include "Inventory.h"

/**
 * @brief Initialize empty store
 */
Store::Store()
{
}

/**
 * @brief Clean up store items
 * Deletes all items in catalog
 */
Store::~Store()
{
    for (auto *item : items)
    {
        delete item;
    }
}

/**
 * @brief Add item to store catalog
 * @param item Item to add (takes ownership)
 */
void Store::addItem(StoreItem *item)
{
    if (item)
    {
        items.push_back(item);
    }
}

/**
 * @brief Process item purchase
 * @param index Catalog index of item
 * @param player Player attempting purchase
 * @return true if purchase successful
 *
 * Validates:
 * - Player has sufficient funds
 * - Player inventory has space
 * - Item can be created successfully
 */
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

/**
 * @brief Get number of items in catalog
 * @return size_t Count of items
 */
size_t Store::getItemCount() const
{
    return items.size();
}

/**
 * @brief Get item at catalog index
 * @param index Index to retrieve
 * @return StoreItem* or nullptr if invalid index
 */
StoreItem *Store::getItem(size_t index) const
{
    if (index >= items.size())
    {
        return nullptr;
    }

    return items[index];
}