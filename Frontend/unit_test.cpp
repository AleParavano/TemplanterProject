#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// Backend includes
#include "../Backend/Game.h"
#include "../Backend/Player.h"
#include "../Backend/Plant.h"
#include "../Backend/PlantFactory.h"
#include "../Backend/PlantState.h"
#include "../Backend/Greenhouse.h"
#include "../Backend/Inventory.h"
#include "../Backend/Worker.h"
#include "../Backend/Command.h"
#include "../Backend/Customer.h"
#include "../Backend/CustomerFactory.h"
#include "../Backend/Store.h"
#include "../Backend/SeedAdapter.h"
#include "../Backend/Caretaker.h"
#include "../Backend/Memento.h"
#include "../Backend/Serializer.h"
#include "../Backend/GrowthCycle.h"

using namespace std;

// Test counters
int tests_passed = 0;
int tests_failed = 0;
int tests_total = 0;

// Macro for assertions
#define TEST_ASSERT(condition, message) \
    do { \
        tests_total++; \
        if (condition) { \
            tests_passed++; \
            cout << "  [PASS] " << message << endl; \
        } else { \
            tests_failed++; \
            cout << "  [FAIL] " << message << endl; \
        } \
    } while(0)

#define TEST_SECTION(name) \
    cout << "\n=== " << name << " ===" << endl;

// Forward declaration for cleanup
extern void cleanupPlantCatalog();

// ============================================================================
// UNIT TESTS
// ============================================================================

// --- PlantState Tests ---
void test_PlantState_Initialization() {
    TEST_SECTION("PlantState Initialization");
    
    SeedState seed(0.0f, 100.0f, 100.0f);
    TEST_ASSERT(seed.getGrowth() == 0.0f, "Seed starts at 0% growth");
    TEST_ASSERT(seed.getWater() == 100.0f, "Seed starts with 100% water");
    TEST_ASSERT(seed.getNutrients() == 100.0f, "Seed starts with 100% nutrients");
    TEST_ASSERT(seed.getState() == "Seed", "State name is 'Seed'");
    
    GrowingState growing(50.0f, 80.0f, 70.0f);
    TEST_ASSERT(growing.getGrowth() == 50.0f, "Growing state preserves growth");
    TEST_ASSERT(growing.getState() == "Growing", "State name is 'Growing'");
    
    RipeState ripe(100.0f, 60.0f, 50.0f);
    TEST_ASSERT(ripe.getGrowth() == 100.0f, "Ripe state at 100% growth");
    TEST_ASSERT(ripe.getState() == "Ripe", "State name is 'Ripe'");
    
    DeadState dead(25.0f, 0.0f, 0.0f);
    TEST_ASSERT(dead.getState() == "Dead", "State name is 'Dead'");
}

void test_PlantState_ResourceManagement() {
    TEST_SECTION("PlantState Resource Management");
    
    SeedState state(10.0f, 50.0f, 60.0f);
    
    state.addWater(30.0f);
    TEST_ASSERT(state.getWater() == 80.0f, "Adding water increases level");
    
    state.addWater(50.0f);
    TEST_ASSERT(state.getWater() == 100.0f, "Water caps at 100%");
    
    state.addNutrients(20.0f);
    TEST_ASSERT(state.getNutrients() == 80.0f, "Adding nutrients increases level");
    
    state.consumeResources(30.0f, 20.0f);
    TEST_ASSERT(state.getWater() == 70.0f, "Consuming water decreases level");
    TEST_ASSERT(state.getNutrients() == 60.0f, "Consuming nutrients decreases level");
}

void test_PlantState_GrowthApplication() {
    TEST_SECTION("PlantState Growth Application");
    
    SeedState state(20.0f, 100.0f, 100.0f);
    
    state.applyGrowth(15.0f);
    TEST_ASSERT(state.getGrowth() == 35.0f, "Growth increases correctly");
    
    state.applyGrowth(100.0f);
    TEST_ASSERT(state.getGrowth() == 100.0f, "Growth caps at 100%");
}

