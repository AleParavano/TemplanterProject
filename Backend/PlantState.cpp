/**
 * @file PlantState.cpp
 * @brief Implementation of plant lifecycle state behaviors.
 *
 * Contains implementations for SeedState, GrowingState, RipeState and DeadState.
 */

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

float PlantState::getGrowth() const { return growth; }
float PlantState::getWater() const { return water; }
float PlantState::getNutrients() const { return nutrients;
}

void PlantState::setNutrients(float n) { 
    nutrients = std::max(0.0f, n); 
}

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

void PlantState::applyGrowth(float growthAmount) {
    growth += growthAmount;
}

SeedState::SeedState() : PlantState(0.0f, 100.0f, 100.0f) {}
SeedState::SeedState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}
SeedState::SeedState(const SeedState& other) : PlantState(other) {}
SeedState::~SeedState() {}

float SeedState::getWaterConsumptionRate() const {
    return WATER_CONSUMPTION_RATE * 0.5f;
}

float SeedState::getNutrientConsumptionRate() const {
    return NUTRIENT_CONSUMPTION_RATE * 0.5f;
}

void SeedState::handle(Plant* plant) {
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[SEED] Plant died from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    if (growth >= SEED_TO_GROWING_THRESHOLD) {
        std::cout << "[SEED -> GROWING] Plant sprouted! Growth: " << growth << std::endl;
        plant->setState(new GrowingState(growth, water, nutrients));
        return;
    }
}

void SeedState::tick(Plant* plant) {
    consumeResources(getWaterConsumptionRate(), getNutrientConsumptionRate());
    
    if (water <= 10.0f || nutrients <= 10.0f) {
        std::cout << "[SEED] Low resources! Water: " << water 
                  << ", Nutrients: " << nutrients << std::endl;
    }
    
    handle(plant);
}

std::string SeedState::getState() {
    return "Seed";
}

GrowingState::GrowingState() : PlantState(25.0f, 100.0f, 100.0f) {}
GrowingState::GrowingState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}
GrowingState::GrowingState(const GrowingState& other) : PlantState(other) {}
GrowingState::~GrowingState() {}

float GrowingState::getWaterConsumptionRate() const {
    return WATER_CONSUMPTION_RATE;
}

float GrowingState::getNutrientConsumptionRate() const {
    return NUTRIENT_CONSUMPTION_RATE;
}

void GrowingState::handle(Plant* plant) {
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[GROWING] Plant died from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    if (growth >= GROWING_TO_RIPE_THRESHOLD) {
        std::cout << "[GROWING -> RIPE] Plant is ripe! Growth: " << growth << std::endl;
        plant->setState(new RipeState(growth, water, nutrients));
        return;
    }
}

void GrowingState::tick(Plant* plant) {
    consumeResources(getWaterConsumptionRate(), getNutrientConsumptionRate());
    
    if (water <= 5.0f || nutrients <= 5.0f) {
        std::cout << "[GROWING] Warning! Low resources! Water: " << water 
                  << ", Nutrients: " << nutrients << std::endl;
    }
    
    handle(plant);
}

std::string GrowingState::getState() {
    return "Growing";
}
RipeState::RipeState() : PlantState(100.0f, 100.0f, 100.0f) {}
RipeState::RipeState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}
RipeState::RipeState(const RipeState& other) : PlantState(other) {}
RipeState::~RipeState() {}

float RipeState::getWaterConsumptionRate() const {
    return WATER_CONSUMPTION_RATE * 0.3f;
}

float RipeState::getNutrientConsumptionRate() const {
    return NUTRIENT_CONSUMPTION_RATE * 0.3f;
}

void RipeState::handle(Plant* plant) {
    if (water <= DEATH_WATER_THRESHOLD || nutrients <= DEATH_NUTRIENT_THRESHOLD) {
        std::cout << "[RIPE] Plant withered from lack of resources!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
    
    if (growth > 150.0f) {
        std::cout << "[RIPE] Plant over-ripened and died!" << std::endl;
        plant->setState(new DeadState(growth, water, nutrients));
        return;
    }
}

void RipeState::tick(Plant* plant) {
    consumeResources(getWaterConsumptionRate(), getNutrientConsumptionRate());
    handle(plant);
}

std::string RipeState::getState() {
    return "Ripe";
}

DeadState::DeadState() : PlantState(0.0f, 0.0f, 0.0f) {}
DeadState::DeadState(float gr, float wa, float nu) : PlantState(gr, wa, nu) {}
DeadState::DeadState(const DeadState& other) : PlantState(other) {}
DeadState::~DeadState() {}

float DeadState::getWaterConsumptionRate() const {
    return 0.0f;
}

float DeadState::getNutrientConsumptionRate() const {
    return 0.0f;
}

void DeadState::handle(Plant* plant) {}

void DeadState::tick(Plant* plant) {
    growth = std::max(0.0f, growth - 0.5f);
    handle(plant);
}

std::string DeadState::getState() {
    return "Dead";
}