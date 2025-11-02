#ifndef STORESCENE_H
#define STORESCENE_H

#include "Scene.h"
#include "Slot.h"
#include "CustomerManager.h"
#include "../Backend/Inventory.h"
#include "../Backend/Store.h"
#include <vector>
#include "InventoryUI.h"

class Player; // Forward declaration

class StoreScene : public Scene
{
private:

    std::vector<Slot> storageSlots;
    Store *backendStore;
    CustomerManager* customerManager;
    Inventory* storageInventory;  // StoreScene owns the storage inventory!

    // Modal state
    bool showModal;
    bool selectedPlantFromGrid;
    int selectedGridX;
    int selectedGridY;

    Rectangle manageToggle;
    Rectangle exit;
    Rectangle openNClose;
    int selectedStorageSlot;
    bool storeOpen = false;

public:
    // Collision rectangles
    Rectangle counterHitBox;
    Rectangle sDoor;
    Rectangle plotHitBox;
    Rectangle boundaryWall;
    InventoryUI invUI;
    
    StoreScene();
    ~StoreScene();

    void update(Player *player = nullptr);
    void render();
    void updateCustomers(float deltaTime, Player *player);
    
    string getType();
    int *getSelectedStorageSlot() { return &selectedStorageSlot; }
    bool getShowModal() { return showModal; }
    void toggleOpen() { storeOpen = !storeOpen; }

    Inventory *getStorage() { return storageInventory; }
    Store *getBackendStore() { return backendStore; }
    CustomerManager* getCustomerManager() { return customerManager; }
};

#endif