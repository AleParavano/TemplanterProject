#include "StoreScene.h"

StoreScene::StoreScene()
    : showModal(false),
      selectedInventorySlot(-1),
      selectedPlantFromGrid(false),
      selectedGridX(-1),
      selectedGridY(-1),
      manageToggle{341, 376, 149, 35},
      counterHitBox{875, 613, 525, 47},
      sDoor{1225, 613, 175, 46},
      plotHitBox{131, 131, 560, 525},
      boundaryWall{823, 0, 53, 660}
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
            int slotY = 210 + (i * 70);
            Rectangle slot = {823, slotY, 70, 70};
            
            if(CheckCollisionPointRec(mouse, slot) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if(inventory[i] > 0){
                    selectedInventorySlot = i;
                    selectedPlantFromGrid = false;
                }
            }
        }
        
        // Handle planting with selected inventory item
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(mouse.x >= 123 && mouse.x <= 753 && mouse.y >= 158 && mouse.y <= 788){
                int gridX = (mouse.x - 123) / 70;
                int gridY = (mouse.y - 158) / 70;
                
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
            if(mouse.x >= 123 && mouse.x <= 753 && mouse.y >= 158 && mouse.y <= 788){
                int gridX = (mouse.x - 123) / 70;
                int gridY = (mouse.y - 158) / 70;
                
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
    DrawRectangle(875, 88, 525, 613, RAYWHITE);

    int cellSize = 88;

    // Tile shading
    for (int i = 868; i < GetScreenWidth(); i += cellSize){
        DrawRectangle(i, 88, 12, 613, LIGHTGRAY);
    }
    for (int j = 163; j < 700; j += cellSize){
        DrawRectangle(875, j, 525, 12, LIGHTGRAY);
    }

    // Tile lines
    for (int i = 875; i < GetScreenWidth(); i += cellSize){
        DrawLine(i, 88, i, 700, BLACK);
    }
    for (int j = 88; j <= 700; j += cellSize){
        DrawLine(875, j, GetScreenWidth(), j, BLACK);
    }

    // Building the counter
    Color customColor = {178, 102, 0, 255};
    Color custColor2 = {30, 15, 0, 255};
    Color custColor3 = {86, 49, 0, 255};
    DrawRectangle(875, 613, 350, 131, customColor);
    DrawRectangle(875, 660, 350, 84, custColor3);
    for (int i = 889; i < 1225; i += 168){
        for (int j = 665; j < 744; j += 40){
            DrawRectangle(i, j, 154, 35, custColor2);
        }
    }
    for (int i = 875; i <= 1225; i += 35){
        DrawLine(i, 613, i, 660, custColor3);
    }
    DrawLine(875, 660, 1225, 660, custColor3);

    DrawRectangleRec(counterHitBox, Color{0, 0, 0, 0});

    // Swing door
    DrawRectangleRec(sDoor, customColor);
    DrawRectangle(1225, 658, 175, 5, custColor3);
    DrawLine(1225, 613, 1225, 744, BLACK);

    // Creating the boundary wall
    Color custColor5 = {50, 50, 50, 255};
    DrawRectangleRec(boundaryWall, DARKGRAY);
    Rectangle boundaryWallShadow = {823, 569, 53, 175};
    DrawRectangleRec(boundaryWallShadow, custColor5);

    // Drawing the plot
    Color custColor4 = {50, 25, 0, 255};
    DrawRectangle(131, 131, 560, 525, customColor);
    DrawRectangle(149, 149, 525, 490, custColor4);
    DrawRectangle(131, 656, 560, 35, custColor3);
    DrawRectangleRec(plotHitBox, Color{0, 0, 0, 0});

    // Creating entrance
    DrawRectangle(1225, 0, 88, 18, Color{50, 100, 50, 255});
    DrawRectangle(875, 0, 350, 88, custColor5);
    DrawRectangle(1313, 0, 88, 88, custColor5);
    DrawRectangle(1295, 0, 18, 70, custColor3);
    DrawRectangle(919, 0, 263, 53, custColor3);
    DrawRectangle(928, 0, 245, 44, customColor);
    DrawRectangle(928, 0, 245, 35, Color{130, 200, 250, 255});
    DrawRectangle(928, 0, 245, 18, Color{100, 165, 250, 255});
    
    // Drawing plants on the plot
    for(int i = 187, k = 0; i < 691; i += 56, k++){
        for(int j = 184, p = 0; j < 648; p++, j += 53){
            if(plants[k][p]){
                DrawRectangle(i, j, 5, 11, Color{50, 100, 50, 255});
                DrawRectangle(i, j, 5, 5, GREEN);
            }
        }
    }
    
    // Modal Button
    DrawText("Manage Plants", 350, 385, 18, WHITE);
    DrawRectangleRec(manageToggle, Color{255, 255, 255, 100});
}

void StoreScene::renderModal(int width, int height)
{
    if(!showModal) return;
    
    Vector2 mouse = GetMousePosition();
    
    // Darken background
    DrawRectangle(0, 0, width, height, Fade(BLACK, 0.5f));

    // Modal box
    Rectangle modal = {88, 88, 1225, 744};
    DrawRectangleRec(modal, RAYWHITE);
    DrawRectangleLinesEx(modal, 4, DARKGRAY);

    // Title
    DrawText("Plant Management", 525, 105, 35, BLACK);

    // Draw plant grid (10x10)
    for (int i = 123; i < 788; i += 70){
        DrawLine(i, 158, i, 788, BLACK);
    }
    for(int j = 158; j < 823; j += 70){
        DrawLine(123, j, 753, j, BLACK);
    }

    // Adding plants to grid
    for(int i = 154, k = 0; i < 753; i += 70, k++){
        for(int j = 187, p = 0; j < 753; j += 70, p++){
            if(plants[k][p]){
                if(selectedPlantFromGrid && selectedGridX == k && selectedGridY == p){
                    DrawRectangle(i - 32, j - 26, 70, 70, Color{255, 255, 100, 100});
                }
                DrawRectangle(i, j, 5, 11, Color{50, 100, 50, 255});
                DrawRectangle(i, j, 5, 5, GREEN);
            }
        }
    }

    // Inventory section
    DrawText("Inventory", 875, 158, 28, BLACK);

    for(int i = 0; i < 5; i++){
        int slotY = 210 + (i * 70);
        Rectangle slot = {823, slotY, 70, 70};
        
        if(selectedInventorySlot == i){
            DrawRectangleRec(slot, Color{100, 200, 100, 255});
        } else {
            DrawRectangleRec(slot, LIGHTGRAY);
        }
        
        DrawRectangleLinesEx(slot, 4, BLACK);

        if(inventory[i] > 0){
            DrawRectangle(847, slotY + 26, 5, 11, Color{50, 100, 50, 255});
            DrawRectangle(847, slotY + 26, 5, 5, GREEN);
        }

        DrawText(TextFormat("%d", inventory[i]), 901, slotY + 21, 28, BLACK);
    }

    // Instructions
    DrawText("Left-click inventory, then grid to plant", 123, 805, 18, DARKGRAY);
    DrawText("Left-click plant, then empty slot to move", 123, 828, 18, DARKGRAY);
    DrawText("Right-click plant to remove & return to inventory", 735, 805, 18, DARKGRAY);
    DrawText("ESC to close", 1138, 828, 18, DARKGRAY);
}

string StoreScene::getType(){
    return "Store";
}