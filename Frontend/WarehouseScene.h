// ===== WarehouseScene.h =====
#ifndef WAREHOUSESCENE_H
#define WAREHOUSESCENE_H

#include "Scene.h"
#include "Slot.h"
#include "InventoryUI.h"
#include "../Backend/Inventory.h"

// Forward declarations to access other scene/game components if needed
class Player;
class Game;

/**
 * @class WarehouseScene
 * @brief Represents the internal warehouse or storage area where the player manages bulk inventory and supplies.
 *
 * This scene is primarily designed for inventory management, separate from the sales floor (`StoreScene`) 
 * and the farming area (`GreenHouseScene`). It provides a dedicated, focused area for handling large item transfers.
 * * It is a **Concrete Scene** implementing the Scene Abstract Base Class interface.
 */
class WarehouseScene : public Scene {
private:
    /** @brief A list of visual slots representing the static storage units or shelves in the warehouse. */
    std::vector<Slot> shelfSlots;
    
    /** @brief Pointer to the player object for inventory interaction. */
    Player* player;
    
    /** @brief The collision rectangle for the door/exit leading back to the outdoor scene. */
    Rectangle exitDoor;
    
    /** @brief The SceneType to transition to upon exiting the warehouse. */
    SceneType nextScene;
    
    // Private helper methods
    /**
     * @brief Initializes the layout and positions of the storage shelves (shelfSlots).
     */
    void InitShelves();

public:
    /**
     * @brief Constructor. Uses default initialization.
     */
    WarehouseScene() = default;
    
    /**
     * @brief Destructor.
     */
    ~WarehouseScene() = default;

    // Scene interface implementation
    /**
     * @brief Performs one-time setup and initialization for the warehouse, including shelf layouts.
     */
    void Init() override;
    
    /**
     * @brief Updates the logic and state of the scene (e.g., inventory updates, time management).
     * @param dt The delta time since the last frame.
     */
    void Update(float dt) override;
    
    /**
     * @brief Renders the warehouse environment, shelves, and displayed items.
     */
    void Draw() override;
    
    /**
     * @brief Processes player input specific to the warehouse (e.g., interacting with shelves, clicking the door).
     */
    void HandleInput() override;
    
    /**
     * @brief Returns the constant type of this scene.
     * @return SCENE_WAREHOUSE.
     */
    SceneType GetSceneType() const override { return SCENE_WAREHOUSE; }
    
    /**
     * @brief Checks conditions for exiting the current scene (e.g., player clicks the exit door).
     * @return The SceneType to transition to, or SCENE_WAREHOUSE if no exit is triggered.
     */
    SceneType CheckExit() override;

    /**
     * @brief Links the scene to the primary Player object instance.
     * @param p A pointer to the Player object.
     */
    void SetPlayer(Player* p) { player = p; }
};

#endif // WAREHOUSESCENE_H