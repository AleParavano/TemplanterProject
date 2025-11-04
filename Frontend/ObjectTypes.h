#ifndef OBJECTTYPES_H
#define OBJECTTYPES_H

#include "raylib.h"
#include <string>

// --- Road/Path Structure (shared) ---
/**
 * @struct Road
 * @brief Defines a simple line segment used to represent roads, paths, or linear map features.
 */
typedef struct {
    /** @brief The starting point of the road segment. */
    Vector2 start;
    /** @brief The ending point of the road segment. */
    Vector2 end;
    /** @brief The visual width of the road. */
    float width;
} Road;

// --- Plant Structure (shared) ---
/**
 * @struct PlantVisual
 * @brief Represents the visual and spatial properties of a plant plot in the greenhouse or world.
 *
 * This is primarily used for drawing and collision, separate from the core Plant logic model.
 */
typedef struct {
    /** @brief World coordinates of the plant plot or visual object. */
    Vector2 position;
    /** @brief Color tint for rendering the plant. */
    Color color;
    /** @brief Visual scale or size modifier of the plant. */
    float size;
    /** @brief Internal integer ID corresponding to the plant type. */
    int type;
    /** @brief Current growth percentage (0.0 to 1.0) for visual representation. */
    float growthStage;
} PlantVisual; // Renamed from Plant

// --- Building Structure ---
/**
 * @struct Building
 * @brief Defines a static, rectangular building structure in the world.
 */
typedef struct {
    /** @brief The top-left corner position of the building. */
    Vector2 position;
    /** @brief The width and height of the building. */
    Vector2 size;
    /** @brief The primary color of the building. */
    Color color;
    /** @brief A text label to display on or near the building. */
    const char *label;
} Building;

// --- House Structure ---
/**
 * @struct House
 * @brief Defines a house structure with separate wall and roof colors.
 */
typedef struct {
    /** @brief The top-left corner position of the house. */
    Vector2 position;
    /** @brief The width and height of the house. */
    Vector2 size;
    /** @brief The color used for the house walls. */
    Color wallColor;
    /** @brief The color used for the house roof. */
    Color roofColor;
} House;

// --- Tree Structure ---
/**
 * @struct Tree
 * @brief Defines a simple tree structure for world decoration.
 */
typedef struct {
    /** @brief The position of the tree (e.g., center of the trunk). */
    Vector2 position;
    /** @brief The radius of the tree's foliage crown. */
    float radius;
    /** @brief The color used for the tree's foliage (leaves). */
    Color foliageColor;
    /** @brief The color used for the tree's trunk. */
    Color trunkColor;
} Tree;

// --- Person Structure ---
/**
 * @struct Person
 * @brief Defines the state and movement parameters for an NPC person in the game world.
 */
typedef struct {
    /** @brief The current world position of the person. */
    Vector2 position;
    /** @brief The current target position for movement. */
    Vector2 target;
    /** @brief The home position of the person. */
    Vector2 home;
    /** @brief The movement speed of the person. */
    float speed;
    /** @brief The color of the person's shirt. */
    Color shirtColor;
    /** @brief The color of the person's pants. */
    Color pantsColor;
    /** @brief Flag indicating if the person is currently moving toward the store. */
    bool goingToStore;
    /** @brief Timer used for managing waiting or idle periods. */
    float waitTimer;
    /** @brief Value used for simple walk cycle animation (e.g., leg swing). */
    float walkCycle;
    /** @brief Offset used for rendering a simple drop shadow. */
    Vector2 shadowOffset;
} Person;

// --- Car Structure ---
/**
 * @struct Car
 * @brief Defines the state and movement parameters for a vehicle.
 */
typedef struct {
    /** @brief The current world position of the car. */
    Vector2 position;
    /** @brief The dimensions (width, height) of the car. */
    Vector2 size;
    /** @brief The index of the current waypoint the car is driving toward. */
    int currentWaypoint;
    /** @brief The movement speed of the car. */
    float speed;
    /** @brief The primary color of the car body. */
    Color bodyColor;
    /** @brief The color of the car windows. */
    Color windowColor;
    /** @brief Flag indicating the car's general direction of travel (true for forward). */
    bool forward;
    /** @brief Flag indicating if the car is currently parked. */
    bool parked;
    /** @brief Timer used for managing the duration of the car's parking time. */
    float parkTimer;
    /** @brief The index of the parking spot the car is targeting. */
    int targetSpot;
    /** @brief The current rotation angle of the car (for rendering). */
    float angle;
    /** @brief Offset used for rendering a simple drop shadow. */
    Vector2 shadowOffset;
} Car;

// --- Parking Spot Structure ---
/**
 * @struct ParkingSpot
 * @brief Defines the location and status of a parking space.
 */
typedef struct {
    /** @brief The position of the parking spot (e.g., the center). */
    Vector2 position;
    /** @brief Flag indicating if the spot is currently occupied by a car. */
    bool occupied;
} ParkingSpot;

/**
 * @struct WorkerData
 * @brief Defines the configuration data for a specific type of worker (e.g., cost, type).
 */
struct WorkerData {
    /** @brief String identifier for the worker type (e.g., "Gardener"). */
    std::string type;
    /** @brief The cost associated with this worker (e.g., salary, hiring fee). */
    float cost;
    /** @brief The color of the worker's shirt (for visual distinction). */
    Color shirtColor;
};

#endif // TYPES_H