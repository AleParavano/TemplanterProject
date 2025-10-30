#include "StoreScene.h"

StoreScene::StoreScene()
    : showModal(false),
      selectedInventorySlot(-1),
      selectedPlantFromGrid(false),
      selectedGridX(-1),
      selectedGridY(-1),
      manageToggle{195, 215, 85, 20},
      counterHitBox{500, 350, 300, 27},
      sDoor{700, 350, 100, 26},
      plotHitBox{75, 75, 320, 300},
      boundaryWall{470, 0, 30, 377}
{
    // Initialize plants array to false
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            plants[i][j] = false;
        }
    }
    
    // Initialize inventory with some plants
    inventory[0] = 5;
    inventory[1] = 3;
    inventory[2] = 7;
    inventory[3] = 2;
    inventory[4] = 10;
}

void StoreScene::update()
{
    Vector2 mouse = GetMousePosition();
    
    // Check if manage button clicked
    if(CheckCollisionPointRec(mouse, manageToggle) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        showModal = true;
    }
    
    // Close modal with ESC
    if(showModal && IsKeyPressed(KEY_ESCAPE)){
        showModal = false;
        selectedInventorySlot = -1;
        selectedPlantFromGrid = false;
        selectedGridX = -1;
        selectedGridY = -1;
    }
    
    // Handle modal interactions
    if(showModal){
        // Handle inventory slot clicks
        for(int i = 0; i < 5; i++){
            int slotY = 120 + (i * 40);
            Rectangle slot = {470, slotY, 40, 40};
            
            if(CheckCollisionPointRec(mouse, slot) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if(inventory[i] > 0){
                    selectedInventorySlot = i;
                    selectedPlantFromGrid = false;
                }
            }
        }
        
        // Handle planting with selected inventory item
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(mouse.x >= 70 && mouse.x <= 430 && mouse.y >= 90 && mouse.y <= 450){
                int gridX = (mouse.x - 70) / 40;
                int gridY = (mouse.y - 90) / 40;
                
                if(gridX >= 0 && gridX < 10 && gridY >= 0 && gridY < 10){
                    if(selectedPlantFromGrid){
                        if(!plants[gridX][gridY]){
                            plants[selectedGridX][selectedGridY] = false;
                            plants[gridX][gridY] = true;
                            selectedPlantFromGrid = false;
                            selectedGridX = -1;
                            selectedGridY = -1;
                        }
                    }
                    else if(selectedInventorySlot != -1){
                        if(!plants[gridX][gridY]){
                            plants[gridX][gridY] = true;
                            inventory[selectedInventorySlot]--;
                            
                            if(inventory[selectedInventorySlot] <= 0){
                                selectedInventorySlot = -1;
                            }
                        }
                    }
                    else if(plants[gridX][gridY]){
                        selectedPlantFromGrid = true;
                        selectedGridX = gridX;
                        selectedGridY = gridY;
                        selectedInventorySlot = -1;
                    }
                }
            }
        }
        
        // Right click to remove plant
        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            if(mouse.x >= 70 && mouse.x <= 430 && mouse.y >= 90 && mouse.y <= 450){
                int gridX = (mouse.x - 70) / 40;
                int gridY = (mouse.y - 90) / 40;
                
                if(gridX >= 0 && gridX < 10 && gridY >= 0 && gridY < 10){
                    if(plants[gridX][gridY]){
                        plants[gridX][gridY] = false;
                        inventory[0]++;
                        selectedPlantFromGrid = false;
                        selectedGridX = -1;
                        selectedGridY = -1;
                    }
                }
            }
        }
    }
}

