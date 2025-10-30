#include "Serializer.h"
#include "Inventory.h"
#include "Greenhouse.h"
#include "Worker.h"
#include "Plant.h"
#include "PlantState.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> Serializer::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string Serializer::join(const std::vector<std::string>& parts, char delimiter) {
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        if (i < parts.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

std::string Serializer::serializePlantState(PlantState* state) {
    if (!state) return "NONE";
    
    std::stringstream ss;
    std::string stateName = state->getState();
    
    ss << stateName << "|" 
       << state->getGrowth() << "|"
       << state->getWater() << "|"
       << state->getNutrients();
    
    return ss.str();
}

PlantState* Serializer::deserializePlantState(const std::string& stateData) {
    if (stateData == "NONE") return nullptr;
    
    auto parts = split(stateData, '|');
    if (parts.size() < 4) return nullptr;
    
    try {
        std::string stateName = parts[0];
        float growth = std::stof(parts[1]);
        float water = std::stof(parts[2]);
        float nutrients = std::stof(parts[3]);
        
        if (stateName == "Seed") {
            return new SeedState(growth, water, nutrients);
        } else if (stateName == "Growing") {
            return new GrowingState(growth, water, nutrients);
        } else if (stateName == "Ripe") {
            return new RipeState(growth, water, nutrients);
        } else if (stateName == "Dead") {
            return new DeadState(growth, water, nutrients);
        }
    } catch (...) {
        return nullptr;
    }
    
    return nullptr;
}

std::string Serializer::serializePlant(Plant* plant) {
    if (!plant) return "NULL";
    
    std::stringstream ss;
    
    ss << plant->getType() << "|"
       << plant->getBaseGrowthRate() << "|"
       << plant->getSellPrice() << "|"
       << serializePlantState(plant->getPlantState());
    
    return ss.str();
}

Plant* Serializer::deserializePlant(const std::string& plantData) {
    if (plantData == "NULL") return nullptr;
    
    auto parts = split(plantData, '|');
    if (parts.size() < 4) return nullptr;
    
    try {
        std::string type = parts[0];
        float growthRate = std::stof(parts[1]);
        float sellPrice = std::stof(parts[2]);
        
        Plant* plant = nullptr;
        
        if (type == "Lettuce") plant = new Lettuce();
        else if (type == "Tomato") plant = new Tomato();
        else if (type == "Carrot") plant = new Carrot();
        else if (type == "Pumpkin") plant = new Pumpkin();
        else if (type == "Strawberry") plant = new Strawberry();
        else if (type == "Potato") plant = new Potato();
        else if (type == "Cucumber") plant = new Cucumber();
        else return nullptr;
        
        std::string stateData = parts[3];
        if (parts.size() > 4) {
            for (size_t i = 4; i < parts.size(); ++i) {
                stateData += "|" + parts[i];
            }
        }
        
        PlantState* state = deserializePlantState(stateData);
        if (state) {
            plant->setState(state);
        }
        
        return plant;
    } catch (...) {
        return nullptr;
    }
}

std::string Serializer::serializeInventory(Inventory* inventory) {
    if (!inventory) return "";
    
    std::stringstream ss;
    std::vector<std::string> stacks;
    
    std::vector<std::string> plantTypes = {
        "Lettuce", "Tomato", "Carrot", "Pumpkin", 
        "Strawberry", "Potato", "Cucumber"
    };
    
    for (const auto& type : plantTypes) {
        int count = inventory->getPlantCount(type);
        if (count > 0) {
            stacks.push_back(type + ":" + std::to_string(count));
        }
    }
    
    for (size_t i = 0; i < stacks.size(); ++i) {
        ss << stacks[i];
        if (i < stacks.size() - 1) ss << "|";
    }
    
    return ss.str();
}

void Serializer::deserializeInventory(Inventory* inventory, const std::string& data) {
    if (!inventory || data.empty()) return;
    
    inventory->clear();
    
    auto stacks = split(data, '|');
    
    for (const auto& stack : stacks) {
        auto parts = split(stack, ':');
        if (parts.size() < 2) continue;
        
        try {
            std::string type = parts[0];
            int count = std::stoi(parts[1]);
            
            for (int i = 0; i < count; ++i) {
                Plant* plant = nullptr;
                
                if (type == "Lettuce") plant = new Lettuce();
                else if (type == "Tomato") plant = new Tomato();
                else if (type == "Carrot") plant = new Carrot();
                else if (type == "Pumpkin") plant = new Pumpkin();
                else if (type == "Strawberry") plant = new Strawberry();
                else if (type == "Potato") plant = new Potato();
                else if (type == "Cucumber") plant = new Cucumber();
                
                if (plant) {
                    inventory->add(plant);
                }
            }
        } catch (...) {
            continue;
        }
    }
}

std::string Serializer::serializeGreenhouse(Greenhouse* greenhouse) {
    if (!greenhouse) return "";
    
    std::stringstream ss;
    
    ss << greenhouse->getSize() << "," 
       << greenhouse->getCapacity() << "|";
    
    std::vector<std::string> plants;
    for (int i = 0; i < greenhouse->getCapacity(); ++i) {
        Plant* plant = greenhouse->getPlant(i);
        plants.push_back(serializePlant(plant));
    }
    
    for (size_t i = 0; i < plants.size(); ++i) {
        ss << plants[i];
        if (i < plants.size() - 1) ss << "|";
    }
    
    return ss.str();
}

void Serializer::deserializeGreenhouse(Greenhouse* greenhouse, const std::string& data) {
    if (!greenhouse || data.empty()) return;
    
    for (int i = 0; i < greenhouse->getCapacity(); ++i) {
        greenhouse->removePlant(i);
    }
    
    try {
        auto parts = split(data, '|');
        if (parts.empty()) return;
        
        auto header = split(parts[0], ',');
        if (header.size() < 2) return;
        
        int size = std::stoi(header[0]);
        int capacity = std::stoi(header[1]);
        
        int plantIndex = 1;
        for (int i = 0; i < capacity && plantIndex < (int)parts.size(); ++i) {
            Plant* plant = deserializePlant(parts[plantIndex]);
            if (plant) {
                greenhouse->addPlant(plant, i);
            }
            plantIndex++;
        }
    } catch (...) {
    }
}

std::string Serializer::serializeWorkers(const std::vector<Worker*>& workers) {
    if (workers.empty()) return "0";
    
    std::stringstream ss;
    ss << workers.size();
    
    return ss.str();
}

void Serializer::deserializeWorkers(std::vector<Worker*>& workers, const std::string& data) {
    for (auto worker : workers) {
        if (worker) delete worker;
    }
    workers.clear();
    
    if (data.empty()) return;
    
    try {
        int count = std::stoi(data);
        for (int i = 0; i < count; ++i) {
            Worker* newWorker = new Worker();
            workers.push_back(newWorker);
        }
    } catch (...) {
    }
}