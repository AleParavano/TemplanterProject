#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// Backend includes only - NO RAYLIB
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
#include "GreenHouseScene.h"


using namespace std;

// TEST UTILITIES

void printTestHeader(const string &testName)
{
    cout << "TEST: " << testName << endl;
}

void printTestResult(bool passed)
{
    if (passed)
    {
        cout << "[PASS] Test completed successfully" << endl;
    }
    else
    {
        cout << "[FAIL] Test failed" << endl;
    }
}

// TEST 1: Game Singleton & Player Creation
void test_game_singleton()
{
    printTestHeader("Game Singleton & Player");

    Game *game1 = Game::getInstance();
    Game *game2 = Game::getInstance();

    cout << "Game instance 1: " << game1 << endl;
    cout << "Game instance 2: " << game2 << endl;
    cout << "Singleton check: " << (game1 == game2 ? "PASS" : "FAIL") << endl;

    Player &player = game1->getPlayer();
    cout << "Player initial money: $" << player.getMoney() << endl;
    cout << "Player initial rating: " << player.getRating() << endl;
    cout << "Player day: " << player.getDay() << endl;
    cout << "Player time: " << player.getHour() << ":" << player.getMinute() << endl;

    printTestResult(game1 == game2);
}

// TEST 2: Plant Creation & State Transitions
void test_plant_lifecycle()
{
    printTestHeader("Plant Lifecycle & State Transitions");

    // Create a plant without visual strategy (nullptr for testing)
    Plant *lettuce = new Lettuce(nullptr);

    cout << "Plant type: " << lettuce->getType() << endl;
    cout << "Initial state: " << lettuce->getStateName() << endl;
    cout << "Initial growth: " << lettuce->getGrowth() << "%" << endl;
    cout << "Initial water: " << lettuce->getWater() << "%" << endl;
    cout << "Initial nutrients: " << lettuce->getNutrients() << "%" << endl;

    // Test watering
    cout << "\n--- Testing Water Command ---" << endl;
    lettuce->water(30.0f);
    cout << "After watering: " << lettuce->getWater() << "%" << endl;

    // Test fertilizing
    cout << "\n--- Testing Fertilize Command ---" << endl;
    lettuce->fertilize(20.0f);
    cout << "After fertilizing: " << lettuce->getNutrients() << "%" << endl;

    // Simulate growth
    cout << "\n--- Simulating Growth (10 ticks) ---" << endl;
    for (int i = 0; i < 10; i++)
    {
        lettuce->tick();
        if (i % 3 == 0)
        {
            cout << "Tick " << i << ": State=" << lettuce->getStateName()
                 << ", Growth=" << lettuce->getGrowth() << "%"
                 << ", Water=" << lettuce->getWater() << "%"
                 << ", Nutrients=" << lettuce->getNutrients() << "%" << endl;
        }
    }

    cout << "\nFinal state: " << lettuce->getStateName() << endl;
    cout << "Is ripe: " << (lettuce->isRipe() ? "YES" : "NO") << endl;
    cout << "Is dead: " << (lettuce->isDead() ? "YES" : "NO") << endl;

    delete lettuce;
    printTestResult(true);
}

