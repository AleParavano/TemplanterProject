#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

// --- Road/Path Structure (shared) ---
typedef struct {
    Vector2 start;
    Vector2 end;
    float width;
} Road;

// --- Plant Structure (shared) ---
typedef struct {
    Vector2 position;
    Color color;
    float size;
    int type;
    float growthStage;
} Plant;

// --- Building Structure ---
typedef struct {
    Vector2 position;
    Vector2 size;
    Color color;
    const char *label;
} Building;

// --- House Structure ---
typedef struct {
    Vector2 position;
    Vector2 size;
    Color wallColor;
    Color roofColor;
} House;

// --- Tree Structure ---
typedef struct {
    Vector2 position;
    float radius;
    Color foliageColor;
    Color trunkColor;
} Tree;

// --- Person Structure ---
typedef struct {
    Vector2 position;
    Vector2 target;
    Vector2 home;
    float speed;
    Color shirtColor;
    Color pantsColor;
    bool goingToStore;
    float waitTimer;
    float walkCycle;
    Vector2 shadowOffset;
} Person;

// --- Car Structure ---
typedef struct {
    Vector2 position;
    Vector2 size;
    int currentWaypoint;
    float speed;
    Color bodyColor;
    Color windowColor;
    bool forward;
    bool parked;
    float parkTimer;
    int targetSpot;
    float angle;
    Vector2 shadowOffset;
} Car;

// --- Parking Spot Structure ---
typedef struct {
    Vector2 position;
    bool occupied;
} ParkingSpot;

#endif // TYPES_H