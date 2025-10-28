#include "PlantState.h"
#include "Plant.h"
#include <algorithm>
#include <iostream>

const float PlantState::SEED_TO_GROWING_THRESHOLD = 25.0f;
const float PlantState::GROWING_TO_RIPE_THRESHOLD = 100.0f;
const float PlantState::DEATH_WATER_THRESHOLD = 0.0f;
const float PlantState::DEATH_NUTRIENT_THRESHOLD = 0.0f;
const float PlantState::WATER_CONSUMPTION_RATE = 2.0f;     
const float PlantState::NUTRIENT_CONSUMPTION_RATE = 1.0f; 
const float PlantState::GROWTH_PER_TICK = 3.0f;          

PlantState::PlantState() : growth(0.0f), water(100.0f), nutrients(100.0f) {}

PlantState::PlantState(float gr, float wa, float nu) 
    : growth(gr), water(wa), nutrients(nu) {}

PlantState::PlantState(const PlantState& other) 
    : growth(other.growth), water(other.water), nutrients(other.nutrients) {}

PlantState::~PlantState() {}

// Getters
float PlantState::getGrowth() const { return growth; }
float PlantState::getWater() const { return water; }
float PlantState::getNutrients() const { return nutrients; }

// Setters
void PlantState::setGrowth(float g) { 
    growth = std::max(0.0f, g); 
}

void PlantState::setWater(float w) { 
    water = std::max(0.0f, w); 
}

void PlantState::setNutrients(float n) { 
    nutrients = std::max(0.0f, n); 
}

// Resource management
void PlantState::consumeResources(float waterConsumption, float nutrientConsumption) {
    water = std::max(0.0f, water - waterConsumption);
    nutrients = std::max(0.0f, nutrients - nutrientConsumption);
}

void PlantState::addWater(float amount) {
    water = std::min(100.0f, water + amount);
}

void PlantState::addNutrients(float amount) {
    nutrients = std::min(100.0f, nutrients + amount);
}

// ============================================================================
// SeedState
// ============================================================================

SeedState::SeedState() : PlantState(0.0f, 100.0f, 100.0f) {}

SeedState::SeedState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}

SeedState::SeedState(const SeedState& other) : PlantState(other) {}

SeedState::~SeedState() {}

void SeedState::handle(Plant* plant) {
    // Check if plant should die
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[SEED] Plant died from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    // Check if ready to grow into Growing state
    if (growth >= SEED_TO_GROWING_THRESHOLD) {
        std::cout << "[SEED -> GROWING] Plant sprouted! Growth: " << growth << std::endl;
        plant->setState(new GrowingState(growth, water, nutrients));
        return;
    }
}

void SeedState::tick(Plant* plant) {
    // Seeds consume less resources than growing plants
    float seedWaterConsumption = WATER_CONSUMPTION_RATE * 0.5f;
    float seedNutrientConsumption = NUTRIENT_CONSUMPTION_RATE * 0.5f;
    
    // Consume resources
    consumeResources(seedWaterConsumption, seedNutrientConsumption);
    
    // Only grow if resources are available
    if (water > 10.0f && nutrients > 10.0f) {
        // Seeds grow slower than mature plants
        growth += GROWTH_PER_TICK * 0.7f * plant->getGrowthRate();
    } else {
        std::cout << "[SEED] Low resources! Water: " << water 
                  << ", Nutrients: " << nutrients << std::endl;
    }
    
    // Check for state transition
    handle(plant);
}

std::string SeedState::getState() {
    return "Seed";
}

// ============================================================================
// GrowingState
// ============================================================================

GrowingState::GrowingState() : PlantState(25.0f, 100.0f, 100.0f) {}

GrowingState::GrowingState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}

GrowingState::GrowingState(const GrowingState& other) : PlantState(other) {}

GrowingState::~GrowingState() {}

void GrowingState::handle(Plant* plant) {
    // Check if plant should die
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[GROWING] Plant died from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    // Check if ready to ripen
    if (growth >= GROWING_TO_RIPE_THRESHOLD) {
        std::cout << "[GROWING -> RIPE] Plant is ripe! Growth: " << growth << std::endl;
        plant->setState(new RipeState(growth, water, nutrients));
        return;
    }
}

void GrowingState::tick(Plant* plant) {
    // Growing plants consume normal resources
    consumeResources(WATER_CONSUMPTION_RATE, NUTRIENT_CONSUMPTION_RATE);
    
    // Only grow if resources are available
    if (water > 5.0f && nutrients > 5.0f) {
        growth += GROWTH_PER_TICK * plant->getGrowthRate();
    } else {
        std::cout << "[GROWING] Warning! Low resources! Water: " << water 
                  << ", Nutrients: " << nutrients << std::endl;
        // Slow growth when resources are low
        growth += GROWTH_PER_TICK * 0.2f * plant->getGrowthRate();
    }
    
    // Check for state transition
    handle(plant);
}

std::string GrowingState::getState() {
    return "Growing";
}

// ============================================================================
// RipeState
// ============================================================================

RipeState::RipeState() : PlantState(100.0f, 100.0f, 100.0f) {}

RipeState::RipeState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}

RipeState::RipeState(const RipeState& other) : PlantState(other) {}

RipeState::~RipeState() {}

void RipeState::handle(Plant* plant) {
    // Check if plant should die from neglect
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[RIPE] Plant withered from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    // Ripe plants can over-ripen if left too long
    if (growth > 150.0f) {
        std::cout << "[RIPE] Plant over-ripened and died!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
}

void RipeState::tick(Plant* plant) {
    // Ripe plants consume fewer resources (maintenance mode)
    float ripeWaterConsumption = WATER_CONSUMPTION_RATE * 0.3f;
    float ripeNutrientConsumption = NUTRIENT_CONSUMPTION_RATE * 0.3f;
    
    consumeResources(ripeWaterConsumption, ripeNutrientConsumption);
    
    // Ripe plants continue growing slowly (aging)
    if (water > 5.0f && nutrients > 5.0f) {
        growth += GROWTH_PER_TICK * 0.2f;
    }
    
    // Check for state transition
    handle(plant);
}

std::string RipeState::getState() {
    return "Ripe";
}

// ============================================================================
// DeadState
// ============================================================================

DeadState::DeadState() : PlantState(0.0f, 0.0f, 0.0f) {}

DeadState::DeadState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}

DeadState::DeadState(const DeadState& other) : PlantState(other) {}

DeadState::~DeadState() {}

void DeadState::handle(Plant* plant) {
    // Dead plants don't transition to other states
    // They must be removed and replanted
}

void DeadState::tick(Plant* plant) {
    // Dead plants don't consume resources or grow
    // They just decay slowly
    growth = std::max(0.0f, growth - 0.5f);
    
    // No state transition needed
    handle(plant);
}

std::string DeadState::getState() {
    return "Dead";
}