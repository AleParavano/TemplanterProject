#ifndef OUTDOORSCENE_H
#define OUTDOORSCENE_H

#include "Scene.h"
#include "ObjectTypes.h" // Includes Road, Building, Person, Tree, etc.
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../Backend/Player.h"
#include "../Backend/Game.h"

// --- Defines ---
/** @brief Maximum number of NPC people in the outdoor scene. */
#define MAX_PEOPLE 15
/** @brief Maximum number of decorative houses. */
#define MAX_HOUSES 6
/** @brief Standard movement speed for NPC people. */
#define PERSON_SPEED 40.0f
/** @brief Maximum number of trees for decoration. */
#define MAX_TREES 50
/** @brief Maximum parking spots near the store/main area. */
#define MAX_PARKING_SPOTS 6
/** @brief Maximum parking spots near the warehouse/greenhouse area. */
#define MAX_PARKING_SPOTS_WAREHOUSE 6
/** @brief Maximum number of initial plant visual representations (e.g., in a pre-made garden). */
#define MAX_PLANTS 250
/** @brief Maximum number of waypoints for car pathfinding (unused in this file but defined). */
#define MAX_WAYPOINTS 10

// --- OutdoorScene Class ---
/**
 * @class OutdoorScene
 * @brief Represents the top-down, outdoor world map where buildings, NPCs, and traffic are rendered.
 *
 * This scene is responsible for initializing the static world geometry, updating NPC movement, 
 * handling time of day, and managing transitions to indoor scenes (Store, Greenhouse, Inventory).
 */
class OutdoorScene : public Scene {
private:
    // Buildings and structures
    /** @brief The visual and interaction data for the greenhouse building. */
    Building greenhouse;
    /** @brief The visual and interaction data for the main store building. */
    Building store;
    /** @brief The visual and interaction data for the inventory/warehouse building. */
    Building inventory;
    /** @brief Array of house structures for decoration. */
    House houses[MAX_HOUSES];
    /** @brief Array of all active NPC people. */
    Person people[MAX_PEOPLE];
    /** @brief Array of road segments defining the traffic and walking areas. */
    Road roads[8];
    /** @brief Array of tree structures for decoration. */
    Tree trees[MAX_TREES];
    /** @brief Array of parking spots for the main area. */
    ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    /** @brief Array of parking spots near the warehouse. */
    ParkingSpot warehouseParkingSpots[MAX_PARKING_SPOTS_WAREHOUSE];
    /** @brief Array of initial plant visuals (e.g., for a garden plot outside). */
    PlantVisual greenhousePlants[MAX_PLANTS];
    
    
    // UI and game state
    /** @brief The world position of the store entrance point. */
    Vector2 storeEntrance;
    /** @brief The world position of the greenhouse entrance point. */
    Vector2 greenhouseEntrance;
    /** @brief The world position of the inventory/warehouse entrance point. */
    Vector2 inventoryEntrance;
    /** @brief Current time of day, affecting lighting and sky color (0.0 to 24.0). */
    float timeOfDay;
    /** @brief Flag indicating if game updates should be paused. */
    bool isPaused;
    /** @brief Actual count of active road segments. */
    int numRoads;
    /** @brief Actual count of active tree structures. */
    int numTrees;
    /** @brief Actual count of active outdoor plant visuals. */
    int numPlants;
    
    // New game state variables
    /** @brief Player's current monetary balance. */
    float playerMoney;
    /** @brief Player's current store rating/reputation. */
    int playerRating;
    
    // Click detection areas
    /** @brief Bounding box for detecting a click on the greenhouse entrance. */
    Rectangle greenhouseClickArea;
    /** @brief Bounding box for detecting a click on the store entrance. */
    Rectangle storeClickArea;
    /** @brief Bounding box for detecting a click on the warehouse/inventory entrance. */
    Rectangle warehouseClickArea;

    /** @brief The next scene the manager should switch to upon scene exit. */
    SceneType nextScene;

    // Helper functions
    /**
     * @brief Initializes the positions and properties of all main buildings (store, greenhouse, etc.).
     */
    void InitBuildings();
    
    /**
     * @brief Initializes the road network segments.
     */
    void InitRoads();
    
    /**
     * @brief Initializes the positions and appearance of the decorative houses.
     */
    void InitHouses();
    
    /**
     * @brief Initializes the positions and appearance of the decorative trees.
     */
    void InitTrees();
    
    /**
     * @brief Initializes the positions, speeds, and destinations of the NPC people.
     */
    void InitPeople();
    
    /**
     * @brief Initializes the positions and initial status of all parking spots.
     */
    void InitParkingSpots();
    
    /**
     * @brief Initializes the visual data for any outdoor plant structures (not the main farm).
     */
    void InitGreenhousePlants();
    
    /**
     * @brief Initializes car pathfinding waypoints and car objects. (Assuming cars exist/are planned).
     */
    void InitCarPaths();
    
    /**
     * @brief Initializes the rectangular areas used for detecting clicks on building entrances.
     */
    void InitClickAreas();

    // Update functions
    /**
     * @brief Updates the positions and state logic of all NPC people (movement, destination assignment).
     * @param dt The delta time since the last frame.
     */
    void UpdatePeople(float dt);
    
