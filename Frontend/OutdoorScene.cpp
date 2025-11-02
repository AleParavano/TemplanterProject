#include "OutdoorScene.h"
#include <iostream>

// Note: MAX_CARS is defined as 8 in OutdoorScene.h, but we ignore it here.

// --- OutdoorScene Class Implementation ---

OutdoorScene::OutdoorScene() : timeOfDay(0.6f), isPaused(false), numRoads(0), numTrees(0), numPlants(0), nextScene(SCENE_OUTDOOR) {}

void OutdoorScene::Init() {
    // Reset all counters to prevent accumulation on re-initialization
    numRoads = 0;
    numTrees = 0;
    numPlants = 0;
    
    InitBuildings();
    InitRoads();
    InitHouses();
    InitTrees();
    InitParkingSpots();
    InitPeople();
    InitGreenhousePlants();

    // Initialize timeOfDay float by synchronizing with the global Player time 
    Player* player = Game::getInstance()->getPlayerPtr();
    if (player) {
        float h = (float)player->getHour();
        float m = (float)player->getMinute();
        timeOfDay = h / 24.0f + m / (24.0f * 60.0f);
    }

}

void OutdoorScene::InitBuildings() {
    greenhouse = {{250, 300}, {140, 90}, {220, 220, 220, 255}, "GREENHOUSE"};
    store = {{950, 600}, {200, 160}, {200, 80, 60, 255}, "MEGA STORE"};
    inventory = {{930, 200}, {200, 160}, {180, 180, 190, 255}, "WAREHOUSE"};
    
    // Define all entrance points for people
    greenhouseEntrance = {greenhouse.position.x + greenhouse.size.x / 2, greenhouse.position.y + greenhouse.size.y + 90}; 
    storeEntrance = {store.position.x + store.size.x / 2, store.position.y + store.size.y + 25};
    inventoryEntrance = {inventory.position.x + inventory.size.x / 2, inventory.position.y + inventory.size.y + 25}; 
}

void OutdoorScene::InitRoads() {
    roads[numRoads++] = {{0, 450}, {1400, 450}, 80};
    roads[numRoads++] = {{700, 0}, {700, 900}, 80};
    roads[numRoads++] = {{1250, 450}, {1250, 600}, 55};
    roads[numRoads++] = {{0, 700}, {700, 700}, 55};
    roads[numRoads++] = {{1250, 200}, {1250, 450}, 55};
}

void OutdoorScene::InitHouses() {
    Color houseColors[] = {
        {230, 200, 160, 255}, {255, 235, 205, 255}, {210, 180, 140, 255}, 
        {200, 220, 240, 255}, {255, 240, 220, 255}, {255, 200, 150, 255}
    };
    Color roofColors[] = {
        {139, 69, 19, 255}, {160, 82, 45, 255}, {178, 34, 34, 255}, 
        {120, 60, 40, 255}, {140, 70, 50, 255}, {155, 80, 55, 255}
    };

    houses[0] = {{50, 580}, {80, 75}, houseColors[0], roofColors[0]};
    houses[1] = {{290, 540}, {80, 75}, houseColors[1], roofColors[1]};
    houses[2] = {{510, 580}, {80, 75}, houseColors[2], roofColors[2]};
    houses[3] = {{50, 820}, {80, 75}, houseColors[3], roofColors[3]};
    houses[4] = {{290, 780}, {80, 75}, houseColors[4], roofColors[4]};
    houses[5] = {{510, 820}, {80, 75}, houseColors[5], roofColors[5]};
}

