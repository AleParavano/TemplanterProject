#include "Inventory.h"

bool InventorySlot::add(Plant* plant) {
    if (!plant) return false;
    if (isFull()) return false;
    
    // If empty slot, accept any plant type
    if (isEmpty()) {
        plantType = plant->getType(); // Assuming Plant has getType() method
        items.push_back(plant);
        return true;
    }
    
    // If not empty, check type compatibility
    if (plant->getType() != plantType) {
        return false;
    }
    
    items.push_back(plant);
    return true;
}

Plant* InventorySlot::remove() {
    if (isEmpty()) return nullptr;
    
    Plant* plant = items.back();
    items.pop_back();
    
    // Clear plant type if slot becomes empty
    if (isEmpty()) {
        plantType.clear();
    }
    
    return plant;
}

bool InventorySlot::canAccept( Plant* plant) const {
    if (!plant) return false;
    if (isFull()) return false;
    if (isEmpty()) return true;
    return plant->getType() == plantType;
}

// Inventory Implementation
Inventory::Inventory() {
    slots.reserve(MAX_SLOTS);
}

Inventory::~Inventory() {
    clear();
}

bool Inventory::add(Plant* plant) {
    if (!plant) return false;
    
    // Try to find existing compatible slot
    InventorySlot* slot = findCompatibleSlot(plant);
    
    if (slot) {
        return slot->add(plant);
    }
    
    // Need to create new slot
    if (slots.size() >= MAX_SLOTS) {
        return false; // Inventory full
    }
    
    slot = createNewSlot();
    if (!slot) return false;
    
    return slot->add(plant);
}

Plant* Inventory::removeItem(const std::string& plantType) {
    // Find first slot with this plant type
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        InventorySlot* slot = *it;
        if (slot->getPlantType() == plantType) {
            Plant* plant = slot->remove();
            
            if (slot->isEmpty()) {
                slots.erase(it);
                delete slot;
            }
            
            return plant;
        }
    }
    return nullptr;
}

bool Inventory::removeStack(size_t index) {
    if (index >= slots.size()) return false;
    
    InventorySlot* slot = slots[index];
    
    while (!slot->isEmpty()) {
        Plant* plant = slot->remove();
        delete plant; 
    }
    
    slots.erase(slots.begin() + index);
    delete slot;
    
    return true;
}

int Inventory::getPlantCount(const std::string& plantType) const {
    int count = 0;
    for (const auto* slot : slots) {
        if (slot->getPlantType() == plantType) {
            count += slot->getSize();
        }
    }
    return count;
}

bool Inventory::isFull() const {
    if (slots.size() < MAX_SLOTS) return false;
    
    // Check if all slots are full
    for (const auto* slot : slots) {
        if (!slot->isFull()) return false;
    }
    return true;
}

const InventorySlot* Inventory::getSlot(size_t index) const {
    if (index >= slots.size()) return nullptr;
    return slots[index];
}

void Inventory::clear() {
    for (auto* slot : slots) {
        while (!slot->isEmpty()) {
            Plant* plant = slot->remove();
            delete plant;
        }
        delete slot;
    }
    slots.clear();
}

InventorySlot* Inventory::findCompatibleSlot( Plant* plant) {
    for (auto* slot : slots) {
        if (slot->canAccept(plant)) {
            return slot;
        }
    }
    return nullptr;
}

InventorySlot* Inventory::createNewSlot() {
    if (slots.size() >= MAX_SLOTS) return nullptr;
    
    InventorySlot* newSlot = new InventorySlot();
    slots.push_back(newSlot);
    return newSlot;
}