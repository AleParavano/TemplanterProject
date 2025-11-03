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
//     Inventory* storageInventory;  // StoreScene owns the storage inventory!

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

// public:
//     // Collision rectangles
//     Rectangle counterHitBox;
//     Rectangle sDoor;
//     Rectangle plotHitBox;
//     Rectangle boundaryWall;
//     InventoryUI invUI;
    
//     StoreScene();
//     ~StoreScene();

//     void update(Player *player = nullptr);
//     void render();
//     void updateCustomers(float deltaTime, Player *player);
    
//     std::string getType();
//     int *getSelectedStorageSlot() { return &selectedStorageSlot; }
//     bool getShowModal() { return showModal; }
//     void toggleOpen() { storeOpen = !storeOpen; }

//     Inventory *getStorage() { return storageInventory; }
//     Store *getBackendStore() { return backendStore; }
//     CustomerManager* getCustomerManager() { return customerManager; }
// };

// #endif
<<<<<<< HEAD

=======
>>>>>>> origin/Frontend
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
<<<<<<< HEAD
    Inventory* storageInventory;  // StoreScene owns the storage inventory!
=======
    // Inventory* storageInventory;  <<< REMOVED: No longer local >>>
>>>>>>> origin/Frontend
    Player* player;  // Store player reference for use across methods

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

public:
    // Collision rectangles
    Rectangle counterHitBox;
    Rectangle sDoor;
    Rectangle plotHitBox;
    Rectangle boundaryWall;
<<<<<<< HEAD
    InventoryUI invUI;
=======
>>>>>>> origin/Frontend
    
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
    void toggleOpen() { storeOpen = !storeOpen; }

<<<<<<< HEAD
    Inventory *getStorage() { return storageInventory; }
=======
    // Inventory *getStorage() { return storageInventory; } <<< REMOVED: Use player->getInventory() >>>
>>>>>>> origin/Frontend
    Store *getBackendStore() { return backendStore; }
    CustomerManager* getCustomerManager() { return customerManager; }
};

#endif