    /**
     * @brief Performs a general collision check against world obstacles.
     * @param pos The position to check.
     * @param radius The size of the object checking collision.
     * @return true if collision occurs, false otherwise.
     */
    bool CheckCollision(Vector2 pos, float radius);
    
    /**
     * @brief Assigns a new random or specific destination (store, home) to an NPC person.
     * @param person A reference to the Person object to update.
     */
    void AssignPersonDestination(Person& person);
    
    /**
     * @brief Checks if the player has clicked on a building entrance and updates the next scene accordingly.
     */
    void HandleBuildingClicks();

    // Draw functions
    /**
     * @brief Draws a large, repeating background pattern (e.g., grass).
     * @param baseColor The color of the background.
     * @param width The width of the drawing area.
     * @param height The height of the drawing area.
     */
    void DrawTiledBackground(Color baseColor, int width, int height);
    
    /**
     * @brief Renders a single horizontal road segment.
     * @param r The Road structure to draw.
     */
    void DrawSimpleHorizontalRoad(Road r);
    
    /**
     * @brief Renders a single vertical road segment.
     * @param r The Road structure to draw.
     */
    void DrawSimpleVerticalRoad(Road r);
    
    /**
     * @brief Renders a building, including its details and label.
     * @param b The Building structure to draw.
     */
    void DrawBuildingWithDetails(Building b);
    
    /**
     * @brief Renders a detailed house structure (walls and roof).
     * @param h The House structure to draw.
     */
    void DrawHouseDetailed(House h);
    
    /**
     * @brief Renders a detailed tree structure (trunk and foliage).
     * @param t The Tree structure to draw.
     */
    void DrawTreeDetailed(Tree t);
    
    /**
     * @brief Renders an NPC person, including movement animation and shadow.
     * @param p The Person structure to draw.
     */
    void DrawPersonDetailed(Person p);
    
    /**
     * @brief Renders a car object, including rotation and shadow.
     * @param c The Car structure to draw.
     */
    void DrawCarDetailed(Car c);
    
    /**
     * @brief Renders a single PlantVisual structure.
     * @param p The PlantVisual structure to draw.
     */
    void DrawPlantDetailed( PlantVisual p);
    
    /**
     * @brief Renders the specific area dedicated to the outdoor greenhouse garden plot.
     */
    void DrawGreenhouseGarden();
    
    /**
     * @brief Renders the overall heads-up display (HUD) for the scene.
     */
    void DrawUI();
    
    /**
     * @brief Renders the player's money balance on the UI.
     */
    void DrawMoneyCounter();
    
    /**
     * @brief Renders the player's rating using a star system or similar visual.
     */
    void DrawRatingStars();

    // Utility functions
    /**
     * @brief Calculates the Euclidean distance between two Vector2 points.
     * @param a The first point.
     * @param b The second point.
     * @return The distance between the points.
     */
    float Distance(Vector2 a, Vector2 b);
    
    /**
     * @brief Determines the appropriate sky color based on the current timeOfDay.
     * @return The calculated Color value for the sky.
     */
    Color GetSkyColor();
    
    /**
     * @brief Determines the appropriate grass color based on the timeOfDay (e.g., darker at night).
     * @return The calculated Color value for the grass.
     */
    Color GetGrassColor();
    
    /**
     * @brief Clamps an integer value within a specified range.
     * @param value The value to clamp.
     * @param min The minimum allowed value.
     * @param max The maximum allowed value.
     * @return The clamped value.
     */
    int ClampValue(int value, int min, int max);
    
    /**
     * @brief Calculates the standard entrance point position for a given building.
     * @param b The Building structure.
     * @return The Vector2 position of the entrance.
     */
    Vector2 GetBuildingEntrance(Building b);
    
    // Save/Load hooks
    /**
     * @brief Serializes the necessary game state data from the scene (e.g., NPC positions).
     */
    void SaveGame();
    
    /**
     * @brief Deserializes and loads game state data into the scene.
     */
    void LoadGame();

public:
    /**
     * @brief Constructor.
     */
    OutdoorScene();
    
    /**
     * @brief Default destructor.
     */
    ~OutdoorScene() = default;

    /**
     * @brief Performs one-time setup and initialization for all scene components.
     */
    void Init() override;
    
    /**
     * @brief Updates the logic and simulation state of the scene (time, NPC movement).
     * @param dt The delta time since the last frame.
     */
    void Update(float dt) override;
    
    /**
     * @brief Renders all visual elements of the scene (buildings, roads, trees, NPCs, cars).
     */
    void Draw() override;
    
    /**
     * @brief Processes player input specific to the outdoor world (movement, clicks on buildings).
     */
    void HandleInput() override;
    
    /**
     * @brief Returns the constant type of this scene.
     * @return SCENE_OUTDOOR.
     */
    SceneType GetSceneType() const override { return SCENE_OUTDOOR; }
    
    /**
     * @brief Checks conditions for exiting the current scene (e.g., clicking a building entrance).
     * @return The SceneType to transition to, or SCENE_OUTDOOR if no exit is triggered.
     */
    SceneType CheckExit() override;
};

#endif // OUTDOORSCENE_H