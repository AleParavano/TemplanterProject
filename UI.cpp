#include "UI.h"

// #include "ActionLogManager.h" 
#include <iostream>

void DrawGlobalMenu() {
    // Draw Menu Background (Translucent Black)
    float menuX = SCREEN_WIDTH - MENU_WIDTH;
    Color translucentBlack = {0, 0, 0, 180}; 
    
    DrawRectangle(menuX, 0, MENU_WIDTH, SCREEN_HEIGHT, translucentBlack);
    DrawRectangleLinesEx({menuX, 0, MENU_WIDTH, SCREEN_HEIGHT}, 3, LIGHTGRAY);
    
    // Get Global Data
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    if (player) {
        //  CLOCK (Day, Hour, Minute) ---
        int clockY = 20;
        
        // Day
        DrawText(TextFormat("DAY: %d", player->getDay()), menuX + 10, clockY, 20, RAYWHITE);
        // Time
        DrawText(player->getTimeString().c_str(), menuX + 10, clockY + 30, 30, YELLOW);
        
        
        // PLAYER STATES (Money, Rating, Protection) 
        int statsY = 95;
        
        // Money
        DrawText(TextFormat("Money: $%.2f", player->getMoney()), menuX + 10, statsY, 20, LIME);
        
        // Rating
        std::string ratingStr = TextFormat("Rating: %d", player->getRating());
        std::string starStr = std::string(player->getRating(), '*'); 
        DrawText((ratingStr + " " + starStr).c_str(), menuX + 10, statsY + 35, 20, GOLD);

        // Protection Status (Patrol Command integration)
        std::string protectionStr = player->isProtected() ? "SAFE !!!" : "VULNERABLE???";
        Color protectionColor = player->isProtected() ? GREEN : RED;
        DrawText(protectionStr.c_str(), menuX + 10, statsY + 65, 20, protectionColor);
        
        
        // SAVE/LOAD BUTTONS 
        int buttonY = 225;
        Rectangle saveBtn = {menuX + 10, (float)buttonY, MENU_WIDTH - 20, 30};
        Rectangle loadBtn = {menuX + 10, (float)buttonY + 40, MENU_WIDTH - 20, 30};
        
        // Draw Save Button
        DrawRectangleRec(saveBtn, DARKGREEN);
        DrawText("SAVE GAME", saveBtn.x + (saveBtn.width - MeasureText("SAVE GAME", 20))/2, saveBtn.y + 5, 20, WHITE);
        
        // Draw Load Button
        DrawRectangleRec(loadBtn, MAROON);
        DrawText("LOAD GAME", loadBtn.x + (loadBtn.width - MeasureText("LOAD GAME", 20))/2, loadBtn.y + 5, 20, WHITE);
        
        // SEPARATOR LINE (Static position for scene-specific content) 
        int separatorY = 320;
        DrawLine(menuX + 5, separatorY, menuX + MENU_WIDTH - 5, separatorY, LIGHTGRAY);
        
        //  HINT TEXT (For the bottom half) 
        DrawText("SCENE MENU ", menuX + 50 , separatorY + 10, 20, RAYWHITE);

        // --- 7. MESSAGE LOG (Placeholder/Future Integration) ---
        // int logBoxY = SCREEN_HEIGHT - (MAX_LOG_MESSAGES * 18 + 20); 
        // DrawRectangle(menuX, logBoxY - 5, MENU_WIDTH, SCREEN_HEIGHT - logBoxY + 5, Fade(BLACK, 0.7f));
        // DrawRectangleLinesEx({menuX, (float)logBoxY - 5, MENU_WIDTH, SCREEN_HEIGHT - (float)logBoxY + 5}, 2, LIGHTGRAY);
        // ... (Future calls to ActionLogManager::getInstance()->getMessageLog() here)
    }
}