// --- Plant Tests ---
void test_Plant_Creation() {
    TEST_SECTION("Plant Creation");
    
    Plant* lettuce = new Lettuce(nullptr);
    TEST_ASSERT(lettuce != nullptr, "Lettuce plant created");
    TEST_ASSERT(lettuce->getType() == "Lettuce", "Plant type is Lettuce");
    TEST_ASSERT(lettuce->getStateName() == "Seed", "Plant starts as Seed");
    TEST_ASSERT(lettuce->getGrowth() == 0.0f, "Initial growth is 0");
    TEST_ASSERT(!lettuce->isRipe(), "Plant is not ripe initially");
    TEST_ASSERT(!lettuce->isDead(), "Plant is not dead initially");
    delete lettuce;
    
    Plant* tomato = new Tomato(nullptr);
    TEST_ASSERT(tomato->getType() == "Tomato", "Tomato type correct");
    TEST_ASSERT(tomato->getSellPrice() == 55.0f, "Tomato sell price correct");
    delete tomato;
}

void test_Plant_WateringAndFertilizing() {
    TEST_SECTION("Plant Watering and Fertilizing");
    
    Plant* plant = new Carrot(nullptr);
    
    // Deplete resources
    for (int i = 0; i < 20; i++) {
        plant->tick();
    }
    
    float waterBefore = plant->getWater();
    plant->water(50.0f);
    TEST_ASSERT(plant->getWater() > waterBefore, "Watering increases water level");
    
    float nutrientsBefore = plant->getNutrients();
    plant->fertilize(50.0f);
    TEST_ASSERT(plant->getNutrients() > nutrientsBefore, "Fertilizing increases nutrients");
    
    delete plant;
}

void test_Plant_StateTransitions() {
    TEST_SECTION("Plant State Transitions");
    
    Plant* plant = new Lettuce(nullptr);
    
    // Grow to Growing state
    for (int i = 0; i < 15; i++) {
        plant->water(10.0f);
        plant->fertilize(10.0f);
        plant->tick();
    }
    TEST_ASSERT(plant->getStateName() == "Growing", "Plant transitions to Growing");
    
    // Grow to Ripe state
    for (int i = 0; i < 50; i++) {
        plant->water(10.0f);
        plant->fertilize(10.0f);
        plant->tick();
    }
    TEST_ASSERT(plant->isRipe(), "Plant becomes ripe");
    
    delete plant;
}

void test_Plant_Death() {
    TEST_SECTION("Plant Death from Neglect");
    
    Plant* plant = new Tomato(nullptr);
    
    // Neglect plant
    for (int i = 0; i < 100; i++) {
        plant->tick();
        if (plant->isDead()) {
            break;
        }
    }
    
    TEST_ASSERT(plant->isDead(), "Plant dies from lack of resources");
    
    delete plant;
}

// --- GrowthCycle Tests ---
void test_GrowthCycle_Normal() {
    TEST_SECTION("Normal Growth Cycle");
    
    Plant* plant = new Lettuce(nullptr);
    NormalGrowthCycle* normalCycle = new NormalGrowthCycle();
    plant->setGrowthCycle(normalCycle);
    
    float growthBefore = plant->getGrowth();
    plant->tick();
    float growthAfter = plant->getGrowth();
    
    TEST_ASSERT(growthAfter > growthBefore, "Normal cycle increases growth");
    
    delete plant;
}

void test_GrowthCycle_Boosted() {
    TEST_SECTION("Boosted Growth Cycle");
    
    Plant* plant1 = new Lettuce(nullptr);
    Plant* plant2 = new Lettuce(nullptr);
    
    BoostedGrowthCycle* boostedCycle = new BoostedGrowthCycle();
    plant2->setGrowthCycle(boostedCycle);
    
    // Tick both plants
    for (int i = 0; i < 5; i++) {
        plant1->tick();
        plant2->tick();
    }
    
    TEST_ASSERT(plant2->getGrowth() > plant1->getGrowth(), "Boosted cycle grows faster");
    
    delete plant1;
    delete plant2;
}

