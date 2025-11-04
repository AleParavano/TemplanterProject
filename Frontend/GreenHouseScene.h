#ifndef GREENHOUSESCENE_H
#define GREENHOUSESCENE_H

#include "Scene.h"
#include "ObjectTypes.h" // Assumed to define SCENE_GREENHOUSE, Road, PlantVisual, etc.
#include "../Backend/Game.h"
#include "../Backend/Player.h"
#include "../Backend/Plant.h"
#include "../Backend/PlantFactory.h"
#include "../Backend/Inventory.h"
#include "PlantVisualStrategy.h" // Assumed to define PlantVisual
#include "../Backend/Worker.h"    // Assumed to define Worker
#include "UI.h"                   // Assumed to define UI-related drawing functions
#include <map>
#include <vector>
#include <iostream>

/** @brief Maximum number of plant plots allowed in the greenhouse. */
#define MAX_PLANTS 250
// Constants for menu layout
/** @brief Fixed width for the sidebar menu. */
#define MENU_WIDTH 250
/** @brief X-coordinate where the sidebar menu starts (right side). */
#define MENU_X_START 1400 - MENU_WIDTH 
/** @brief Y-coordinate where the sidebar menu starts. */
#define MENU_Y_START 370
/** @brief Height of individual items within the sidebar menu. */
#define ITEM_HEIGHT 45
/** @brief Common size for square buttons. */
#define BUTTON_SIZE 30
/** @brief Width for general purpose buttons. */
#define BUTTON_WIDTH 30
/** @brief Standard padding used in UI layouts. */
#define PADDING 10

// --- Shop Modal Constants ---
/** @brief Fixed width for the in-game shop modal. */
#define SHOP_WIDTH 700
/** @brief Fixed height for the in-game shop modal. */
#define SHOP_HEIGHT 700
// Note: Assuming SCREEN_WIDTH and SCREEN_HEIGHT are defined globally or via raylib headers
#define SHOP_X ((SCREEN_WIDTH - SHOP_WIDTH) / 2)
#define SHOP_Y ((SCREEN_HEIGHT - SHOP_HEIGHT) / 2)
/** @brief Height of a row item within the shop modal. */
#define ITEM_ROW_HEIGHT 60

/**
 * @brief Utility function to clean up any static or global plant catalog data.
 *
 * (Note: The implementation must be defined elsewhere, likely in the corresponding .cpp file.)
 */
void cleanupPlantCatalog();

/**
 * @class GreenHouseScene
 * @brief Represents the main farming/greenhouse environment where the player manages plants, workers, and purchases supplies.
 *
 * Inherits from Scene and contains all logic for plant management, simulation updates, and UI drawing for this game area.
 */
class GreenHouseScene : public Scene {
private:
    /** @brief Array storing the visual and state data for all plant plots. */
    PlantVisual plants[MAX_PLANTS];
    
    /** @brief Array storing visual data for pathways/roads. */
    Road paths[10];
    
    /** @brief The actual count of active plant plots. */
    int numPlants;
    
    /** @brief The actual count of active pathways. */
    int numPaths;
    
    /** @brief The index of the currently selected plant plot for interaction or inspection. */
    int selectedPlotIndex;
    
    /** @brief Flag indicating if the seed shop modal is currently open. */
    bool isShopOpen;
    
    /** @brief Flag indicating if the worker hiring shop modal is currently open. */
    bool isHireShopOpen;
    
    /** @brief Accumulator for managing internal simulation time updates (e.g., worker actions). */
    float simTimeAccumulator;

    /** @brief The type of scene to switch to (used by CheckExit()). */
    SceneType nextScene;

    /**
     * @brief Initializes the initial state and properties of all plant plots.
     */
    void InitPlants();
    
    /**
     * @brief Initializes the layout and properties of the paths/roads.
     */
    void InitPaths();
    
    /**
     * @brief Draws the detailed visual representation of a single plant plot.
     * @param p The PlantVisual structure to draw.
     */
    void DrawPlantDetailed(PlantVisual p);
    
    /**
     * @brief Renders the UI for the seed shop modal, allowing the player to buy seeds.
     */
    void DrawSeedShop();
    
    /**
     * @brief Renders the UI for the worker hire shop modal, allowing the player to hire workers.
     */
    void DrawHireShop();
    
    /**
     * @brief Renders a detailed inspector view for a specific plant, showing its stats and status.
     * @param plant A pointer to the Plant object being inspected.
     * @param drawPos The position on the screen where the inspector window should be drawn.
     */
    void DrawPlantInspector(Plant* plant, Vector2 drawPos);
    
    /**
     * @brief Renders the visual representation of a gate (e.g., exit to the store).
     * @param position The center position of the gate.
     * @param isVertical Flag indicating if the gate is vertical or horizontal.
     */
    void DrawGate(Vector2 position, bool isVertical);
    
    /**
     * @brief Renders the static background and layout elements of the greenhouse environment.
     */
    void DrawGreenhouse();
    
    /**
     * @brief Calculates the Euclidean distance between two Vector2 points.
     * @param a The first point.
     * @param b The second point.
     * @return The distance between the points.
     */
    float Distance(Vector2 a, Vector2 b);
    
    /**
     * @brief Clamps an integer value within a specified range.
     * @param value The value to clamp.
     * @param min The minimum allowed value.
     * @param max The maximum allowed value.
     * @return The clamped value.
     */
    int ClampValue(int value, int min, int max);

public:
    /**
     * @brief Constructor.
     */
    GreenHouseScene();
    
    /**
     * @brief Destructor.
     */
    ~GreenHouseScene();
    
    /**
     * @brief Checks conditions for exiting the current scene (e.g., clicking a gate).
     * @return The SceneType to transition to, or SCENE_GREENHOUSE if no exit is triggered.
     */
    SceneType CheckExit() override;

    /**
     * @brief Performs one-time setup and initialization for the scene components.
     */
    void Init() override;
    
    /**
     * @brief Updates the logic and simulation state of the scene (plant growth, worker actions).
     * @param dt The delta time since the last frame.
     */
    void Update(float dt) override;
    
    /**
     * @brief Renders all visual elements of the scene (plants, paths, gates, UI modals).
     */
    void Draw() override;
    
    /**
     * @brief Processes player input specific to the greenhouse (clicks, key presses for interaction/UI).
     */
    void HandleInput() override;
    
    /**
     * @brief Renders the persistent sidebar menu for the scene.
     */
    void DrawMenu() override;
    
    /**
     * @brief Returns the constant type of this scene.
     * @return SCENE_GREENHOUSE.
     */
    SceneType GetSceneType() const override { return SCENE_GREENHOUSE; }

};

#endif // GREENHOUSESCENE_H