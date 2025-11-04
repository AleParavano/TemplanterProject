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

/**
 * @class StoreScene
 * @brief Represents the internal store environment where the player serves customers and manages inventory display.
 *
 * This scene handles the store's open/close state, customer flow, collision detection for the counter, 
 * and the interaction with the storage grid/display areas.
 */
class StoreScene : public Scene
{
private:
    /** @brief The visual slots representing the inventory on the display counter (View component). */
    std::vector<Slot> storageSlots;
    
    /** @brief Pointer to the core game logic store object (the Model component). */
    Store *backendStore;
    
    /** @brief Manager responsible for spawning, updating, and rendering all customers in the scene. */
    CustomerManager* customerManager;
    
    /** @brief Pointer to the player object for inventory access and state updates. */
    Player* player;

    // Modal state for inventory interaction
    /** @brief Flag indicating if the interaction modal (for placing/taking plants) is currently shown. */
    bool showModal;
    
    /** @brief Flag indicating if the plant selected for the modal originated from the display grid. */
    bool selectedPlantFromGrid;
    
    /** @brief X-coordinate of the grid plot selected for interaction. */
    int selectedGridX;
    
    /** @brief Y-coordinate of the grid plot selected for interaction. */
    int selectedGridY;

    // UI/Interaction Elements
    /** @brief Rectangle defining the button to toggle management mode. */
    Rectangle manageToggle;
    
    /** @brief Rectangle defining the exit door area to return to the outdoor scene. */
    Rectangle exit;
    
    /** @brief Rectangle defining the button/area to toggle the store's open/closed state. */
    Rectangle openNClose;
    
    /** @brief The index of the currently selected storage slot on the display counter. */
    int selectedStorageSlot;
    
    /** @brief Flag indicating if the store is currently open for business (customer spawning active). */
    bool storeOpen = false;

    // Helper methods
    /**
     * @brief Handles the logic update for all customers, including movement and serving attempts.
     * @param deltaTime The time elapsed since the last frame.
     */
    void UpdateCustomers(float deltaTime);
    
    /**
     * @brief Checks the current in-game time and automatically opens or closes the store if time constraints are enforced.
     */
    void UpdateStoreHours(); 

public:
    // Collision rectangles (public for easier access in Demo/Player update if needed)
    /** @brief Collision area for the main service counter. */
    Rectangle counterHitBox;
    
    /** @brief Collision area for the scene's exit door. */
    Rectangle sDoor;
    
    /** @brief Collision area defining the plot/grid where items are displayed for sale. */
    Rectangle plotHitBox;
    
    /** @brief Collision area for the boundary/walls of the store. */
    Rectangle boundaryWall;
    
    /**
     * @brief Constructor. Initializes member variables and collision rectangles.
     */
    StoreScene();
    
    /**
     * @brief Destructor. Cleans up dynamically allocated resources, particularly the CustomerManager.
     */
    ~StoreScene();

    // Scene interface implementation
    /**
     * @brief Initializes scene resources, including loading the CustomerManager and synchronizing storage slots.
     */
    void Init() override;
    
    /**
     * @brief Updates the scene logic, customer state, store hours, and player interaction.
     * @param dt The delta time since the last frame.
     */
    void Update(float dt) override;
    
    /**
     * @brief Renders the store environment, customers, the display counter, and any active modals.
     */
    void Draw() override;
    
    /**
     * @brief Processes player input specific to the store (e.g., clicking the counter, serving customers).
     */
    void HandleInput() override;
    
    /**
     * @brief Returns the constant type of this scene.
     * @return SCENE_STORE.
     */
    SceneType GetSceneType() const override;
    
    /**
     * @brief Checks if conditions for exiting the scene are met (e.g., player clicks the door).
     * @return SCENE_OUTDOOR if exiting, otherwise SCENE_STORE.
     */
    SceneType CheckExit() override;
    
    // Scene-specific methods
    /**
     * @brief Links the scene to the primary Player object instance.
     * @param p A pointer to the Player object.
     */
    void SetPlayer(Player* p) { player = p; }
    
    /**
     * @brief Provides a mutable pointer to the currently selected storage slot index.
     * @return A pointer to the selectedStorageSlot integer.
     */
    int *getSelectedStorageSlot() { return &selectedStorageSlot; }
    
    /**
     * @brief Gets the current state of the interaction modal.
     * @return true if the modal is being shown, false otherwise.
     */
    bool getShowModal() { return showModal; }
    
    /**
     * @brief Toggles the open/closed state of the store, starting/stopping customer spawning.
     */
    void toggleOpen();  // Modified to check time constraints
    
    /**
     * @brief Checks if the current in-game time allows the store to be open.
     * @return true if within operating hours, false otherwise.
     */
    bool canOpenStore() const; 
    
    /**
     * @brief Gets the current operational status of the store.
     * @return true if the store is open, false otherwise.
     */
    bool isStoreOpen() const { return storeOpen; }

};

#endif