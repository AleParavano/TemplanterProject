#ifndef OUTDOORSCENE_H
#define OUTDOORSCENE_H

#include "Scene.h"
#include "Types.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Backend/Player.h"
#include "Backend/Game.h"

// --- Defines ---
#define MAX_PEOPLE 15
#define MAX_HOUSES 6
#define PERSON_SPEED 40.0f
#define MAX_TREES 50
#define MAX_PARKING_SPOTS 6
#define MAX_PARKING_SPOTS_WAREHOUSE 6
#define MAX_PLANTS 250
#define MAX_WAYPOINTS 10

//Time 




// --- OutdoorScene Class ---
class OutdoorScene : public Scene {
private:
    // Buildings and structures
    Building greenhouse, store, inventory;
    House houses[MAX_HOUSES];
    Person people[MAX_PEOPLE];
    Road roads[8];
    Tree trees[MAX_TREES];
    ParkingSpot parkingSpots[MAX_PARKING_SPOTS];
    ParkingSpot warehouseParkingSpots[MAX_PARKING_SPOTS_WAREHOUSE];
    PlantVisual greenhousePlants[MAX_PLANTS];
    
    
    // UI and game state
    Vector2 storeEntrance;
    Vector2 greenhouseEntrance;
    Vector2 inventoryEntrance;
    float timeOfDay;
    bool isPaused;
    int numRoads;
    int numTrees;
    int numPlants;
    
    // New game state variables
    float playerMoney;
    int playerRating;
    
    // Click detection areas
    Rectangle greenhouseClickArea;
    Rectangle storeClickArea;
    Rectangle warehouseClickArea;

    SceneType nextScene;

    // Helper functions
    void InitBuildings();
    void InitRoads();
    void InitHouses();
    void InitTrees();
    void InitPeople();
    void InitParkingSpots();
    void InitGreenhousePlants();
    void InitCarPaths();
    void InitClickAreas();

    // Update functions
    void UpdatePeople(float dt);
    bool CheckCollision(Vector2 pos, float radius);
    void AssignPersonDestination(Person& person);
    void HandleBuildingClicks();

    // Draw functions
    void DrawTiledBackground(Color baseColor, int width, int height);
    void DrawSimpleHorizontalRoad(Road r);
    void DrawSimpleVerticalRoad(Road r);
    void DrawBuildingWithDetails(Building b);
    void DrawHouseDetailed(House h);
    void DrawTreeDetailed(Tree t);
    void DrawPersonDetailed(Person p);
    void DrawCarDetailed(Car c);
    void DrawPlantDetailed( PlantVisual p);
    void DrawGreenhouseGarden();
    void DrawUI();
    void DrawMoneyCounter();
    void DrawRatingStars();

    // Utility functions
    float Distance(Vector2 a, Vector2 b);
    Color GetSkyColor();
    Color GetGrassColor();
    int ClampValue(int value, int min, int max);
    Vector2 GetBuildingEntrance(Building b);
    
    // Save/Load hooks
    void SaveGame();
    void LoadGame();

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