void StoreScene::render()
{
    ClearBackground(GRAY);

    // Drawing tiled floor
    DrawRectangle(500, 50, 300, 350, RAYWHITE);

    int cellSize = 50;

    // Tile shading
    for (int i = 496; i < GetScreenWidth(); i += cellSize){
        DrawRectangle(i, 50, 7, 350, LIGHTGRAY);
    }
    for (int j = 93; j < 400; j += cellSize){
        DrawRectangle(500, j, 300, 7, LIGHTGRAY);
    }

    // Tile lines
    for (int i = 500; i < GetScreenWidth(); i += cellSize){
        DrawLine(i, 50, i, 400, BLACK);
    }
    for (int j = 50; j <= 400; j += cellSize){
        DrawLine(500, j, GetScreenWidth(), j, BLACK);
    }

    // Building the counter
    Color customColor = {178, 102, 0, 255};
    Color custColor2 = {30, 15, 0, 255};
    Color custColor3 = {86, 49, 0, 255};
    DrawRectangle(500, 350, 200, 75, customColor);
    DrawRectangle(500, 377, 200, 48, custColor3);
    for (int i = 508; i < 700; i += 96){
        for (int j = 380; j < 425; j += 23){
            DrawRectangle(i, j, 88, 20, custColor2);
        }
    }
    for (int i = 500; i <= 700; i += 20){
        DrawLine(i, 350, i, 377, custColor3);
    }
    DrawLine(500, 377, 700, 377, custColor3);

    DrawRectangleRec(counterHitBox, Color{0, 0, 0, 0});

    // Swing door
    DrawRectangleRec(sDoor, customColor);
    DrawRectangle(700, 376, 100, 3, custColor3);
    DrawLine(700, 350, 700, 425, BLACK);

    // Creating the boundary wall
    Color custColor5 = {50, 50, 50, 255};
    DrawRectangleRec(boundaryWall, DARKGRAY);
    Rectangle boundaryWallShadow = {470, 325, 30, 100};
    DrawRectangleRec(boundaryWallShadow, custColor5);

    // Drawing the plot
    Color custColor4 = {50, 25, 0, 255};
    DrawRectangle(75, 75, 320, 300, customColor);
    DrawRectangle(85, 85, 300, 280, custColor4);
    DrawRectangle(75, 375, 320, 20, custColor3);
    DrawRectangleRec(plotHitBox, Color{0, 0, 0, 0});

    // Creating entrance
    DrawRectangle(700, 0, 50, 10, Color{50, 100, 50, 255});
    DrawRectangle(500, 0, 200, 50, custColor5);
    DrawRectangle(750, 0, 50, 50, custColor5);
    DrawRectangle(740, 0, 10, 40, custColor3);
    DrawRectangle(525, 0, 150, 30, custColor3);
    DrawRectangle(530, 0, 140, 25, customColor);
    DrawRectangle(530, 0, 140, 20, Color{130, 200, 250, 255});
    DrawRectangle(530, 0, 140, 10, Color{100, 165, 250, 255});
    
    // Drawing plants on the plot
    for(int i = 107, k = 0; i < 395; i += 32, k++){
        for(int j = 105, p = 0; j < 370; j += 30, p++){
            if(plants[k][p]){
                DrawRectangle(i, j, 3, 6, Color{50, 100, 50, 255});
                DrawRectangle(i, j, 3, 3, GREEN);
            }
        }
    }
    
    // Modal Button
    DrawText("Manage Plants", 200, 220, 10, WHITE);
    DrawRectangleRec(manageToggle, Color{255, 255, 255, 100});
}

void StoreScene::renderModal(int width, int height)
{
    if(!showModal) return;
    
    Vector2 mouse = GetMousePosition();
    
    // Darken background
    DrawRectangle(0, 0, width, height, Fade(BLACK, 0.5f));

    // Modal box
    Rectangle modal = {50, 50, 700, 425};
    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 2, DARKGRAY);

    // Title
    DrawText("Plant Management", 300, 60, 20, BLACK);

    // Draw plant grid (10x10)
    for (int i = 70; i < 450; i += 40){
        DrawLine(i, 90, i, 450, BLACK);
    }
    for(int j = 90; j < 470; j += 40){
        DrawLine(70, j, 430, j, BLACK);
    }

    // Adding plants to grid
    for(int i = 88, k = 0; i < 430; i += 40, k++){
        for(int j = 107, p = 0; j < 430; j += 40, p++){
            if(plants[k][p]){
                if(selectedPlantFromGrid && selectedGridX == k && selectedGridY == p){
                    DrawRectangle(i - 18, j - 15, 40, 40, Color{255, 255, 100, 100});
                }
                DrawRectangle(i, j, 3, 6, Color{50, 100, 50, 255});
                DrawRectangle(i, j, 3, 3, GREEN);
            }
        }
    }

    // Inventory section
    DrawText("Inventory", 500, 90, 16, BLACK);

    for(int i = 0; i < 5; i++){
        int slotY = 120 + (i * 40);
        Rectangle slot = {470, slotY, 40, 40};
        
        if(selectedInventorySlot == i){
            DrawRectangleRec(slot, Color{100, 200, 100, 255});
        } else {
            DrawRectangleRec(slot, LIGHTGRAY);
        }
        
        DrawRectangleLinesEx(slot, 2, BLACK);

        if(inventory[i] > 0){
            DrawRectangle(484, slotY + 15, 3, 6, Color{50, 100, 50, 255});
            DrawRectangle(484, slotY + 15, 3, 3, GREEN);
        }

        DrawText(TextFormat("%d", inventory[i]), 515, slotY + 12, 16, BLACK);
    }

    // Instructions
    DrawText("Left-click inventory, then grid to plant", 70, 460, 10, DARKGRAY);
    DrawText("Left-click plant, then empty slot to move", 70, 473, 10, DARKGRAY);
    DrawText("Right-click plant to remove & return to inventory", 420, 460, 10, DARKGRAY);
    DrawText("ESC to close", 650, 473, 10, DARKGRAY);
}

string StoreScene::getType(){
    return "Store";
}