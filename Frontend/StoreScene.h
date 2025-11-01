// #ifndef STORESCENE_H
// #define STORESCENE_H

// #include "Scene.h"
// #include "Slot.h"
// #include "../Backend/Inventory.h"
// #include "../Backend/Store.h"
// #include <vector>
// #include <queue>
// #include "../Backend/CustomerFactory.h"
// #include "../Backend/PlantFactory.h"

// class Player; // Forward declaration

// class StoreScene : public Scene
// {
// private:
//     bool plants[5][5];

//     std::vector<Slot> storageSlots;
//     Store *backendStore;
//     std::queue<Customer *> customerQueue;

//     // Modal state
//     bool showModal;
//     bool selectedPlantFromGrid;
//     int selectedGridX;
//     int selectedGridY;

//     Rectangle manageToggle;
//     Rectangle exit;
//     Rectangle openNClose;
//     int selectedStorageSlot;
//     bool storeOpen = false;
//     RandomFactory rngFact;
//     RandomPlantFactory rngPlant;

// public:
//     // Collision rectangles
//     Rectangle counterHitBox;
//     Rectangle sDoor;
//     Rectangle plotHitBox;
//     Rectangle boundaryWall;
//     StoreScene();
//     ~StoreScene();

//     void update(Player *player = nullptr);
//     void render();
//     void renderModal(int width, int height);
//     void updateStorage(Player *player); // Takes player to access their inventory
//     string getType();
//     int *getSelectedStorageSlot() { return &selectedStorageSlot; }
//     bool getShowModal() { return showModal; }
//     void toggleOpen() { storeOpen = !storeOpen; }
//     void manageCustomerQ();

//     Inventory *getStorage() { return backendStore ? backendStore->getStorage() : nullptr; }
//     Store *getBackendStore() { return backendStore; }
// };

// #endif

#ifndef STORESCENE_H
#define STORESCENE_H

#include "Scene.h"
#include "Slot.h"
#include "CustomerManager.h"
#include "../Backend/Inventory.h"
#include "../Backend/Store.h"
#include <vector>

class Player; // Forward declaration

class StoreScene : public Scene
{
private:
    bool plants[5][5];

    std::vector<Slot> storageSlots;
    Store *backendStore;
    CustomerManager* customerManager;

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
    
    StoreScene();
    ~StoreScene();

    void update(Player *player = nullptr);
    void render();
    void renderModal(int width, int height);
    void updateStorage(Player *player);
    void updateCustomers(float deltaTime, Player *player);
    
    string getType();
    int *getSelectedStorageSlot() { return &selectedStorageSlot; }
    bool getShowModal() { return showModal; }
    void toggleOpen() { storeOpen = !storeOpen; }

    Inventory *getStorage() { return backendStore ? backendStore->getStorage() : nullptr; }
    Store *getBackendStore() { return backendStore; }
    CustomerManager* getCustomerManager() { return customerManager; }
};

#endif