void OutdoorScene::InitTrees() {
    Color foliageColors[] = {
        {34, 139, 34, 255}, {46, 125, 50, 255}, {27, 94, 32, 255}, 
        {56, 142, 60, 255}, {40, 120, 40, 255}
    };

    Vector2 treePositions[] = {
        {630, 340}, {500, 340}, {200, 340}, {100, 340}, {800, 340}, 
        {800, 240}, {800, 140}, {800, 40}, {800, 620}, {800, 720}, {800, 820},
        {900, 340}, {1100, 40}, {900, 180}, {1200, 40}, {1300, 40}, 
        {800, 530}, {900, 530}, {1000, 530}, {1100, 530}, {1350, 530},
        {200, 570}, {450, 570}, {30, 530}, {630, 530}, {200, 800}, {450, 800}, 
        {1350, 100}, {890, 650}, {900, 750}, {850, 900}, {950, 850}, 
        {1050, 790}, {1200, 820}, {1300, 850}, {1350, 800}
    };

    for (int i = 0; i < 36 && i < MAX_TREES; i++) {
        trees[numTrees].position = treePositions[i];
        trees[numTrees].radius = 20 + rand() % 15;
        trees[numTrees].foliageColor = foliageColors[rand() % 5];
        trees[numTrees].trunkColor = {101, 67, 33, 255};
        numTrees++;
    }
}

void OutdoorScene::InitParkingSpots() {
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        parkingSpots[i].position = {
            store.position.x + 250 + (i % 3) * 55,
            store.position.y + 50 + (i / 3) * 80
        };
        parkingSpots[i].occupied = false;
    }

    for (int i = 0; i < MAX_PARKING_SPOTS_WAREHOUSE; i++) {
        warehouseParkingSpots[i].position = {
            1050.0f + 100 + (i % 3) * 55,
            80.0f + 150 + (i / 3) * 80
        };
        warehouseParkingSpots[i].occupied = false;
    }
}

void OutdoorScene::InitPeople() {
    Color shirtColors[] = {RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, PINK, SKYBLUE, LIME};
    Color pantsColors[] = {DARKBLUE, DARKGRAY, BROWN, BLACK, DARKBROWN};

    Vector2 destinations[] = {greenhouseEntrance, storeEntrance, inventoryEntrance};

    for (int i = 0; i < MAX_PEOPLE; i++) {
        int houseIdx = rand() % MAX_HOUSES;
        Vector2 homePos = {
            houses[houseIdx].position.x + houses[houseIdx].size.x / 2,
            houses[houseIdx].position.y + houses[houseIdx].size.y / 2
        };
        
        Vector2 initialTarget = destinations[rand() % 3]; // Randomly select initial destination

        people[i] = {
            homePos, initialTarget, homePos, PERSON_SPEED + (rand() % 20 - 10),
            shirtColors[rand() % 9], pantsColors[rand() % 5], true,
            (float)(rand() % 500) / 100.0f, 0.0f, {3, 3}
        };
    }
}


void OutdoorScene::InitGreenhousePlants() {
    Color plantColors[][3] = {
        {{40, 160, 40, 255}, {50, 180, 50, 255}, {60, 200, 60, 255}},
        {{255, 200, 60, 255}, {255, 220, 80, 255}, {240, 200, 50, 255}},
        {{200, 40, 40, 255}, {220, 50, 50, 255}, {180, 30, 30, 255}}
    };

    float gardenStartX = 30, gardenStartY = 30, gardenWidth = 600, gardenHeight = 250;
    int rowSpacing = 30, colSpacing = 30;
    int numRows = (int)(gardenHeight / rowSpacing);
    int numCols = (int)(gardenWidth / colSpacing);

    numPlants = 0;
    for (int row = 0; row < numRows && numPlants < MAX_PLANTS; row++) {
        for (int col = 0; col < numCols && numPlants < MAX_PLANTS; col++) {
            float offsetX = (rand() % 6) - 3;
            float offsetY = (rand() % 6) - 3;
            
            greenhousePlants[numPlants].position = {
                gardenStartX + 8 + col * colSpacing + offsetX,
                gardenStartY + 8 + row * rowSpacing + offsetY
            };
            
            int colorType = rand() % 3;
            int colorShade = rand() % 3;
            greenhousePlants[numPlants].color = plantColors[colorType][colorShade];
            greenhousePlants[numPlants].type = rand() % 3;
            greenhousePlants[numPlants].size = 2.5f + (rand() % 3);
            greenhousePlants[numPlants].growthStage = 0.7f + (rand() % 30) / 100.0f;
            numPlants++;
        }
    }
}

