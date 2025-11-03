// #ifndef STORESCENE_H
// #define STORESCENE_H

// #include "Scene.h"
// #include "Slot.h"
// #include "CustomerManager.h"
// #include "../Backend/Inventory.h"
// #include "../Backend/Store.h"
// #include <vector>
// #include "InventoryUI.h"

// class Player; // Forward declaration

// class StoreScene : public Scene
// {
// private:
//     std::vector<Slot> storageSlots;
//     Store *backendStore;
//     CustomerManager* customerManager;
//     Player* player;

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

//     // Helper methods
//     void UpdateCustomers(float deltaTime);
//     void UpdateStoreHours(); // NEW: Check and enforce store hours

// public:
//     // Collision rectangles
//     Rectangle counterHitBox;
//     Rectangle sDoor;
//     Rectangle plotHitBox;
//     Rectangle boundaryWall;
    
//     StoreScene();
//     ~StoreScene();

//     // Scene interface implementation
//     void Init() override;
//     void Update(float dt) override;
//     void Draw() override;
//     void HandleInput() override;
//     SceneType GetSceneType() const override;
    
//     // Scene-specific methods
//     void SetPlayer(Player* p) { player = p; }
//     int *getSelectedStorageSlot() { return &selectedStorageSlot; }
//     bool getShowModal() { return showModal; }
//     void toggleOpen();  // Modified to check time constraints
//     bool canOpenStore() const; // NEW: Check if store can be opened

//     Store *getBackendStore() { return backendStore; }
//     CustomerManager* getCustomerManager() { return customerManager; }
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
#include "InventoryUI.h"

class Player; // Forward declaration

class StoreScene : public Scene
{
private:
    std::vector<Slot> storageSlots;
    Store *backendStore;
    CustomerManager* customerManager;
    Player* player;

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

    // Helper methods
    void UpdateCustomers(float deltaTime);
    void UpdateStoreHours(); // NEW: Check and enforce store hours

public:
    // Collision rectangles
    Rectangle counterHitBox;
    Rectangle sDoor;
    Rectangle plotHitBox;
    Rectangle boundaryWall;
    
    StoreScene();
    ~StoreScene();

    // Scene interface implementation
    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    SceneType GetSceneType() const override;
    
    // Scene-specific methods
    void SetPlayer(Player* p) { player = p; }
    int *getSelectedStorageSlot() { return &selectedStorageSlot; }
    bool getShowModal() { return showModal; }
    void toggleOpen();  // Modified to check time constraints
    bool canOpenStore() const; // NEW: Check if store can be opened

    Store *getBackendStore() { return backendStore; }
    CustomerManager* getCustomerManager() { return customerManager; }
};

#endif