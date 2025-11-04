#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "raymath.h"
#include <string>

/**
 * @enum SceneType
 * @brief Enumerates the different distinct scenes or states within the game application.
 *
 * This is used by the SceneManager to track the current state and determine the next scene to load.
 */
typedef enum
{
    /** @brief The main world map, handling traffic and building access. */
    SCENE_OUTDOOR,
    /** @brief The farming simulation and plant management environment. */
    SCENE_GREENHOUSE,
    /** @brief The customer service and sales area. */
    SCENE_STORE,
    /** @brief The storage and inventory management area. */
    SCENE_WAREHOUSE
} SceneType;

/**
 * @class Scene
 * @brief The abstract base class that defines the core interface for all game scenes.
 *
 * This class establishes the **Template Method** structure, requiring all concrete scenes 
 * to implement essential game loop functions (Init, Update, Draw, HandleInput).
 */
class Scene
{
private:
    /** @brief Internal string used perhaps for debug or logging purposes. */
    std::string type;

public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of resources in derived classes.
     */
    virtual ~Scene() = default;

    // Pure virtual functions that all scenes must implement
    /**
     * @brief Initializes scene-specific resources, loads assets, and sets initial state.
     */
    virtual void Init() = 0;
    
    /**
     * @brief Updates the scene's core logic, simulation, and object states.
     * @param dt The delta time since the last frame (in seconds).
     */
    virtual void Update(float dt) = 0;
    
    /**
     * @brief Renders all visual elements belonging to the scene.
     */
    virtual void Draw() = 0;
    
    /**
     * @brief Processes input (keyboard, mouse) relevant to the current scene.
     */
    virtual void HandleInput() = 0;
    
    /**
     * @brief Returns the constant identifier for this scene type.
     * @return The SceneType enum value (e.g., SCENE_STORE).
     */
    virtual SceneType GetSceneType() const = 0;

    // Virtual functions with default implementations
    /**
     * @brief Renders any scene-specific menu or persistent sidebar UI.
     * * Default implementation does nothing.
     */
    virtual void DrawMenu() {}
    
    /**
     * @brief Checks if the scene should transition to a new one.
     * @return The SceneType to transition to, or the current scene's type if staying put.
     */
    virtual SceneType CheckExit()
    {
        return GetSceneType();
    }
};

#endif // SCENE_H