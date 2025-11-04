#ifndef DEMO_H
#define DEMO_H

#include "raylib.h"
#include "StoreScene.h"
#include "SceneManager.h" 
#include "../Backend/Player.h"
#include "../Backend/Game.h"
#include <iostream>

/**
 * @class Demo
 * @brief The main application class that acts as the **Facade** for the game demo.
 *
 * It initializes the raylib window, manages core subsystems (like the scene manager and player), 
 * and provides the main game loop (`run()`). It encapsulates the complexity of the subsystems.
 */
class Demo {
private:
    // Subsystems
    
    /** @brief The primary game scene representing the store environment. */
    StoreScene store; 
    
    /** @brief The player object representing the user's avatar and inventory. */
    Player* player;
    
    /** @brief Manager responsible for handling transitions and updates across different scenes. */
    SceneManager manager; 
    
    // Window configuration
    /** @brief The fixed width of the game window. */
    const int width = 1400;
    
    /** @brief The fixed height of the game window. */
    const int height = 900;
    
    // Private helper methods
    /**
     * @brief Initializes the raylib window and sets basic configuration.
     */
    void initializeWindow();
    
    /**
     * @brief Sets up the player's initial inventory and game state for testing purposes.
     */
    void setupTestInventory();
    
    /**
     * @brief Draws on-screen text describing the controls for the demo.
     */
    void displayControls();
    
public:
    /**
     * @brief Constructor. Initializes the subsystems and prepares the game state.
     */
    Demo();
    
    /**
     * @brief Destructor. Handles cleanup, particularly deleting the dynamically allocated Player object.
     */
    ~Demo();
    
    // Main facade interface
    /**
     * @brief Executes the main game loop (initialize -> loop -> cleanup).
     * * This is the primary entry point for running the application.
     */
    void run();
    
    // Optional: Getters if needed
    /**
     * @brief Getter for the Player object.
     * @return A const pointer to the Player instance.
     */
    Player* getPlayer() const { return player; }
    
    /**
     * @brief Getter for the StoreScene object.
     * @return A pointer to the StoreScene instance.
     */
    StoreScene* getStore() { return &store; }
    
    /**
     * @brief Getter for the window width.
     * @return The window width in pixels.
     */
    int getWidth() const { return width; }
    
    /**
     * @brief Getter for the window height.
     * @return The window height in pixels.
     */
    int getHeight() const { return height; }
};

#endif