// --- Inventory Tests ---
void test_Inventory_AddRemove() {
    TEST_SECTION("Inventory Add/Remove");
    
    Inventory* inv = new Inventory(10);
    
    TEST_ASSERT(inv->getMaxSlots() == 10, "Inventory has correct capacity");
    
    Plant* plant1 = new Lettuce(nullptr);
    TEST_ASSERT(inv->add(plant1), "Can add plant to inventory");
    TEST_ASSERT(inv->getPlantCount("Lettuce") == 1, "Plant count correct after add");
    
    Plant* plant2 = new Lettuce(nullptr);
    TEST_ASSERT(inv->add(plant2), "Can add another plant of same type");
    TEST_ASSERT(inv->getPlantCount("Lettuce") == 2, "Plant stacking works");
    
    Plant* removed = inv->removeItem("Lettuce");
    TEST_ASSERT(removed != nullptr, "Can remove plant from inventory");
    TEST_ASSERT(removed->getType() == "Lettuce", "Removed correct plant type");
    TEST_ASSERT(inv->getPlantCount("Lettuce") == 1, "Count decreases after removal");
    delete removed;
    
    delete inv;
}

void test_Inventory_Stacking() {
    TEST_SECTION("Inventory Stacking");
    
    Inventory* inv = new Inventory(5);
    
    // Add multiple plants of same type
    for (int i = 0; i < 10; i++) {
        Plant* plant = new Tomato(nullptr);
        inv->add(plant);
    }
    
    TEST_ASSERT(inv->getPlantCount("Tomato") == 10, "All plants stacked correctly");
    TEST_ASSERT(inv->getStackCount() <= 5, "Uses minimal number of slots");
    
    delete inv;
}

void test_Inventory_FullCheck() {
    TEST_SECTION("Inventory Full Check");
    
    Inventory* inv = new Inventory(2);
    
    // Fill inventory completely (2 slots × 64 capacity = 128 items)
    for (int i = 0; i < 128; i++) {
        Plant* plant = new Lettuce(nullptr);
        if (!inv->add(plant)) {
            delete plant;
            break;
        }
    }
    
    TEST_ASSERT(inv->isFull(), "Inventory reports full when at capacity");
    
    Plant* extraPlant = new Lettuce(nullptr);
    TEST_ASSERT(!inv->add(extraPlant), "Cannot add to full inventory");
    delete extraPlant;
    
    delete inv;
}

// --- Greenhouse Tests ---
void test_Greenhouse_AddRemovePlants() {
    TEST_SECTION("Greenhouse Add/Remove Plants");
    
    Inventory* inv = new Inventory(10);
    Greenhouse* gh = new Greenhouse(inv);
    
    TEST_ASSERT(gh->getCapacity() == 56, "Greenhouse has correct initial capacity");
    TEST_ASSERT(gh->getSize() == 0, "Greenhouse starts empty");
    
    Plant* plant = new Lettuce(nullptr);
    TEST_ASSERT(gh->addPlant(plant, 0), "Can add plant at specific position");
    TEST_ASSERT(gh->getSize() == 1, "Size increases after adding plant");
    TEST_ASSERT(gh->getPlant(0) == plant, "Can retrieve plant from position");
    
    TEST_ASSERT(gh->removePlant(0), "Can remove plant");
    TEST_ASSERT(gh->getSize() == 0, "Size decreases after removal");
    TEST_ASSERT(gh->getPlant(0) == nullptr, "Position is empty after removal");
    
    delete gh;
    delete inv;
}