void OutdoorScene::Update(float dt) {
    if (!isPaused) {
        //Synchronize timeOfDay float from the global Player every frame
        Player* player = Game::getInstance()->getPlayerPtr();
        if (player) {
            float h = (float)player->getHour();
            float m = (float)player->getMinute();
            timeOfDay = h / 24.0f + m / (24.0f * 60.0f);
        }
    }
}

void OutdoorScene::UpdatePeople(float dt) {
    Vector2 destinations[] = {greenhouseEntrance, storeEntrance, inventoryEntrance};
    
    for (int i = 0; i < MAX_PEOPLE; i++) {
        Person *p = &people[i];
        if (p->waitTimer > 0) {
            p->waitTimer -= dt;
            continue;
        }

        Vector2 direction = {p->target.x - p->position.x, p->target.y - p->position.y};
        float dist = sqrtf(direction.x * direction.x + direction.y * direction.y);

        if (dist < 8.0f) {
            if (p->goingToStore) { // Reached a public building entrance
                p->target = p->home;
                p->goingToStore = false;
                p->waitTimer = 3.0f + (float)(rand() % 400) / 100.0f;
            } else { // Reached home
                p->target = destinations[rand() % 3]; // Select a new random public building
                p->goingToStore = true;
                p->waitTimer = 2.0f + (float)(rand() % 300) / 100.0f;
            }
        } else {
            direction.x /= dist;
            direction.y /= dist;
            Vector2 newPos = {p->position.x + direction.x * p->speed * dt, 
                            p->position.y + direction.y * p->speed * dt};
            if (!CheckCollision(newPos, 10.0f)) {
                p->position = newPos;
                p->walkCycle += dt * 8.0f;
            }
        }
    }
}


bool OutdoorScene::CheckCollision(Vector2 pos, float radius) {
    Rectangle buildings[] = {
        {greenhouse.position.x - 5, greenhouse.position.y - 5, greenhouse.size.x + 10, greenhouse.size.y + 10},
        {store.position.x - 5, store.position.y - 5, store.size.x + 10, store.size.y + 10},
        {inventory.position.x - 5, inventory.position.y - 5, inventory.size.x + 10, inventory.size.y + 10}
    };

    for (int i = 0; i < 3; i++) {
        if (CheckCollisionCircleRec(pos, radius, buildings[i])) return true;
    }

    for (int i = 0; i < MAX_HOUSES; i++) {
        Rectangle houseRect = {houses[i].position.x, houses[i].position.y, houses[i].size.x, houses[i].size.y};
        if (CheckCollisionCircleRec(pos, radius, houseRect)) return true;
    }
    return false;
}

void OutdoorScene::AssignPersonDestination(Person& person) {
    // REMOVED - Original function was empty or not used. Logic is in UpdatePeople.
}

void OutdoorScene::HandleBuildingClicks() {
    // REMOVED - Original function was empty or not used. Logic is in HandleInput.
}

void OutdoorScene::HandleInput() {
    if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;
    if (IsKeyPressed(KEY_RIGHT)) timeOfDay += 0.05f;
    if (IsKeyPressed(KEY_LEFT)) timeOfDay -= 0.05f;
    
    if (timeOfDay > 1.0f) timeOfDay = 0.0f;
    if (timeOfDay < 0.0f) timeOfDay = 1.0f;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, {greenhouse.position.x, greenhouse.position.y, greenhouse.size.x, greenhouse.size.y})) {
            nextScene = SCENE_GREENHOUSE;
        }
        else if (CheckCollisionPointRec(mousePos, {store.position.x, store.position.y, store.size.x, store.size.y})) {
            nextScene = SCENE_STORE;
        }
        else if (CheckCollisionPointRec(mousePos, {inventory.position.x, inventory.position.y, inventory.size.x, inventory.size.y})) {
            nextScene = SCENE_WAREHOUSE;
        }
    }
}

SceneType OutdoorScene::CheckExit() {
    SceneType result = nextScene;
    nextScene = SCENE_OUTDOOR;  // Reset to stay in outdoor scene by default
    return result;
}