// TEST 3: Inventory Management
void test_inventory_system()
{
    printTestHeader("Inventory Management System");

    Inventory *inv = new Inventory(10);
    cout << "Created inventory with capacity: " << inv->getMaxSlots() << endl;

    // Add multiple plants
    cout << "\n--- Adding Plants ---" << endl;
    for (int i = 0; i < 5; i++)
    {
        Plant *plant = new Tomato(nullptr);
        if (inv->add(plant))
        {
            cout << "Added Tomato #" << (i + 1) << endl;
        }
        else
        {
            cout << "Failed to add Tomato #" << (i + 1) << endl;
            delete plant;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        Plant *plant = new Carrot(nullptr);
        if (inv->add(plant))
        {
            cout << "Added Carrot #" << (i + 1) << endl;
        }
        else
        {
            cout << "Failed to add Carrot #" << (i + 1) << endl;
            delete plant;
        }
    }

    // Check inventory contents
    cout << "\n--- Inventory Status ---" << endl;
    cout << "Total stacks: " << inv->getStackCount() << endl;
    cout << "Tomato count: " << inv->getPlantCount("Tomato") << endl;
    cout << "Carrot count: " << inv->getPlantCount("Carrot") << endl;
    cout << "Is full: " << (inv->isFull() ? "YES" : "NO") << endl;

    // Remove items
    cout << "\n--- Removing Items ---" << endl;
    Plant *removed = inv->removeItem("Tomato");
    if (removed)
    {
        cout << "Removed: " << removed->getType() << endl;
        delete removed;
    }

    cout << "Tomato count after removal: " << inv->getPlantCount("Tomato") << endl;

    delete inv;
    printTestResult(true);
}

// TEST 4: Greenhouse Management
void test_greenhouse()
{
    printTestHeader("Greenhouse Management");

    Inventory *inv = new Inventory(20);
    Greenhouse *greenhouse = new Greenhouse(inv);

    cout << "Greenhouse capacity: " << greenhouse->getCapacity() << endl;
    cout << "Initial size: " << greenhouse->getSize() << endl;

    // Add plants to greenhouse
    cout << "\n--- Planting Seeds ---" << endl;
    for (int i = 0; i < 5; i++)
    {
        Plant *plant = new Lettuce(nullptr);
        if (greenhouse->addPlant(plant))
        {
            cout << "Planted Lettuce at position " << i << endl;
        }
        else
        {
            cout << "Failed to plant at position " << i << endl;
            delete plant;
        }
    }

    cout << "Greenhouse size after planting: " << greenhouse->getSize() << endl;

    // Tick all plants
    cout << "\n--- Simulating Time (5 ticks) ---" << endl;
    for (int tick = 0; tick < 5; tick++)
    {
        greenhouse->tickAllPlants();
        cout << "Tick " << tick << " completed" << endl;
    }

    // Check plant at position 0
    Plant *plant = greenhouse->getPlant(0);
    if (plant)
    {
        cout << "\nPlant at position 0:" << endl;
        cout << "  Type: " << plant->getType() << endl;
        cout << "  State: " << plant->getStateName() << endl;
        cout << "  Growth: " << plant->getGrowth() << "%" << endl;
    }

    // Test harvesting
    cout << "\n--- Testing Harvest ---" << endl;
    int initialInvCount = inv->getPlantCount("Lettuce");
    greenhouse->harvestPlant(0);
    int afterInvCount = inv->getPlantCount("Lettuce");

    cout << "Inventory before harvest: " << initialInvCount << endl;
    cout << "Inventory after harvest: " << afterInvCount << endl;
    cout << "Greenhouse size after harvest: " << greenhouse->getSize() << endl;

    delete greenhouse;
    delete inv;
    printTestResult(true);
}

// TEST 5: Worker System with Commands
void test_worker_system()
{
    printTestHeader("Worker System with Commands");

    Inventory *inv = new Inventory(20);
    Greenhouse *greenhouse = new Greenhouse(inv);

    // Plant some seeds
    for (int i = 0; i < 3; i++)
    {
        Plant *plant = new Tomato(nullptr);
        greenhouse->addPlant(plant);
    }

    // Create workers
    cout << "--- Creating Workers ---" << endl;
    WaterWorker *waterWorker = new WaterWorker();
    FertiliserWorker *fertWorker = new FertiliserWorker();
    HarvestWorker *harvestWorker = new HarvestWorker();

    // Attach workers to greenhouse
    greenhouse->attach(waterWorker);
    greenhouse->attach(fertWorker);
    greenhouse->attach(harvestWorker);

    cout << "\n--- Workers attached to greenhouse ---" << endl;

    // Manually trigger updates (simulate low resources)
    cout << "\n--- Simulating Plant Care ---" << endl;

    // Deplete resources
    for (int i = 0; i < 3; i++)
    {
        Plant *plant = greenhouse->getPlant(i);
        if (plant)
        {
            // Reduce water below threshold
            for (int j = 0; j < 10; j++)
            {
                plant->tick();
            }
            cout << "Plant " << i << " - Water: " << plant->getWater()
                 << "%, Nutrients: " << plant->getNutrients() << "%" << endl;
        }
    }

    // Trigger worker update
    cout << "\n--- Notifying Workers ---" << endl;
    greenhouse->notify();

    // Give workers time to process
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    cout << "Workers have been notified to perform tasks" << endl;

    // Cleanup - workers will stop their threads
    cout << "\n--- Cleaning up workers ---" << endl;
    delete waterWorker;
    delete fertWorker;
    delete harvestWorker;

    delete greenhouse;
    delete inv;
    printTestResult(true);
}

// TEST 6: Customer System
void test_customer_system()
{
    printTestHeader("Customer Factory & Types");

    // Create factories
    RegularFactory regularFactory;
    VIPFactory vipFactory;
    RobberFactory robberFactory;
    RandomFactory randomFactory;

    // Create a dummy plant for requests
    Plant *requestedPlant = new Lettuce(nullptr);

    cout << "--- Creating Customers ---" << endl;

    Customer *regular = regularFactory.create(requestedPlant);
    cout << "Regular customer type: " << regular->type() << endl;

    Customer *vip = vipFactory.create(requestedPlant);
    cout << "VIP customer type: " << vip->type() << endl;

    Customer *robber = robberFactory.create(requestedPlant);
    cout << "Robber customer type: " << robber->type() << endl;

    cout << "\n--- Creating Random Customers ---" << endl;
    for (int i = 0; i < 10; i++)
    {
        Customer *randomCust = randomFactory.create(requestedPlant);
        cout << "Random customer " << i << ": " << randomCust->type() << endl;
        delete randomCust;
    }

    delete regular;
    delete vip;
    delete robber;
    delete requestedPlant;

    printTestResult(true);
}

// TEST 7: Store System with Seed Adapter
void test_store_system()
{
    printTestHeader("Store System with Seed Adapter");

    Store *store = new Store();
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    // Give player some money
    player->setMoney(500.0f);
    cout << "Player starting money: $" << player->getMoney() << endl;

    // Add seed items to store
    cout << "\n--- Adding Seeds to Store ---" << endl;

    store->addItem(new SeedAdapter(15.0f, []() -> Plant *
                                   { return new Lettuce(nullptr); }));
    cout << "Added Lettuce seeds ($15.00)" << endl;

    store->addItem(new SeedAdapter(25.0f, []() -> Plant *
                                   { return new Carrot(nullptr); }));
    cout << "Added Carrot seeds ($25.00)" << endl;

    store->addItem(new SeedAdapter(55.0f, []() -> Plant *
                                   { return new Tomato(nullptr); }));
    cout << "Added Tomato seeds ($55.00)" << endl;

    cout << "Total items in store: " << store->getItemCount() << endl;

    // Purchase items
    cout << "\n--- Purchasing Seeds ---" << endl;
    for (size_t i = 0; i < store->getItemCount(); i++)
    {
        StoreItem *item = store->getItem(i);
        cout << "Item " << i << " price: $" << item->getPrice() << endl;

        if (store->purchaseItem(i, player))
        {
            cout << "Purchase successful!" << endl;
        }
        else
        {
            cout << "Purchase failed!" << endl;
        }
        cout << "Player money after purchase: $" << player->getMoney() << endl;
    }

    cout << "\nPlayer inventory count:" << endl;
    cout << "Lettuce: " << player->getInventory()->getPlantCount("Lettuce") << endl;
    cout << "Carrot: " << player->getInventory()->getPlantCount("Carrot") << endl;
    cout << "Tomato: " << player->getInventory()->getPlantCount("Tomato") << endl;

    delete store;
    printTestResult(true);
}

// TEST 8: Save/Load System (Memento Pattern)
void test_save_load_system()
{
    printTestHeader("Save/Load System (Memento Pattern)");

    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    // Setup initial state
    cout << "--- Setting up initial game state ---" << endl;
    player->setMoney(1000.0f);
    player->setRating(3.5f);
    player->setTime(5, 14, 30);

    // Add some plants to inventory
    for (int i = 0; i < 3; i++)
    {
        player->getInventory()->add(new Lettuce(nullptr));
    }

    // Add plants to greenhouse
    for (int i = 0; i < 2; i++)
    {
        player->getPlot()->addPlant(new Tomato(nullptr));
    }

    cout << "Initial state:" << endl;
    cout << "  Money: $" << player->getMoney() << endl;
    cout << "  Rating: " << player->getRating() << endl;
    cout << "  Day: " << player->getDay() << endl;
    cout << "  Time: " << player->getHour() << ":" << player->getMinute() << endl;
    cout << "  Lettuce in inventory: " << player->getInventory()->getPlantCount("Lettuce") << endl;
    cout << "  Plants in greenhouse: " << player->getPlot()->getSize() << endl;

    // Save game
    cout << "\n--- Saving game ---" << endl;
    game->saveGame();
    cout << "Game saved successfully" << endl;

    // Modify state
    cout << "\n--- Modifying game state ---" << endl;
    player->setMoney(5000.0f);
    player->setRating(5.0f);
    player->setTime(10, 18, 45);
    player->getInventory()->clear();

    cout << "Modified state:" << endl;
    cout << "  Money: $" << player->getMoney() << endl;
    cout << "  Rating: " << player->getRating() << endl;
    cout << "  Day: " << player->getDay() << endl;
    cout << "  Time: " << player->getHour() << ":" << player->getMinute() << endl;
    cout << "  Lettuce in inventory: " << player->getInventory()->getPlantCount("Lettuce") << endl;

    // Load game
    cout << "\n--- Loading saved game ---" << endl;
    game->loadGame();
    cout << "Game loaded successfully" << endl;

    cout << "Restored state:" << endl;
    cout << "  Money: $" << player->getMoney() << endl;
    cout << "  Rating: " << player->getRating() << endl;
    cout << "  Day: " << player->getDay() << endl;
    cout << "  Time: " << player->getHour() << ":" << player->getMinute() << endl;
    cout << "  Lettuce in inventory: " << player->getInventory()->getPlantCount("Lettuce") << endl;
    cout << "  Plants in greenhouse: " << player->getPlot()->getSize() << endl;

    printTestResult(true);
}

// TEST 9: Plant State Transitions (Seed -> Growing -> Ripe -> Dead)
void test_plant_state_transitions()
{
    printTestHeader("Plant State Transitions");

    Plant *plant = new Lettuce(nullptr);

    cout << "Starting state: " << plant->getStateName() << endl;

    // Grow from Seed to Growing
    cout << "\n--- Growing from Seed ---" << endl;
    for (int i = 0; i < 20; i++)
    {
        plant->tick();
        if (plant->getStateName() == "Growing")
        {
            cout << "State changed to Growing at tick " << i << endl;
            break;
        }
    }

    // Keep watering and fertilizing to sustain growth
    cout << "\n--- Sustaining growth to Ripe ---" << endl;
    for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 0)
        {
            plant->water(50.0f);
            plant->fertilize(50.0f);
        }
        plant->tick();

        if (plant->getStateName() == "Ripe")
        {
            cout << "State changed to Ripe at tick " << i << endl;
            cout << "Growth level: " << plant->getGrowth() << "%" << endl;
            break;
        }
    }

    // Test death from lack of resources
    cout << "\n--- Testing death from neglect ---" << endl;
    Plant *dyingPlant = new Tomato(nullptr);
    for (int i = 0; i < 200; i++)
    {
        dyingPlant->tick();
        if (dyingPlant->isDead())
        {
            cout << "Plant died at tick " << i << endl;
            cout << "Final water: " << dyingPlant->getWater() << "%" << endl;
            cout << "Final nutrients: " << dyingPlant->getNutrients() << "%" << endl;
            break;
        }
    }

    delete plant;
    delete dyingPlant;
    printTestResult(true);
}