void test_Greenhouse_Harvesting() {
    TEST_SECTION("Greenhouse Harvesting");
    
    Inventory* inv = new Inventory(10);
    Greenhouse* gh = new Greenhouse(inv);
    
    Plant* plant = new Lettuce(nullptr);
    gh->addPlant(plant);
    
    // Grow plant to ripe
    for (int i = 0; i < 50; i++) {
        plant->water(10.0f);
        plant->fertilize(10.0f);
        plant->tick();
    }
    
    int invCountBefore = inv->getPlantCount("Lettuce");
    gh->harvestPlant(0);
    int invCountAfter = inv->getPlantCount("Lettuce");
    
    TEST_ASSERT(invCountAfter == invCountBefore + 1, "Harvest adds plant to inventory");
    TEST_ASSERT(gh->getSize() == 0, "Greenhouse plot empty after harvest");
    
    delete gh;
    delete inv;
}

void test_Greenhouse_TickAllPlants() {
    TEST_SECTION("Greenhouse Tick All Plants");
    
    Inventory* inv = new Inventory(10);
    Greenhouse* gh = new Greenhouse(inv);
    
    // Add multiple plants
    for (int i = 0; i < 5; i++) {
        Plant* plant = new Tomato(nullptr);
        gh->addPlant(plant);
    }
    
    gh->tickAllPlants();
    
    // Check that all plants have ticked
    for (int i = 0; i < 5; i++) {
        Plant* plant = gh->getPlant(i);
        TEST_ASSERT(plant->getWater() < 100.0f, "Plant has consumed resources");
    }
    
    delete gh;
    delete inv;
}

// --- Worker Tests ---
void test_Worker_Creation() {
    TEST_SECTION("Worker Creation");
    
    WaterWorker* waterWorker = new WaterWorker();
    TEST_ASSERT(waterWorker != nullptr, "WaterWorker created");
    TEST_ASSERT(string(waterWorker->type()) == "Water Worker", "WaterWorker type correct");
    delete waterWorker;
    
    FertiliserWorker* fertWorker = new FertiliserWorker();
    TEST_ASSERT(string(fertWorker->type()) == "Fertiliser Worker", "FertiliserWorker type correct");
    delete fertWorker;
    
    HarvestWorker* harvestWorker = new HarvestWorker();
    TEST_ASSERT(string(harvestWorker->type()) == "Harvest Worker", "HarvestWorker type correct");
    delete harvestWorker;
}

void test_Worker_Commands() {
    TEST_SECTION("Worker Commands");
    
    Inventory* inv = new Inventory(10);
    Greenhouse* gh = new Greenhouse(inv);
    
    Plant* plant = new Tomato(nullptr);
    gh->addPlant(plant, 0);
    
    // Deplete water
    for (int i = 0; i < 25; i++) {
        plant->tick();
    }
    
    float waterBefore = plant->getWater();
    
    WaterWorker* worker = new WaterWorker();
    gh->attach(worker);
    gh->notify();
    
    // Give worker time to process
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    TEST_ASSERT(plant->getWater() >= waterBefore, "Worker processes commands");
    
    delete worker;
    delete gh;
    delete inv;
}

// --- Command Tests ---
void test_Commands_Execution() {
    TEST_SECTION("Command Execution");
    
    Inventory* inv = new Inventory(10);
    Greenhouse* gh = new Greenhouse(inv);
    
    Plant* plant = new Lettuce(nullptr);
    gh->addPlant(plant);
    
    float waterBefore = plant->getWater();
    WaterCommand waterCmd(plant, gh);
    waterCmd.execute();
    TEST_ASSERT(plant->getWater() >= waterBefore, "WaterCommand executes");
    
    float nutrientsBefore = plant->getNutrients();
    FertilizeCommand fertCmd(plant, gh);
    fertCmd.execute();
    TEST_ASSERT(plant->getNutrients() > nutrientsBefore, "FertilizeCommand executes");
    
    delete gh;
    delete inv;
}

// --- Customer Tests ---
void test_Customer_Types() {
    TEST_SECTION("Customer Types");
    
    Plant* requestedPlant = new Lettuce(nullptr);
    
    RegularFactory regularFactory;
    Customer* regular = regularFactory.create(requestedPlant);
    TEST_ASSERT(regular->type() == "Regular", "RegularFactory creates Regular customer");
    delete regular;
    
    VIPFactory vipFactory;
    Customer* vip = vipFactory.create(requestedPlant);
    TEST_ASSERT(vip->type() == "VIP", "VIPFactory creates VIP customer");
    delete vip;
    
    RobberFactory robberFactory;
    Customer* robber = robberFactory.create(requestedPlant);
    TEST_ASSERT(robber->type() == "Robber", "RobberFactory creates Robber customer");
    delete robber;
    
    delete requestedPlant;
}

