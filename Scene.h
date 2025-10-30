#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"

// --- Screen/Scene Enum ---
typedef enum {
    SCENE_OUTDOOR,
    SCENE_GREENHOUSE,
    SCENE_STORE,
    SCENE_WAREHOUSE
} SceneType;

// --- Base Scene Class ---
class Scene {
public:
    virtual ~Scene() = default;

    // Pure virtual functions that all scenes must implement
    virtual void Init() = 0;                    // Initialize scene resources
    virtual void Update(float dt) = 0;          // Update scene logic
    virtual void Draw() = 0;                    // Render scene
    virtual void HandleInput() = 0;             // Handle keyboard/mouse input
    virtual SceneType GetSceneType() const = 0; // Return this scene's type

    // Check if this scene should exit (returns next scene type, or current if staying)
    virtual SceneType CheckExit() { 
        return GetSceneType(); 
    }
};

#endif // SCENE_H