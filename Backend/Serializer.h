#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>

class Inventory;
class Greenhouse;
class Worker;
class Plant;
class PlantState;

class Serializer {
public:
    static std::string serializeInventory(Inventory* inventory);
    static std::string serializeGreenhouse(Greenhouse* greenhouse);
    static std::string serializeWorkers(const std::vector<Worker*>& workers);
    
    static void deserializeInventory(Inventory* inventory, const std::string& data);
    static void deserializeGreenhouse(Greenhouse* greenhouse, const std::string& data);
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