void test_Customer_RequestedPlant() {
    TEST_SECTION("Customer Requested Plant");
    
    Plant* plant1 = new Tomato(nullptr);
    Plant* plant2 = new Lettuce(nullptr);
    
    RegularFactory factory;
    Customer* customer = factory.create(plant1);
    
    TEST_ASSERT(customer->getRequestedPlant() == plant1, "Customer has correct requested plant");
    
    customer->setRequestedPlant(plant2);
    TEST_ASSERT(customer->getRequestedPlant() == plant2, "Can change requested plant");
    
    delete customer;
    delete plant1;
    delete plant2;
}

// --- Store Tests ---
void test_Store_AddItems() {
    TEST_SECTION("Store Add Items");
    
    Store* store = new Store();
    
    store->addItem(new SeedAdapter(15.0f, []() { return new Lettuce(nullptr); }));
    TEST_ASSERT(store->getItemCount() == 1, "Store has 1 item after adding");
    
    store->addItem(new SeedAdapter(25.0f, []() { return new Carrot(nullptr); }));
    TEST_ASSERT(store->getItemCount() == 2, "Store has 2 items after adding");
    
    delete store;
}

void test_Store_Purchase() {
    TEST_SECTION("Store Purchase");
    
    Store* store = new Store();
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    player->setMoney(100.0f);
    
    store->addItem(new SeedAdapter(15.0f, []() { return new Lettuce(nullptr); }));
    
    int invCountBefore = player->getInventory()->getPlantCount("Lettuce");
    float moneyBefore = player->getMoney();
    
    bool purchased = store->purchaseItem(0, player);
    
    TEST_ASSERT(purchased, "Purchase succeeds with sufficient funds");
    TEST_ASSERT(player->getMoney() < moneyBefore, "Money decreases after purchase");
    TEST_ASSERT(player->getInventory()->getPlantCount("Lettuce") > invCountBefore, "Plant added to inventory");
    
    delete store;
}

// --- Memento Tests ---
void test_Memento_SaveRestore() {
    TEST_SECTION("Memento Save/Restore");
    
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    // Set initial state
    player->setMoney(1000.0f);
    player->setRating(4.0f);
    player->setTime(5, 12, 30);
    
    // Save
    game->saveGame();
    
    // Modify state
    player->setMoney(5000.0f);
    player->setRating(1.0f);
    player->setTime(10, 18, 45);
    
    // Load
    game->loadGame();
    
    TEST_ASSERT(player->getMoney() == 1000.0f, "Money restored correctly");
    TEST_ASSERT(player->getRating() == 4, "Rating restored correctly");
    TEST_ASSERT(player->getDay() == 5, "Day restored correctly");
    TEST_ASSERT(player->getHour() == 12, "Hour restored correctly");
    TEST_ASSERT(player->getMinute() == 30, "Minute restored correctly");
}

// --- Player Tests ---
void test_Player_MoneyManagement() {
    TEST_SECTION("Player Money Management");
    
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    player->setMoney(100.0f);
    TEST_ASSERT(player->getMoney() == 100.0f, "Set money works");
    
    player->addMoney(50.0f);
    TEST_ASSERT(player->getMoney() == 150.0f, "Add money works");
    
    player->subtractMoney(30.0f);
    TEST_ASSERT(player->getMoney() == 120.0f, "Subtract money works");
    
    player->subtractMoney(200.0f);
    TEST_ASSERT(player->getMoney() == 0.0f, "Money cannot go negative");
}