void OutdoorScene::Draw() {
    DrawTiledBackground(GetGrassColor(), 1400, 900);

    for (int i = 0; i < numRoads; i++) {
        Road currentRoad = roads[i];
        if (currentRoad.start.y == currentRoad.end.y) {
            DrawSimpleHorizontalRoad(currentRoad);
        } else if (currentRoad.start.x == currentRoad.end.x) {
            DrawSimpleVerticalRoad(currentRoad);
        }
    }

    // Draw Store Parking Spots Background (No car spot drawing detail)
    int parkingSpotwidth = Distance(parkingSpots[0].position, parkingSpots[MAX_PARKING_SPOTS - 1].position);
    int parkingSpotheight = Distance(parkingSpots[0].position, parkingSpots[3].position);
    DrawRectangle(parkingSpots[0].position.x - 40, store.position.y, parkingSpotwidth + 50, parkingSpotheight + 100, {60, 60, 60, 255});
    
    // Draw Warehouse Parking Spots Background (No car spot drawing detail)
    DrawRectangle(warehouseParkingSpots[0].position.x, inventory.position.y, parkingSpotwidth + 50, parkingSpotheight + 100, {60, 60, 60, 255});
    
    // Draw Parking Spot outlines
    for (int i = 0; i < MAX_PARKING_SPOTS; i++) {
        Color spotColor = Color{80, 80, 80, 255}; // Neutral color since occupancy is irrelevant without cars
        DrawRectangle(parkingSpots[i].position.x - 20, parkingSpots[i].position.y - 15, 40, 30, spotColor);
        DrawRectangleLinesEx({parkingSpots[i].position.x - 20, parkingSpots[i].position.y - 15, 40, 30}, 2, YELLOW);
    }
    for (int i = 0; i < MAX_PARKING_SPOTS_WAREHOUSE; i++) {
        Color spotColor = Color{80, 80, 80, 255}; // Neutral color
        DrawRectangle(warehouseParkingSpots[i].position.x + 20, warehouseParkingSpots[i].position.y + 10, 40, 30, spotColor);
        DrawRectangleLinesEx({warehouseParkingSpots[i].position.x + 20, warehouseParkingSpots[i].position.y + 10, 40, 30}, 2, YELLOW);
    }

    for (int i = 0; i < numTrees; i++) {
        if (trees[i].position.y < 400) DrawTreeDetailed(trees[i]);
    }

    DrawGreenhouseGarden();
    DrawBuildingWithDetails(greenhouse);
    DrawBuildingWithDetails(store);
    DrawBuildingWithDetails(inventory);

    for (int i = 0; i < MAX_HOUSES; i++) {
        DrawHouseDetailed(houses[i]);
    }

    for (int i = 0; i < numTrees; i++) {
        if (trees[i].position.y >= 400) DrawTreeDetailed(trees[i]);
    }


    for (int i = 0; i < MAX_PEOPLE; i++) {
        DrawPersonDetailed(people[i]);
    }

    if (timeOfDay < 0.3f || timeOfDay > 0.7f) {
        float darkness = 0.0f;
        if (timeOfDay < 0.3f) {
            darkness = 0.6f - (timeOfDay / 0.3f) * 0.6f;
        } else {
            darkness = ((timeOfDay - 0.7f) / 0.3f) * 0.6f;
        }
        DrawRectangle(0, 0, 1400, 900, Fade(BLACK, darkness));
    }
}

float OutdoorScene::Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Color OutdoorScene::GetSkyColor() {
    if (timeOfDay < 0.25f) {
        float t = timeOfDay / 0.25f;
        return {(unsigned char)(15 + t * 30), (unsigned char)(15 + t * 50), (unsigned char)(35 + t * 80), 255};
    } else if (timeOfDay < 0.35f) {
        float t = (timeOfDay - 0.25f) / 0.1f;
        return {(unsigned char)(45 + t * 90), (unsigned char)(65 + t * 100), (unsigned char)(115 + t * 120), 255};
    } else if (timeOfDay < 0.65f) {
        return {135, 206, 250, 255};
    } else if (timeOfDay < 0.75f) {
        float t = (timeOfDay - 0.65f) / 0.1f;
        return {(unsigned char)(135 - t * 80), (unsigned char)(206 - t * 130), (unsigned char)(250 - t * 160), 255};
    } else {
        float t = (timeOfDay - 0.75f) / 0.25f;
        return {(unsigned char)(55 - t * 40), (unsigned char)(76 - t * 61), (unsigned char)(90 - t * 55), 255};
    }
}

