/**
 * @file Game.h
 * @brief Singleton class managing the main game state and persistence.
 * @details Implements the Singleton pattern to ensure a single global instance of the game.
 *          Provides access to the player state and handles save/load functionality through
 *          the Memento pattern via the Caretaker.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Player
 * @see Caretaker
 * @see Memento
 */

#pragma once

#include "Player.h"
#include "Caretaker.h"

/**
 * @class Game
 * @brief Main game singleton managing game state and persistence.
 * 
 * The Game class implements the Singleton pattern to maintain a single instance
 * of the game throughout the application lifecycle. It provides:
 * - Access to the player state through a Player object
 * - Save/load functionality via the Caretaker (Memento pattern)
 * - Global access point for all game systems
 * 
 * @par Design Pattern: Singleton
 * Ensures only one instance of Game exists, providing a centralized point of access
 * for the game state and all major subsystems.
 * 
 * @par Design Pattern: Memento
 * Uses Caretaker and Memento to implement save/load functionality, allowing the
 * game state to be persisted and restored.
 * 
 * @example
 * @code
 * Game* game = Game::getInstance();
 * Player& player = game->getPlayer();
 * game->saveGame();
 * @endcode
 */
class Game
{
private:
    static Game *uniqueInstance;  ///< Static pointer to the singleton instance
    Player player;                ///< The player object managing all game data
    Caretaker caretaker;          ///< Handles save/load operations using Memento pattern

public:
    /**
     * @brief Default constructor.
     * @details Initializes the Game with a default Player and Caretaker using
     *          "game_state.txt" as the save file.
     */
    Game();

    /**
     * @brief Destructor.
     * @details Cleans up the Game instance.
     */
    ~Game();

    /**
     * @brief Gets the singleton instance of the Game.
     * @return Pointer to the single Game instance. Creates one if it doesn't exist.
     * 
     * @par Thread Safety
     * This implementation is not thread-safe. For multi-threaded environments,
     * consider using double-checked locking or other thread-safe patterns.
     */
    static Game *getInstance();

    /**
     * @brief Gets a reference to the player.
     * @return Reference to the Player object.
     * 
     * @note Use getPlayerPtr() if you need a pointer instead.
     */
    Player &getPlayer();

    /**
     * @brief Gets a pointer to the player.
     * @return Pointer to the Player object.
     * 
     * @note Use getPlayer() if you need a reference instead.
     */
    Player *getPlayerPtr();

    /**
     * @brief Saves the current game state to disk.
     * @details Creates a Memento from the current player state and passes it to the
     *          Caretaker, which automatically writes the state to the save file.
     * 
     * @see Caretaker::addMemento()
     * @see Player::createMemento()
     */
    void saveGame();

    /**
     * @brief Loads the previously saved game state from disk.
     * @details Retrieves a Memento from the Caretaker and applies it to the player,
     *          restoring the game to a previously saved state.
     * 
     * @see Caretaker::getMemento()
     * @see Player::setMemento()
     */
    void loadGame();

    /**
     * @brief Cleans up the singleton instance.
     * @details Should be called at game shutdown to properly delete the singleton.
     *          Sets the singleton pointer to nullptr.
     * 
     * @note This should be called before the program exits to avoid memory leaks.
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