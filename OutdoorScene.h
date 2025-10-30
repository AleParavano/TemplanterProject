#ifndef OUTDOORSCENE_H
#define OUTDOORSCENE_H

#include "Scene.h"
#include "Types.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// --- Defines ---
#define MAX_PEOPLE 15
#define MAX_CARS 8
#define MAX_HOUSES 6
#define PERSON_SPEED 40.0f
#define CAR_SPEED 80.0f
#define MAX_TREES 50
#define MAX_PARKING_SPOTS 6
#define MAX_PARKING_SPOTS_WAREHOUSE 6
#define MAX_PLANTS 250

// --- OutdoorScene Class ---
class OutdoorScene : public Scene {
private:
    Building greenhouse, store, inventory;
    House houses[MAX_HOUSES];
    Person people[MAX_PEOPLE];
    Car cars[MAX_CARS];
    Road roads[8];
    Tree trees[MAX_TREES];
    ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    ParkingSpot warehouseParkingSpots[MAX_PARKING_SPOTS_WAREHOUSE];
    Plant greenhousePlants[MAX_PLANTS];
    
    Vector2 storeEntrance;
    float timeOfDay;
    bool isPaused;
    int numRoads;
    int numTrees;
    int numPlants;

    SceneType nextScene;

    // Helper functions
    void InitBuildings();
    void InitRoads();
    void InitHouses();
    void InitTrees();
    void InitPeople();
    void InitCars();
    void InitParkingSpots();
    void InitGreenhousePlants();

    // Update functions
    void UpdatePeople(float dt);
    void UpdateCars(float dt);
    bool CheckCollision(Vector2 pos, float radius);

    // Draw functions
    void DrawTiledBackground(Color baseColor, int width, int height);
    void DrawSimpleHorizontalRoad(Road r);
    void DrawSimpleVerticalRoad(Road r);
    void DrawBuildingWithDetails(Building b);
    void DrawHouseDetailed(House h);
    void DrawTreeDetailed(Tree t);
    void DrawPersonDetailed(Person p);
    void DrawCarDetailed(Car c);
    void DrawPlantDetailed(Plant p);
    void DrawGreenhouseGarden();

    // Utility functions
    float Distance(Vector2 a, Vector2 b);
    Color GetSkyColor();
    Color GetGrassColor();
    int ClampValue(int value, int min, int max);

public:
    OutdoorScene();
    ~OutdoorScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    SceneType GetSceneType() const override { return SCENE_OUTDOOR; }
    SceneType CheckExit() override;
};

#endif // OUTDOORSCENE_H