// --- Local Helper Function (Required by DrawTiledBackground) ---
static int ClampValue(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// GLOBAL IMPLEMENTATION
void DrawTiledBackground(Color baseColor, int width, int height)
{
    for (int y = 0; y < height; y += 20) {
        for (int x = 0; x < width; x += 20) {
            Color varColor = baseColor;
            
            // Generate a variation based on coordinates (noise effect)
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
void DrawTiledArea(Rectangle targetRect, Color baseColor) {
    const int TILE_SIZE = 20;

    // Determine the start and end points for tiling
    int startX = (int)targetRect.x;
    int startY = (int)targetRect.y;
    int endX = startX + (int)targetRect.width;
    int endY = startY + (int)targetRect.height;
    
    // We start iterating from the first tile boundary that covers targetRect
    int tileStartX = (startX / TILE_SIZE) * TILE_SIZE;
    int tileStartY = (startY / TILE_SIZE) * TILE_SIZE;

    for (int y = tileStartY; y < endY; y += TILE_SIZE) {
        for (int x = tileStartX; x < endX; x += TILE_SIZE) {
            
            // Generate color variation based on absolute screen coordinates (x, y)
            int variation = (x * 7 + y * 13) % 30 - 15;
            
            Color varColor = {
                (unsigned char)ClampValue(baseColor.r + variation, 0, 255),
                (unsigned char)ClampValue(baseColor.g + variation, 0, 255),
                (unsigned char)ClampValue(baseColor.b + variation, 0, 255),
                255
            };
            
            // Define the tile rectangle (full tile size)
            Rectangle tileRect = {(float)x, (float)y, (float)TILE_SIZE, (float)TILE_SIZE};
            
            // Clip the drawing to the targetRect boundary
            Rectangle drawRect = GetCollisionRec(tileRect, targetRect);
            
            // Draw the clipped portion
            DrawRectangleRec(drawRect, varColor);
        }
    }
}

void DrawBackButton(SceneType currentScene)
{
    if (currentScene == SCENE_OUTDOOR)
        return;

    Rectangle backBtn = {BACK_BUTTON_MARGIN, BACK_BUTTON_MARGIN, BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT};
    
    DrawRectangleRec(backBtn, MAROON);
    DrawRectangleLinesEx(backBtn, 2, RED);
    
    DrawText("BACK TO MAP", 
             backBtn.x + (BACK_BUTTON_WIDTH - MeasureText("↩ BACK TO MAP", 20)) / 2, 
             backBtn.y + 5, 
             20, WHITE);
}

void DrawPersonDetailed(Person p) {
    // Positioning is based on p.position
    DrawEllipse(p.position.x + p.shadowOffset.x, p.position.y + p.shadowOffset.y, 8, 4, Fade(BLACK, 0.4f));
    float legOffset = sinf(p.walkCycle) * 3;
    DrawRectangle(p.position.x - 3, p.position.y + 3, 2, 6 + legOffset, p.pantsColor);
    DrawRectangle(p.position.x + 1, p.position.y + 3, 2, 6 - legOffset, p.pantsColor);
    
    // Shirt color input is directly p.shirtColor
    DrawRectangle(p.position.x - 4, p.position.y - 5, 8, 8, p.shirtColor);
    
    // Note: ColorBrightness must be available
    DrawRectangleLinesEx({p.position.x - 4, p.position.y - 5, 8, 8}, 1, ColorBrightness(p.shirtColor, -0.3f));
    
    float armOffset = sinf(p.walkCycle) * 2;
    DrawRectangle(p.position.x - 5, p.position.y - 3 + armOffset, 1, 5, ColorBrightness(p.shirtColor, -0.2f));
    DrawRectangle(p.position.x + 4, p.position.y - 3 - armOffset, 1, 5, ColorBrightness(p.shirtColor, -0.2f));
    DrawCircle(p.position.x, p.position.y - 9, 4, {255, 220, 177, 255});
    DrawCircleLines(p.position.x, p.position.y - 9, 4, {210, 180, 140, 255});
    DrawCircle(p.position.x, p.position.y - 11, 4, {101, 67, 33, 255});
}