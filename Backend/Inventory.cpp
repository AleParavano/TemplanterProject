#include "Inventory.h"

bool InventorySlot::add(Plant *plant)
{
    if (!plant)
        return false;
    if (isFull())
        return false;

    // If empty slot, accept any plant type
    if (isEmpty())
    {
        plantType = plant->getType(); // Assuming Plant has getType() method
        items.push_back(plant);
        return true;
    }

    // If not empty, check type compatibility
    if (plant->getType() != plantType)
    {
        return false;
    }

    items.push_back(plant);
    return true;
}

Plant *InventorySlot::remove()
{
    if (isEmpty())
        return nullptr;

    Plant *plant = items.back();
    items.pop_back();

    // Clear plant type if slot becomes empty
    if (isEmpty())
    {
        plantType.clear();
    }

    return plant;
}

bool InventorySlot::canAccept(Plant *plant) const
{
    if (!plant)
        return false;
    if (isFull())
        return false;
    if (isEmpty())
        return true;
    return plant->getType() == plantType;
}

// Inventory Implementation
Inventory::Inventory(int capacity) : maxSlots(capacity)
{
    slots.resize(maxSlots);
    for (int i = 0; i < maxSlots; i++)
    {
        slots[i] = nullptr;
    }
}

Inventory::~Inventory()
{
    clear();
}

bool Inventory::add(Plant *plant)
{    
    if (!plant) {
        return false;
    }


    // Try to find existing compatible slot
    InventorySlot *slot = findCompatibleSlot(plant);

    if (slot)
    {
        return slot->add(plant);
    }
    
    // Create new slot (removes the bad check!)
    slot = createNewSlot();
    if (!slot) {
        return false;
    }

    return slot->add(plant);
}

Plant *Inventory::removeItem(const std::string &plantType)
{
    // Find first slot with this plant type
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
        InventorySlot *slot = *it;
        if (slot->getPlantType() == plantType)
        {
            Plant *plant = slot->remove();

            if (slot->isEmpty())
            {
                slots.erase(it);
                delete slot;
            }

            return plant;
        }
    }
    return nullptr;
}

bool Inventory::removeStack(size_t index)
{
    if (index >= slots.size())
        return false;

    InventorySlot *slot = slots[index];

    while (!slot->isEmpty())
    {
        Plant *plant = slot->remove();
        delete plant;
    }

    slots.erase(slots.begin() + index);
    delete slot;

    return true;
}

int Inventory::getPlantCount(const std::string &plantType) const
{
    int count = 0;
    for (const auto *slot : slots)
    {
        if (slot != nullptr && slot->getPlantType() == plantType) 
        {
            count += slot->getSize();
        }
    }
    return count;
}

bool Inventory::isFull() const
{
 int filledSlots = 0;
    for (const auto *slot : slots)
    {
        if (slot != nullptr)  
        {
            filledSlots++;
            if (!slot->isFull())
                return false;
        }
    }
    return filledSlots >= maxSlots;
}

const InventorySlot *Inventory::getSlot(size_t index) const
{
    if (index >= slots.size())
        return nullptr;
    return slots[index];
}

void Inventory::clear()
{
    for (auto *slot : slots)
    {
        if (slot != nullptr)  
        {
            while (!slot->isEmpty())
            {
                Plant *plant = slot->remove();
                delete plant;
            }
            delete slot;
        }
    }
    slots.clear();
}

InventorySlot *Inventory::findCompatibleSlot(Plant *plant)
{
    for (auto *slot : slots)
    {
        // Skip nullptr slots!
        if (slot != nullptr && slot->canAccept(plant))
        {
            return slot;
        }
    }
    return nullptr;
}

InventorySlot *Inventory::createNewSlot()
{
    // Find first nullptr slot
    for (int i = 0; i < slots.size(); i++)
    {
        if (slots[i] == nullptr)
        {
            slots[i] = new InventorySlot();
            return slots[i];
        }
    }

    return nullptr; // No empty slots
}

void Inventory::swapSlots(int index1, int index2)
{
    if (index1 < 0 || index1 >= maxSlots || index2 < 0 || index2 >= maxSlots)
    {
        return;
    }

    InventorySlot *temp = slots[index1];
    slots[index1] = slots[index2];
    slots[index2] = temp;
}