// TEST 10: Time System
void test_time_system()
{
    printTestHeader("Time System");

    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    player->setTime(1, 6, 0);
    cout << "Initial time: Day " << player->getDay()
         << ", " << player->getHour() << ":" << player->getMinute() << endl;

    // Advance time
    cout << "\n--- Advancing time ---" << endl;
    player->advanceTime(30); // 30 minutes
    cout << "After 30 minutes: " << player->getHour() << ":" << player->getMinute() << endl;

    player->advanceTime(45); // 45 more minutes
    cout << "After 45 more minutes: " << player->getHour() << ":" << player->getMinute() << endl;

    player->advanceTime(1000); // Advance significantly
    cout << "After 1000 minutes: Day " << player->getDay()
         << ", " << player->getHour() << ":" << player->getMinute() << endl;

    printTestResult(true);
}

// m ain function
int main()
{
    cout << "TEMPLANTER - MEMORY LEAK TESTING SUITE" << endl;
    cout << "Backend Systems Only (No Raylib)" << endl;

    try
    {
        test_game_singleton();
        test_plant_lifecycle();
        test_inventory_system();
        test_greenhouse();
        test_worker_system();
        test_customer_system();
        test_store_system();
        test_save_load_system();
        test_plant_state_transitions();
        test_time_system();

        cout << "ALL TESTS COMPLETED" << endl;

        // ADD THIS CLEANUP CODE
        cout << "\n--- Cleaning up singleton and global resources ---" << endl;
        Game::cleanup();
        cleanupPlantCatalog();
        cout << "Cleanup completed" << endl;

        cout << "Run with Valgrind:" << endl;
        cout << "  valgrind --leak-check=full --show-leak-kinds=all \\" << endl;
        cout << "           --track-origins=yes --verbose \\" << endl;
        cout << "           --log-file=valgrind-out.txt ./test_main" << endl;
    }
    catch (const exception &e)
    {
        cerr << "\n[EXCEPTION] " << e.what() << endl;
        return 1;
    }

    return 0;
}