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

std::string Serializer::serializePlant(Plant* plant) {
    if (!plant) return "NULL";
    
    PlantState* state = plant->getPlantState();
    std::stringstream ss;
    
    ss << plant->getType() << "|"
       << plant->getBaseGrowthRate() << "|"
       << plant->getSellPrice() << "|"
       << (state ? state->getState() : "Seed") << "|"
       << (state ? state->getGrowth() : 0.0f) << "|"
       << (state ? state->getWater() : 100.0f) << "|"
       << (state ? state->getNutrients() : 100.0f);
    
    return ss.str();
}

Plant* Serializer::deserializePlant(const std::string& plantData) {
    if (plantData == "NULL") return nullptr;
    
    auto parts = split(plantData, '|');
    if (parts.size() < 7) return nullptr;
    
    try {
        std::string type = parts[0];
        float growthRate = std::stof(parts[1]);
        float sellPrice = std::stof(parts[2]);
        std::string stateName = parts[3];
        float growth = std::stof(parts[4]);
        float water = std::stof(parts[5]);
        float nutrients = std::stof(parts[6]);
        
        Plant* plant = nullptr;
        
        if (type == "Lettuce") plant = new Lettuce(new LettuceVisualStrategy(20.0f, 15.0f));
        else if (type == "Tomato") plant = new Tomato(new TomatoVisualStrategy(25.0f, 25.0f));
        else if (type == "Carrot") plant = new Carrot(new CarrotVisualStrategy(15.0f, 30.0f));
        else if (type == "Pumpkin") plant = new Pumpkin(new PumpkinVisualStrategy(40.0f, 30.0f));
        else if (type == "Strawberry") plant = new Strawberry(new StrawberryVisualStrategy(25.0f, 15.0f));
        else if (type == "Potato") plant = new Potato(new PotatoVisualStrategy(18.0f, 20.0f));
        else if (type == "Cucumber") plant = new Cucumber(new CucumberVisualStrategy(20.0f, 35.0f));
        else if (type == "Pepper") plant = new Pepper( new PepperVisualStrategy(25.0f, 30.0f));
        else if (type == "Sunflower") plant = new Sunflower(new SunflowerVisualStrategy(25.0f, 50.0f));
        else if (type == "Corn") plant = new Corn( new CornVisualStrategy(20.0f, 55.0f));
        else return nullptr;
        
        PlantState* newState = nullptr;
        if (stateName == "Seed") {
            newState = new SeedState(growth, water, nutrients);
        } else if (stateName == "Growing") {
            newState = new GrowingState(growth, water, nutrients);
        } else if (stateName == "Ripe") {
            newState = new RipeState(growth, water, nutrients);
        } else if (stateName == "Dead") {
            newState = new DeadState(growth, water, nutrients);
        } else {
            newState = new SeedState(growth, water, nutrients);
        }
        
        if (newState) {
            plant->setState(newState);
        }
        
        return plant;
    } catch (...) {
        return nullptr;
    }
}

std::string Serializer::serializeInventory(Inventory* inventory) {
    if (!inventory) return "";
    
    std::stringstream ss;
    std::vector<std::string> allPlants;
    
    for (size_t i = 0; i < inventory->getStackCount(); ++i) {
        const InventorySlot* slot = inventory->getSlot(i);
        if (slot && slot->getSize() > 0) {
            for (int j = 0; j < slot->getSize(); ++j) {
                Plant* plant = slot->getPlant(j);
                if (plant) {
                    allPlants.push_back(serializePlant(plant));
                } else {
                    allPlants.push_back(slot->getPlantType() + "|1.6|15.0|Seed|0.0|100.0|100.0");
                }
            }
        }
    }
    
    for (size_t i = 0; i < allPlants.size(); ++i) {
        ss << allPlants[i];
        if (i < allPlants.size() - 1) ss << "|";
    }
    
    return ss.str();
}

void Serializer::deserializeInventory(Inventory* inventory, const std::string& data) {
    if (!inventory || data.empty()) return;
    
    inventory->clear();
    
    auto parts = split(data, '|');
    
    for (size_t i = 0; i < parts.size(); i += 7) {
        if (i + 6 >= parts.size()) break;
        
        try {
            std::string plantData = parts[i] + "|" + parts[i+1] + "|" + parts[i+2] + "|" 
                                   + parts[i+3] + "|" + parts[i+4] + "|" + parts[i+5] + "|" + parts[i+6];
            
            Plant* plant = deserializePlant(plantData);
            if (plant) {
                inventory->add(plant);
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
            if (plantIndex + 6 < (int)parts.size()) {
                std::string plantData = parts[plantIndex] + "|" + parts[plantIndex+1] + "|" 
                                       + parts[plantIndex+2] + "|" + parts[plantIndex+3] + "|"
                                       + parts[plantIndex+4] + "|" + parts[plantIndex+5] + "|" + parts[plantIndex+6];
                Plant* plant = deserializePlant(plantData);
                if (plant) {
                    greenhouse->addPlant(plant, i);
                }
                plantIndex += 7;
            } else {
                plantIndex++;
            }
        }
    } catch (...) {
    }
}

std::string Serializer::serializeWorkers(const std::vector<Worker*>& workers) {
    if (workers.empty()) return "";
    
    std::stringstream ss;
    std::vector<std::string> workerData;
    
    for (const auto* worker : workers) {
        if (worker) {
            std::string workerType = worker->type();
            workerData.push_back(workerType);
        }
    }
    
    for (size_t i = 0; i < workerData.size(); ++i) {
        ss << workerData[i];
        if (i < workerData.size() - 1) ss << "|";
    }
    
    return ss.str();
}

void Serializer::deserializeWorkers(std::vector<Worker*>& workers, const std::string& data) {
    for (auto worker : workers) {
        if (worker) delete worker;
    }
    workers.clear();
    
    if (data.empty()) return;
    
    try {
        auto workerTypes = split(data, '|');
        
        for (const auto& workerType : workerTypes) {
            Worker* newWorker = nullptr;
            
            if (workerType == "Water Worker") {
                newWorker = new WaterWorker();
            } else if (workerType == "Fertiliser Worker") {
                newWorker = new FertiliserWorker();
            } else if (workerType == "Harvest Worker") {
                newWorker = new HarvestWorker();
                
            } else {
                newWorker = new Worker();
            }
            
            if (newWorker) {
                workers.push_back(newWorker);
            }
        }
    } catch (...) {}
}