/**
 * @file Serializer.h
 * @brief Serialization utilities for save/load functionality.
 * @details Provides functions to serialize and deserialize game objects
 *          to/from strings for file-based persistence.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Memento
 * @see Caretaker
 * @see Player
 */

#pragma once

#include <string>
#include <vector>

// Forward declarations
class Inventory;
class Greenhouse;
class Worker;
class Plant;
class PlantState;

/**
 * @class Serializer
 * @brief Static utility class for object serialization.
 * 
 * Provides static methods to convert game objects to/from string representations
 * for file-based save/load functionality. All methods are static and utility-based.
 * 
 * @par Design
 * Serializer is designed as a collection of static utility functions.
 * It serves as the "worker" for the Memento pattern, handling the technical
 * details of object serialization.
 * 
 * @par Format
 * Objects are serialized using delimited text for human readability:
 * - Pipe character (|) separates object fields
 * - Comma character (,) separates nested data
 * - "NULL" string represents null pointers
 * - Format allows for easy debugging and manual inspection
 * 
 * @par Supported Objects
 * - **Plant**: Type, growth rate, sell price, state name, growth, water, nutrients
 * - **Inventory**: All plants in all slots with full state
 * - **Greenhouse**: Size, capacity, all plant positions with state
 * - **Worker**: Type identifier for reconstruction (WaterWorker, etc.)
 * 
 * @par Serialization Examples
 * ```
 * Plant: Tomato|1.0|55.0|Growing|50.5|80.0|90.0
 * Inventory: (multiple plants separated by |)
 * Greenhouse: 5,56|Tomato|...|NULL|Carrot|...|NULL|...
 * Workers: Water Worker|Fertiliser Worker|Harvest Worker
 * ```
 * 
 * @par Error Handling
 * - Returns nullptr for invalid plant data
 * - Skips malformed entries silently
 * - Recovers gracefully from parsing errors
 * - Used by Caretaker for file I/O
 * 
 * @see Memento
 * @see Caretaker
 * @see Player::createMemento()
 * @see Player::setMemento()
 */
class Serializer {
public:
    /**
     * @brief Serializes an entire inventory to a string.
     * @param inventory Pointer to inventory to serialize
     * @return String representation of all plants in pipe-delimited format
     * 
     * @details Iterates through all inventory slots and serializes each plant.
     *         Plants are separated by pipe characters (|).
     * 
     * @pre inventory must not be nullptr
     * @post All plants are represented as strings
     */
    static std::string serializeInventory(Inventory* inventory);

    /**
     * @brief Serializes a greenhouse to a string.
     * @param greenhouse Pointer to greenhouse to serialize
     * @return String representation including size, capacity, and all plants
     * 
     * @details Format: "size,capacity|plant1|plant2|NULL|..."
     *         Each plot is serialized in order, with NULL for empty plots.
     * 
     * @pre greenhouse must not be nullptr
     * @post All plant positions and states are captured
     */
    static std::string serializeGreenhouse(Greenhouse* greenhouse);

    /**
     * @brief Serializes a worker list to a string.
     * @param workers Vector of workers to serialize
     * @return String representation of worker types separated by pipes
     * 
     * @details Format: "Water Worker|Fertiliser Worker|Harvest Worker"
     *         Only stores worker type for reconstruction on load.
     * 
     * @post Worker types are enumerated for save file
     */
    static std::string serializeWorkers(const std::vector<Worker*>& workers);
    
    /**
     * @brief Deserializes an inventory from a string.
     * @param inventory Pointer to inventory to populate
     * @param data Serialized inventory string
     * 
     * @details Parses pipe-delimited plant data and reconstructs plants.
     *         Handles errors gracefully - skips malformed entries.
     * 
     * @pre inventory must not be nullptr
     * @post Inventory is cleared and repopulated with deserialized plants
     * @post Errors do not throw - missing data is skipped
     */
    static void deserializeInventory(Inventory* inventory, const std::string& data);

    /**
     * @brief Deserializes a greenhouse from a string.
     * @param greenhouse Pointer to greenhouse to populate
     * @param data Serialized greenhouse string
     * 
     * @details Reconstructs all plant positions in correct plot locations.
     *         Handles NULL entries (empty plots) correctly.
     * 
     * @pre greenhouse must not be nullptr
     * @post Greenhouse plots are repopulated with deserialized plants
     * @post Plant positions match original layout
     */
    static void deserializeGreenhouse(Greenhouse* greenhouse, const std::string& data);

    /**
     * @brief Deserializes a worker list from a string.
     * @param workers Vector to populate with deserialized workers
     * @param data Serialized worker string
     * 
     * @details Creates new worker instances based on type strings.
     *         Supports: "Water Worker", "Fertiliser Worker", "Harvest Worker"
     * 
     * @post Workers vector is cleared and repopulated with new instances
     * @post Unknown worker types create generic Worker instances
     */
    static void deserializeWorkers(std::vector<Worker*>& workers, const std::string& data);

private:
    /**
     * @brief Serializes a single plant.
     * @param plant Pointer to plant to serialize
     * @return Plant as pipe-delimited string or "NULL" if nullptr
     * 
     * @details Format: "Type|GrowthRate|SellPrice|StateName|Growth|Water|Nutrients"
     *         Example: "Tomato|1.0|55.0|Growing|50.5|80.0|90.0"
     */
    static std::string serializePlant(Plant* plant);

    /**
     * @brief Deserializes a plant from a string.
     * @param plantData Pipe-delimited plant string
     * @return Newly created Plant, or nullptr if invalid data
     * 
     * @details Parses plant type and creates instance using factories.
     *         Reconstructs state and resource levels.
     * 
     * @post Plant is fully reconstructed with original state
     * @return nullptr if type is unknown or parsing fails
     */
    static Plant* deserializePlant(const std::string& plantData);
    
    /**
     * @brief Splits a string by delimiter.
     * @param str String to split
     * @param delimiter Character to split on
     * @return Vector of substrings
     * 
     * @details Helper method for parsing delimited data.
     *         Example: split("a|b|c", '|') returns ["a", "b", "c"]
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * @brief Joins strings with delimiter.
     * @param parts Vector of strings to join
     * @param delimiter Character to join with
     * @return Concatenated string with delimiters
     * 
     * @details Helper method for creating delimited data.
     *         Example: join(["a", "b", "c"], '|') returns "a|b|c"
     */
    static std::string join(const std::vector<std::string>& parts, char delimiter);
};