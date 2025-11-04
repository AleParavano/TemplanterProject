#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "../Backend/Game.h"  // Assumed to contain core game state access
#include "../Backend/Player.h" // Assumed to contain player data access
#include "ObjectTypes.h"      // Includes structures like Person
#include "Scene.h"            // Includes SceneType enum
#include <string>

// --- Global UI Constants ---
/** @brief The standard width of the game screen (1400 pixels). */
#define SCREEN_WIDTH 1400
/** @brief The standard height of the game screen (900 pixels). */
#define SCREEN_HEIGHT 900
/** @brief The fixed width allocated for the persistent side menu/HUD. */
#define MENU_WIDTH 250
/** @brief The maximum number of scrolling text log messages to display at once. */
#define MAX_LOG_MESSAGES 10

// --- Defines for Button ---\
/** @brief Standard width for a generic back button element. */
#define BACK_BUTTON_WIDTH 180
/** @brief Standard height for a generic back button element. */
#define BACK_BUTTON_HEIGHT 30
/** @brief Standard margin/padding used around the back button. */
#define BACK_BUTTON_MARGIN 20


// --- Global UI Drawing Utility Functions ---
/**
 * @brief Draws a rectangular area filled with a repetitive, tiled pattern (e.g., grass, floor tile).
 *
 * Tiles start their pattern relative to the screen origin (0, 0).
 * @param targetRect The bounding box of the area to fill.
 * @param baseColor The primary color of the tile.
 */
void DrawTiledArea(Rectangle targetRect, Color baseColor);

/**
 * @brief Draws a tiled background across the entire specified width and height.
 * @param baseColor The primary color for the background tile.
 * @param width The total width of the area to cover (usually SCREEN_WIDTH).
 * @param height The total height of the area to cover (usually SCREEN_HEIGHT).
 */
void DrawTiledBackground(Color baseColor, int width, int height);

/**
 * @brief Renders a standard 'Back' or 'Exit' button, typically positioned in a corner.
 * * Function may handle button click logic internally.
 * @param currentScene The type of the scene currently being rendered (used for context/exit target).
 */
void DrawBackButton(SceneType currentScene);

/**
 * @brief Renders the detailed visual representation of a Person NPC.
 * * This function is defined here as a utility used by various scenes (Outdoor, Store).
 * @param p The Person structure containing position, color, and animation data.
 */
void DrawPersonDetailed(Person p);

/**
 * @brief Renders the persistent, non-scene-specific heads-up display (HUD) elements.
 * * This includes money, time of day, status messages, and inventory/global buttons.
 */
void DrawGlobalMenu();


// --- Utility Functions ---

/**
 * @brief Draws a basic text message log (e.g., system announcements, transaction records).
 * * Assumed to manage a scrolling/fading list of messages.
 * @param messages The list of strings to display.
 */
void DrawMessageLog(const std::vector<std::string>& messages);


#endif // UI_H