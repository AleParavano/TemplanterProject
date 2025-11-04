#pragma once

#include "Player.h"
#include "Caretaker.h"

/**
 * @class Game
 * @brief Represents the main game context and manages the overall state.
 * * This class is implemented using the **Singleton** design pattern to ensure
 * only one instance of the game exists throughout the application lifecycle.
 */
class Game
{
private:
    /**
     * @brief The static pointer to the unique instance of the Game class (Singleton pattern).
     */
    static Game *uniqueInstance;
    
    /**
     * @brief The main player object managed by the game.
     */
    Player player;
    
    /**
     * @brief The Caretaker object responsible for managing Mementos (save states).
     */
    Caretaker caretaker;

public:
    /**
     * @brief Private default constructor for the Singleton pattern.
     */
    Game();
    
    /**
     * @brief Destructor for the Game class.
     */
    ~Game();
    
    /**
     * @brief Access method for the Singleton instance.
     * @return A pointer to the unique Game instance, creating it if it doesn't exist.
     */
    static Game *getInstance();
    
    /**
     * @brief Gets a reference to the Player object.
     * @return A reference to the internal Player instance.
     */
    Player &getPlayer();
    
    /**
     * @brief Gets a pointer to the Player object.
     * @return A raw pointer to the internal Player instance.
     */
    Player *getPlayerPtr();

    /**
     * @brief Initiates the game saving process.
     * * Creates a Memento from the Player's current state and gives it to the Caretaker.
     */
    void saveGame();
    
    /**
     * @brief Initiates the game loading process.
     * * Retrieves the Memento from the Caretaker and restores the Player's state from it.
     */
    void loadGame();

    /**
     * @brief Static function to clean up and delete the unique Singleton instance.
     * * Should be called once when the application shuts down.
     */
    static void cleanup()
    {
        if (uniqueInstance)
        {
            delete uniqueInstance;
            uniqueInstance = nullptr;
        }
    }
};