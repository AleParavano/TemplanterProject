#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "UI.h"               // Assumed to manage the main inventory/cross-scene UI
#include "OutdoorScene.h"     // Concrete Scene
#include "GreenHouseScene.h"  // Concrete Scene
#include "StoreScene.h"       // Concrete Scene
#include "WarehouseScene.h"   // Concrete Scene
#include "../Backend/Game.h"  // Contains core game logic/state
#include "../Backend/Player.h" // Contains player data/state
#include <map>

class Demo; // Forward declaration: Demo acts as the Facade/main application

/**
 * @class SceneManager
 * @brief Manages the state machine for the game, controlling which scene is active, 
 * updating the active scene, and handling transitions between them.
 *
 * Implements the **State Pattern** (or FSM) to switch between different game environments 
 * (Outdoor, Greenhouse, Store, etc.).
 */
class SceneManager {
private:
    /** @brief Map storing pointers to all initialized Scene objects, keyed by SceneType. */
    std::map<SceneType, Scene*> scenes;
    /** @brief The SceneType identifier for the currently active scene. */
    SceneType currentScene;
    /** @brief The SceneType identifier for the next scene to load (triggered by CheckExit). */
    SceneType nextScene;
    /** @brief Flag indicating if the application should terminate. */
    bool shouldExit;

    /**
     * @brief Declares Demo as a friend class to allow it access to private members, 
     * particularly to initialize the 'scenes' map and set the initial state.
     */
    friend class Demo; 

public:
    /**
     * @brief Constructor. Initializes the scene map with pointers to all concrete scene instances.
     */
    SceneManager();
    
    /**
     * @brief Destructor. Responsible for cleaning up and deleting all dynamically allocated Scene objects in the map.
     */
    ~SceneManager();

    /**
     * @brief Updates the currently active scene, checking for and executing any scene transitions.
     * @param dt The delta time since the last frame.
     */
    void Update(float dt);
    
    /**
     * @brief Passes input events to the currently active scene.
     */
    void HandleInput();
    
    /**
     * @brief Calls the Draw and DrawMenu methods of the currently active scene.
     */
    void Draw();
    
    /**
     * @brief Checks if the SceneManager has determined the game should quit.
     * @return true if the game is ready to exit, false otherwise.
     */
    bool IsDone() const;

private:
    /**
     * @brief Private helper to perform the actual scene change logic (transition from currentScene to nextScene).
     * @param newSceneType The SceneType to switch to.
     */
    void changeScene(SceneType newSceneType);
};

#endif // SCENEMANAGER_H