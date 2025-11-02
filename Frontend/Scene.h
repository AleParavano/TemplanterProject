#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "raymath.h"
#include <string>

// --- Screen/Scene Enum ---
typedef enum
{
    SCENE_OUTDOOR,
    SCENE_GREENHOUSE,
    SCENE_STORE,
    SCENE_WAREHOUSE
} SceneType;

// --- Base Scene Class ---
class Scene
{
private:
    std::string type;

public:
    virtual ~Scene() = default;

    // Pure virtual functions that all scenes must implement
    virtual void Init() = 0;                    // Initialize scene resources
    virtual void Update(float dt) = 0;          // Update scene logic
    virtual void Draw() = 0;                    // Render scene
    virtual void HandleInput() = 0;             // Handle keyboard/mouse input
    virtual SceneType GetSceneType() const = 0; // Return this scene's type

    // Virtual functions
    // Default implementation does nothing, so not all scenes need a menu.
    virtual void DrawMenu() {}
    // Check if this scene should exit (returns next scene type, or current if staying)
    virtual SceneType CheckExit()
    {
        return GetSceneType();
    }

    virtual void render() = 0;
    virtual std::string getType() = 0;
};

#endif // SCENE_H#ifndef SCENE_H
