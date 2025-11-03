/**
 * @file Serializer.h
 * @brief Game state serialization system
 *
 * Provides methods to convert game objects to/from string format for saving
 * and loading game state. Handles inventory, greenhouse, and worker data.
 *
 * @pattern Visitor - Traverses object structures for serialization
 */

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>

class Inventory;
class Greenhouse;
class Worker;
class Plant;
class PlantState;

/**
 * @class Serializer
 * @brief Static utility class for game state serialization
 *
 * Provides methods to convert complex game objects to/from string format
 * for save/load functionality.
 */
class Serializer {
public:
    /**
     * @brief Convert inventory to string format
     * @param inventory Inventory to serialize
     * @return Serialized inventory string
     */
    static std::string serializeInventory(Inventory* inventory);
    
    /**
     * @brief Convert greenhouse to string format
     * @param greenhouse Greenhouse to serialize
     * @return Serialized greenhouse string
     */
    static std::string serializeGreenhouse(Greenhouse* greenhouse);
    
    /**
     * @brief Convert worker list to string format
     * @param workers Vector of workers to serialize
     * @return Serialized worker string
     */
    static std::string serializeWorkers(const std::vector<Worker*>& workers);
    
    /**
     * @brief Restore inventory from string
     * @param inventory Target inventory to populate
     * @param data Serialized inventory string
     */
    static void deserializeInventory(Inventory* inventory, const std::string& data);
    
    /**
     * @brief Restore greenhouse from string
     * @param greenhouse Target greenhouse to populate
     * @param data Serialized greenhouse string
     */
    static void deserializeGreenhouse(Greenhouse* greenhouse, const std::string& data);
    
    /**
     * @brief Restore workers from string
     * @param workers Target vector to populate
     * @param data Serialized worker string
     */
    static void deserializeWorkers(std::vector<Worker*>& workers, const std::string& data);

private:
    static std::string serializePlant(Plant* plant);
    static Plant* deserializePlant(const std::string& plantData);
    
    static std::string serializePlantState(PlantState* state);
    static PlantState* deserializePlantState(const std::string& stateData);
    
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static std::string join(const std::vector<std::string>& parts, char delimiter);
};

#endif