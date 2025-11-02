#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "../Backend\Game.h"
#include "../Backend\Player.h"
#include "Types.h"
#include "Scene.h"
#include <string>

// Defines for Global Menu 
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900
#define MENU_WIDTH 250 
#define MAX_LOG_MESSAGES 10

// --- Defines for Button ---
#define BACK_BUTTON_WIDTH 180
#define BACK_BUTTON_HEIGHT 30
#define BACK_BUTTON_MARGIN 20



//Tiles start their pattern relative to the screen origin (0, 0)
 void DrawTiledArea(Rectangle targetRect, Color baseColor);
//Function to tile a background 
 void DrawTiledBackground(Color baseColor, int width, int height);
 // Function to draw the back button 
void DrawBackButton(SceneType currentScene);

void DrawPersonDetailed(Person p);

void DrawGlobalMenu();




#endif 