Color OutdoorScene::GetGrassColor() {
    float brightness = 1.0f;
    if (timeOfDay < 0.3f || timeOfDay > 0.7f) {
        brightness = 0.4f + (timeOfDay < 0.3f ? timeOfDay : (1.0f - timeOfDay)) * 2.0f;
    }
    return {(unsigned char)(34 * brightness), (unsigned char)(139 * brightness), (unsigned char)(34 * brightness), 255};
}

int OutdoorScene::ClampValue(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Vector2 OutdoorScene::GetBuildingEntrance(Building b) {
    // REMOVED - Original function was empty or not used.
    return {0, 0};
}
    
void OutdoorScene::SaveGame() {
    // REMOVED - Original function was empty or not used.
}

void OutdoorScene::LoadGame() {
    // REMOVED - Original function was empty or not used.
}

void OutdoorScene::DrawTiledBackground(Color baseColor, int width, int height) {
    for (int y = 0; y < height; y += 20) {
        for (int x = 0; x < width; x += 20) {
            Color varColor = baseColor;
            int variation = (x * 7 + y * 13) % 30 - 15;
            varColor = {
                (unsigned char)ClampValue(varColor.r + variation, 0, 255),
                (unsigned char)ClampValue(varColor.g + variation, 0, 255),
                (unsigned char)ClampValue(varColor.b + variation, 0, 255),
                255
            };
            DrawRectangle(x, y, 20, 20, varColor);
        }
    }
}

void OutdoorScene::DrawSimpleHorizontalRoad(Road r) {
    DrawRectangle(r.start.x, r.start.y - r.width / 2, (int)Distance(r.start, r.end), (int)r.width, {60, 60, 60, 255});
    int numDashes = (int)(Distance(r.start, r.end) / 40);
    for (int i = 0; i < numDashes; i++) {
        float segmentStart = r.start.x + i * 40;
        float segmentEnd = segmentStart + 20;
        if (segmentEnd > r.end.x) segmentEnd = r.end.x;
        if (segmentStart >= r.end.x) break;
        DrawLineEx({segmentStart, r.start.y}, {segmentEnd, r.start.y}, 3, WHITE);
    }
}

void OutdoorScene::DrawSimpleVerticalRoad(Road r) {
    DrawRectangle(r.start.x - r.width / 2, r.start.y, (int)r.width, (int)Distance(r.start, r.end), {60, 60, 60, 255});
    int numDashes = (int)(Distance(r.start, r.end) / 40);
    for (int i = 0; i < numDashes; i++) {
        float segmentStart = r.start.y + i * 40;
        float segmentEnd = segmentStart + 20;
        if (segmentEnd > r.end.y) segmentEnd = r.end.y;
        if (segmentStart >= r.end.y) break;
        DrawLineEx({r.start.x, segmentStart}, {r.start.x, segmentEnd}, 3, WHITE);
    }
}

void OutdoorScene::DrawBuildingWithDetails(Building b) {
    DrawRectangle(b.position.x + 8, b.position.y + 8, b.size.x, b.size.y, Fade(BLACK, 0.3f));
    DrawRectangleV(b.position, b.size, b.color);
    DrawRectangleLinesEx({b.position.x, b.position.y, b.size.x, b.size.y}, 3, ColorBrightness(b.color, -0.3f));
    DrawRectangle(b.position.x - 5, b.position.y - 5, b.size.x + 10, 8, ColorBrightness(b.color, -0.2f));

    int windowsX = (int)(b.size.x / 30);
    int windowsY = (int)(b.size.y / 35);
    for (int y = 0; y < windowsY; y++) {
        for (int x = 0; x < windowsX; x++) {
            float wx = b.position.x + 15 + x * 30;
            float wy = b.position.y + 20 + y * 35;
            Color windowColor = (timeOfDay > 0.3f && timeOfDay < 0.7f) ? Color{150, 200, 255, 200} : Color{255, 240, 150, 255};
            DrawRectangle(wx, wy, 18, 22, windowColor);
            DrawRectangleLinesEx({wx, wy, 18, 22}, 2, ColorBrightness(b.color, -0.5f));
            DrawLine(wx + 9, wy, wx + 9, wy + 22, ColorBrightness(b.color, -0.5f));
            DrawLine(wx, wy + 11, wx + 18, wy + 11, ColorBrightness(b.color, -0.5f));
        }
    }
    int textWidth = MeasureText(b.label, 20);
    DrawText(b.label, b.position.x + b.size.x / 2 - textWidth / 2, b.position.y + b.size.y / 2 - 10, 20, ColorBrightness(b.color, -0.7f));
}

void OutdoorScene::DrawHouseDetailed(House h) {
    DrawRectangle(h.position.x + 5, h.position.y + 5, h.size.x, h.size.y, Fade(BLACK, 0.3f));
    DrawRectangleV(h.position, h.size, h.wallColor);
    DrawRectangleLinesEx({h.position.x, h.position.y, h.size.x, h.size.y}, 2, ColorBrightness(h.wallColor, -0.3f));
    Vector2 roofTop = {h.position.x + h.size.x / 2, h.position.y - 20};
    Vector2 roofLeft = {h.position.x - 8, h.position.y};
    Vector2 roofRight = {h.position.x + h.size.x + 8, h.position.y};
    DrawTriangle(roofTop, roofRight, roofLeft, h.roofColor);
    DrawTriangleLines(roofTop, roofRight, roofLeft, ColorBrightness(h.roofColor, -0.3f));
    DrawRectangle(h.position.x + h.size.x / 2 - 10, h.position.y + h.size.y - 25, 20, 25, {139, 90, 43, 255});
    DrawRectangleLinesEx({h.position.x + h.size.x / 2 - 10, h.position.y + h.size.y - 25, 20, 25}, 2, {101, 67, 33, 255});
    DrawCircle(h.position.x + h.size.x / 2 + 5, h.position.y + h.size.y - 13, 2, GOLD);
    DrawRectangle(h.position.x + 10, h.position.y + 20, 18, 18, {150, 200, 250, 200});
    DrawRectangleLinesEx({h.position.x + 10, h.position.y + 20, 18, 18}, 2, ColorBrightness(h.wallColor, -0.5f));
    DrawRectangle(h.position.x + h.size.x - 28, h.position.y + 20, 18, 18, {150, 200, 250, 200});
    DrawRectangleLinesEx({h.position.x + h.size.x - 28, h.position.y + 20, 18, 18}, 2, ColorBrightness(h.wallColor, -0.5f));
}

void OutdoorScene::DrawTreeDetailed(Tree t) {
    DrawCircle(t.position.x + 3, t.position.y + t.radius + 3, t.radius, Fade(BLACK, 0.2f));
    DrawRectangle(t.position.x - 4, t.position.y + t.radius - 10, 8, t.radius + 10, t.trunkColor);
    DrawRectangleLinesEx({t.position.x - 4, t.position.y + t.radius - 10, 8, t.radius + 10}, 1, ColorBrightness(t.trunkColor, -0.3f));
    DrawCircle(t.position.x, t.position.y, t.radius, ColorBrightness(t.foliageColor, -0.2f));
    DrawCircle(t.position.x - t.radius / 3, t.position.y - t.radius / 4, t.radius * 0.8f, t.foliageColor);
    DrawCircle(t.position.x + t.radius / 3, t.position.y - t.radius / 4, t.radius * 0.8f, ColorBrightness(t.foliageColor, -0.1f));
    DrawCircle(t.position.x, t.position.y - t.radius / 2, t.radius * 0.7f, ColorBrightness(t.foliageColor, 0.1f));
}

void OutdoorScene::DrawPersonDetailed(Person p) {
    DrawEllipse(p.position.x + p.shadowOffset.x, p.position.y + p.shadowOffset.y, 8, 4, Fade(BLACK, 0.4f));
    float legOffset = sinf(p.walkCycle) * 3;
    DrawRectangle(p.position.x - 3, p.position.y + 3, 2, 6 + legOffset, p.pantsColor);
    DrawRectangle(p.position.x + 1, p.position.y + 3, 2, 6 - legOffset, p.pantsColor);
    DrawRectangle(p.position.x - 4, p.position.y - 5, 8, 8, p.shirtColor);
    DrawRectangleLinesEx({p.position.x - 4, p.position.y - 5, 8, 8}, 1, ColorBrightness(p.shirtColor, -0.3f));
    float armOffset = sinf(p.walkCycle) * 2;
    DrawRectangle(p.position.x - 5, p.position.y - 3 + armOffset, 1, 5, ColorBrightness(p.shirtColor, -0.2f));
    DrawRectangle(p.position.x + 4, p.position.y - 3 - armOffset, 1, 5, ColorBrightness(p.shirtColor, -0.2f));
    DrawCircle(p.position.x, p.position.y - 9, 4, {255, 220, 177, 255});
    DrawCircleLines(p.position.x, p.position.y - 9, 4, {210, 180, 140, 255});
    DrawCircle(p.position.x, p.position.y - 11, 4, {101, 67, 33, 255});
}



void OutdoorScene::DrawPlantDetailed(PlantVisual p) {
    float size = p.size * p.growthStage;
    if (p.type == 0) {
        DrawEllipse(p.position.x + 1, p.position.y + 1, size + 1, size * 0.6f, Fade(BLACK, 0.3f));
        for (int i = 0; i < 4; i++) {
            float angle = (PI / 2.0f) * i + PI / 4.0f;
            DrawEllipse(p.position.x + cosf(angle) * (size * 0.4f), p.position.y + sinf(angle) * (size * 0.4f), size * 0.7f, size * 0.5f, p.color);
        }
        DrawCircle(p.position.x, p.position.y, size * 0.4f, ColorBrightness(p.color, 0.1f));
    } else if (p.type == 1) {
        DrawCircle(p.position.x + 1, p.position.y + 1, size, Fade(BLACK, 0.3f));
        DrawCircle(p.position.x, p.position.y, size, p.color);
        DrawCircle(p.position.x - size * 0.3f, p.position.y - size * 0.2f, size * 0.7f, ColorBrightness(p.color, -0.1f));
        DrawCircle(p.position.x + size * 0.3f, p.position.y - size * 0.2f, size * 0.7f, ColorBrightness(p.color, 0.1f));
        DrawCircle(p.position.x - size * 0.2f, p.position.y - size * 0.3f, size * 0.3f, ColorBrightness(p.color, 0.3f));
    } else {
        DrawEllipse(p.position.x + 1, p.position.y + 1, size, size * 0.8f, Fade(BLACK, 0.3f));
        DrawRectangle(p.position.x - 1, p.position.y - size, 2, size, {60, 100, 40, 255});
        DrawCircle(p.position.x, p.position.y, size, p.color);
        DrawCircle(p.position.x - size * 0.3f, p.position.y - size * 0.3f, size * 0.4f, ColorBrightness(p.color, 0.4f));
        DrawCircle(p.position.x - size * 0.4f, p.position.y - size * 0.9f, size * 0.3f, {40, 140, 40, 255});
        DrawCircle(p.position.x + size * 0.4f, p.position.y - size * 0.9f, size * 0.3f, {40, 140, 40, 255});
    }
}

void OutdoorScene::DrawGreenhouseGarden() {
    float gardenStartX = 30, gardenStartY = 30, gardenWidth = 600, gardenHeight = 250;
    
    // Draw soil background
    for (int y = 0; y < (int)gardenHeight; y += 8) {
        for (int x = 0; x < (int)gardenWidth; x += 8) {
            Color soilColor = {101, 67, 33, 255};
            int variation = ((int)(gardenStartX + x) * 7 + (int)(gardenStartY + y) * 13) % 20 - 10;
            soilColor = {
                (unsigned char)ClampValue(soilColor.r + variation, 0, 255),
                (unsigned char)ClampValue(soilColor.g + variation, 0, 255),
                (unsigned char)ClampValue(soilColor.b + variation, 0, 255),
                255
            };
            DrawRectangle(gardenStartX + x, gardenStartY + y, 8, 8, soilColor);
        }
    }

    // Draw garden rows
    for (int row = 0; row < (int)((gardenHeight - 16) / 16); row++) {
        float rowY = gardenStartY + 8 + row * 16;
        DrawLineEx({gardenStartX + 5, rowY}, {gardenStartX + gardenWidth - 5, rowY}, 1, {80, 50, 25, 100});
    }

    // Draw plants
    for (int i = 0; i < numPlants; i++) {
        DrawPlantDetailed(greenhousePlants[i]);
    }

    // Draw greenhouse frame (metal posts and beams)
    Color metalColor = {100, 100, 100, 255};
    Color metalDark = {60, 60, 60, 255};
    float postThickness = 4, postSpacing = 40;

    // Top posts and beams
    for (float x = gardenStartX; x <= gardenStartX + gardenWidth; x += postSpacing) {
        DrawRectangle(x - postThickness/2, gardenStartY - 20, postThickness, 20, metalColor);
        DrawRectangle(x - postThickness/2 + 1, gardenStartY - 19, postThickness - 2, 19, metalDark);
        if (x < gardenStartX + gardenWidth) {
            DrawRectangle(x + postThickness/2, gardenStartY - 12, postSpacing - postThickness, 3, metalColor);
            DrawRectangle(x + postThickness/2 + 1, gardenStartY - 11, postSpacing - postThickness - 2, 2, metalDark);
        }
    }

    // Bottom posts and beams
    for (float x = gardenStartX; x <= gardenStartX + gardenWidth; x += postSpacing) {
        DrawRectangle(x - postThickness/2, gardenStartY + gardenHeight, postThickness, 20, metalColor);
        DrawRectangle(x - postThickness/2 + 1, gardenStartY + gardenHeight + 1, postThickness - 2, 19, metalDark);
        if (x < gardenStartX + gardenWidth) {
            DrawRectangle(x + postThickness/2, gardenStartY + gardenHeight + 9, postSpacing - postThickness, 3, metalColor);
            DrawRectangle(x + postThickness/2 + 1, gardenStartY + gardenHeight + 10, postSpacing - postThickness - 2, 2, metalDark);
        }
    }

    // Left posts and beams
    for (float y = gardenStartY; y <= gardenStartY + gardenHeight; y += postSpacing) {
        DrawRectangle(gardenStartX - 20, y - postThickness/2, 20, postThickness, metalColor);
        DrawRectangle(gardenStartX - 19, y - postThickness/2 + 1, 19, postThickness - 2, metalDark);
        if (y < gardenStartY + gardenHeight) {
            DrawRectangle(gardenStartX - 12, y + postThickness/2, 3, postSpacing - postThickness, metalColor);
            DrawRectangle(gardenStartX - 11, y + postThickness/2 + 1, 2, postSpacing - postThickness - 2, metalDark);
        }
    }

    // Right posts and beams
    for (float y = gardenStartY; y <= gardenStartY + gardenHeight; y += postSpacing) {
        DrawRectangle(gardenStartX + gardenWidth, y - postThickness/2, 20, postThickness, metalColor);
        DrawRectangle(gardenStartX + gardenWidth + 1, y - postThickness/2 + 1, 19, postThickness - 2, metalDark);
        if (y < gardenStartY + gardenHeight) {
            DrawRectangle(gardenStartX + gardenWidth + 9, y + postThickness/2, 3, postSpacing - postThickness, metalColor);
            DrawRectangle(gardenStartX + gardenWidth + 10, y + postThickness/2 + 1, 2, postSpacing - postThickness - 2, metalDark);
        }
    }
}

void OutdoorScene::DrawUI() {
    // REMOVED - Original function was empty or not used.
}

void OutdoorScene::DrawMoneyCounter() {
    // REMOVED - Original function was empty or not used.
}

void OutdoorScene::DrawRatingStars() {
    // REMOVED - Original function was empty or not used.
}