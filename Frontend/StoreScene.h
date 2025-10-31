#ifndef STORESCENE_H
#define STORESCENE_H

#include "Scene.h"
#include "Slot.h"
#include "../Backend/Inventory.h"
#include <vector>

class Player; // Forward declaration

class StoreScene : public Scene
{
private:
    bool plants[5][5];

    std::vector<Slot> storageSlots;
    Inventory *storageInventory;

    // Modal state
    bool showModal;
    bool selectedPlantFromGrid;
    int selectedGridX;
    int selectedGridY;

    Rectangle manageToggle;
    int selectedStorageSlot;

public:
    // Collision rectangles
    Rectangle counterHitBox;
    Rectangle sDoor;
    Rectangle plotHitBox;
    Rectangle boundaryWall;

    StoreScene();
    ~StoreScene();

    void update();
    void render();
    void renderModal(int width, int height);
    void updateStorage(Player *player); // Takes player to access their inventory
    string getType();
    int *getSelectedStorageSlot() { return &selectedStorageSlot; }
    bool getShowModal() { return showModal; }

    Inventory *getStorage() { return storageInventory; }
};

#endif