void test_Player_TimeSystem() {
    TEST_SECTION("Player Time System");
    
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    player->setTime(1, 10, 30);
    TEST_ASSERT(player->getDay() == 1, "Day set correctly");
    TEST_ASSERT(player->getHour() == 10, "Hour set correctly");
    TEST_ASSERT(player->getMinute() == 30, "Minute set correctly");
    
    player->advanceTime(45);
    TEST_ASSERT(player->getHour() == 11, "Hour advances correctly");
    TEST_ASSERT(player->getMinute() == 15, "Minute advances correctly");
    
    player->advanceTime(1000);
    TEST_ASSERT(player->getDay() == 1, "Day advances after 1440 minutes");
}

void test_Player_RatingSystem() {
    TEST_SECTION("Player Rating System");
    
    Game* game = Game::getInstance();
    Player* player = game->getPlayerPtr();
    
    player->setRating(3.0f);
    TEST_ASSERT(player->getRating() == 3.0f, "Set rating works");
    
    player->addRating(1.5f);
    TEST_ASSERT(player->getRating() == 4.5f, "Add rating works");
    
    player->addRating(2.0f);
    TEST_ASSERT(player->getRating() == 5.0f, "Rating caps at 5");
    
    player->subtractRating(2.0f);
    TEST_ASSERT(player->getRating() == 3.0f, "Subtract rating works");
    
    player->subtractRating(5.0f);
    TEST_ASSERT(player->getRating() == 0.0f, "Rating cannot go negative");
}

// --- Game Singleton Tests ---
void test_Game_Singleton() {
    TEST_SECTION("Game Singleton Pattern");
    
    Game* game1 = Game::getInstance();
    Game* game2 = Game::getInstance();
    
    TEST_ASSERT(game1 == game2, "Singleton returns same instance");
    TEST_ASSERT(game1 != nullptr, "Singleton instance is not null");
}

// ============================================================================
// MAIN TEST RUNNER
// ============================================================================

int main() {
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║         TEMPLANTER - BACKEND UNIT TEST SUITE              ║" << endl;
    cout << "║                  Comprehensive Testing                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    try {
        // PlantState Tests
        test_PlantState_Initialization();
        test_PlantState_ResourceManagement();
        test_PlantState_GrowthApplication();
        
        // Plant Tests
        test_Plant_Creation();
        test_Plant_WateringAndFertilizing();
        test_Plant_StateTransitions();
        test_Plant_Death();
        
        // GrowthCycle Tests
        test_GrowthCycle_Normal();
        test_GrowthCycle_Boosted();
        
        // Inventory Tests
        test_Inventory_AddRemove();
        test_Inventory_Stacking();
        test_Inventory_FullCheck();
        
        // Greenhouse Tests
        test_Greenhouse_AddRemovePlants();
        test_Greenhouse_Harvesting();
        test_Greenhouse_TickAllPlants();
        
        // Worker Tests
        test_Worker_Creation();
        test_Worker_Commands();
        
        // Command Tests
        test_Commands_Execution();
        
        // Customer Tests
        test_Customer_Types();
        test_Customer_RequestedPlant();
        
        // Store Tests
        test_Store_AddItems();
        test_Store_Purchase();
        
        // Memento Tests
        test_Memento_SaveRestore();
        
        // Player Tests
        test_Player_MoneyManagement();
        test_Player_TimeSystem();
        test_Player_RatingSystem();
        
        // Game Singleton Tests
        test_Game_Singleton();
        
    } catch (const exception& e) {
        cerr << "\n[EXCEPTION] " << e.what() << endl;
        return 1;
    }
    
    // Print summary
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                      TEST SUMMARY                          ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  Total Tests:   " << tests_total << endl;
    cout << "║  Passed:        " << tests_passed << " (" 
         << (tests_total > 0 ? (tests_passed * 100 / tests_total) : 0) << "%)" << endl;
    cout << "║  Failed:        " << tests_failed << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    // Cleanup
    cout << "\n--- Cleaning up resources ---" << endl;
    Game::cleanup();
    cleanupPlantCatalog();
    cout << "Cleanup completed" << endl;
    
    return (tests_failed == 0) ? 0 : 1;
}