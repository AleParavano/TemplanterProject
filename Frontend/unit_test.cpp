#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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

// Forward declaration for cleanup
//extern void cleanupPlantCatalog();

// =============================================================================
// PLANTSTATE TESTS
// =============================================================================

TEST_CASE("PlantState - Initialization") {
    SUBCASE("Seed state initialization") {
        SeedState seed(0.0f, 100.0f, 100.0f);
        CHECK(seed.getGrowth() == 0.0f);
        CHECK(seed.getWater() == 100.0f);
        CHECK(seed.getNutrients() == 100.0f);
        CHECK(seed.getState() == "Seed");
    }

    SUBCASE("Growing state initialization") {
        GrowingState growing(50.0f, 80.0f, 70.0f);
        CHECK(growing.getGrowth() == 50.0f);
        CHECK(growing.getState() == "Growing");
    }

    SUBCASE("Ripe state initialization") {
        RipeState ripe(100.0f, 60.0f, 50.0f);
        CHECK(ripe.getGrowth() == 100.0f);
        CHECK(ripe.getState() == "Ripe");
    }

    SUBCASE("Dead state initialization") {
        DeadState dead(25.0f, 0.0f, 0.0f);
        CHECK(dead.getState() == "Dead");
    }
}

TEST_CASE("PlantState - Resource Management") {
    SeedState state(10.0f, 50.0f, 60.0f);

    SUBCASE("Adding water") {
        state.addWater(30.0f);
        CHECK(state.getWater() == 80.0f);
    }

    SUBCASE("Water caps at 100%") {
        state.addWater(30.0f);
        state.addWater(50.0f);
        CHECK(state.getWater() == 100.0f);
    }

    SUBCASE("Adding nutrients") {
        state.addNutrients(20.0f);
        CHECK(state.getNutrients() == 80.0f);
    }

    SUBCASE("Consuming resources") {
        state.addWater(50.0f);
        state.addNutrients(40.0f);
        state.consumeResources(30.0f, 20.0f);
        CHECK(state.getWater() == 70.0f);
        CHECK(state.getNutrients() == 80.0f);
    }
}

TEST_CASE("PlantState - Growth Application") {
    SeedState state(20.0f, 100.0f, 100.0f);

    SUBCASE("Growth increases correctly") {
        state.applyGrowth(15.0f);
        CHECK(state.getGrowth() == 35.0f);
    }

    SUBCASE("Growth caps at 100%") {
        state.applyGrowth(15.0f);
        state.applyGrowth(100.0f);
        CHECK(state.getGrowth() == 100.0f);
    }
}

// =============================================================================
// PLANT TESTS
// =============================================================================

TEST_CASE("Plant - Creation") {
    SUBCASE("Lettuce creation") {
        Plant *lettuce = new Lettuce(nullptr);
        REQUIRE(lettuce != nullptr);
        CHECK(lettuce->getType() == "Lettuce");
        CHECK(lettuce->getStateName() == "Seed");
        CHECK(lettuce->getGrowth() == 0.0f);
        CHECK_FALSE(lettuce->isRipe());
        CHECK_FALSE(lettuce->isDead());
        delete lettuce;
    }

    SUBCASE("Tomato creation") {
        Plant *tomato = new Tomato(nullptr);
        CHECK(tomato->getType() == "Tomato");
        CHECK(tomato->getSellPrice() == 55.0f);
        delete tomato;
    }
}

TEST_CASE("Plant - Watering and Fertilizing") {
    Plant *plant = new Carrot(nullptr);

    // Deplete resources
    for (int i = 0; i < 20; i++) {
        plant->tick();
    }

    SUBCASE("Watering increases water level") {
        float waterBefore = plant->getWater();
        plant->water(50.0f);
        CHECK(plant->getWater() > waterBefore);
    }

    SUBCASE("Fertilizing increases nutrients") {
        float nutrientsBefore = plant->getNutrients();
        plant->fertilize(50.0f);
        CHECK(plant->getNutrients() > nutrientsBefore);
    }

    delete plant;
}

TEST_CASE("Plant - State Transitions") {
    Plant *plant = new Lettuce(nullptr);

    SUBCASE("Transition to Growing state") {
        for (int i = 0; i < 15; i++) {
            plant->water(10.0f);
            plant->fertilize(10.0f);
            plant->tick();
        }
        CHECK(plant->getStateName() == "Growing");
    }

    SUBCASE("Transition to Ripe state") {
        for (int i = 0; i < 50; i++) {
            plant->water(10.0f);
            plant->fertilize(10.0f);
            plant->tick();
        }
        CHECK(plant->isRipe());
    }

    delete plant;
}

TEST_CASE("Plant - Death from Neglect") {
    Plant *plant = new Tomato(nullptr);

    for (int i = 0; i < 100; i++) {
        plant->tick();
        if (plant->isDead()) {
            break;
        }
    }

    CHECK(plant->isDead());
    delete plant;
}

// =============================================================================
// GROWTHCYCLE TESTS
// =============================================================================

TEST_CASE("GrowthCycle - Normal") {
    Plant *plant = new Lettuce(nullptr);
    NormalGrowthCycle *normalCycle = new NormalGrowthCycle();
    plant->setGrowthCycle(normalCycle);

    float growthBefore = plant->getGrowth();
    plant->tick();
    float growthAfter = plant->getGrowth();

    CHECK(growthAfter > growthBefore);
    delete plant;
}

TEST_CASE("GrowthCycle - Boosted") {
    Plant *plant1 = new Lettuce(nullptr);
    Plant *plant2 = new Lettuce(nullptr);

    BoostedGrowthCycle *boostedCycle = new BoostedGrowthCycle();
    plant2->setGrowthCycle(boostedCycle);

    for (int i = 0; i < 5; i++) {
        plant1->tick();
        plant2->tick();
    }

    CHECK(plant2->getGrowth() > plant1->getGrowth());

    delete plant1;
    delete plant2;
}

// =============================================================================
// INVENTORY TESTS
// =============================================================================

TEST_CASE("Inventory - Add and Remove") {
    Inventory *inv = new Inventory(10);

    SUBCASE("Initial capacity") {
        CHECK(inv->getMaxSlots() == 10);
    }

    SUBCASE("Adding plants") {
        Plant *plant1 = new Lettuce(nullptr);
        CHECK(inv->add(plant1));
        CHECK(inv->getPlantCount("Lettuce") == 1);

        Plant *plant2 = new Lettuce(nullptr);
        CHECK(inv->add(plant2));
        CHECK(inv->getPlantCount("Lettuce") == 2);
    }

    SUBCASE("Removing plants") {
        Plant *plant = new Lettuce(nullptr);
        inv->add(plant);
        
        Plant *removed = inv->removeItem("Lettuce");
        REQUIRE(removed != nullptr);
        CHECK(removed->getType() == "Lettuce");
        CHECK(inv->getPlantCount("Lettuce") == 0);
        delete removed;
    }

    delete inv;
}

TEST_CASE("Inventory - Stacking") {
    Inventory *inv = new Inventory(5);

    for (int i = 0; i < 10; i++) {
        Plant *plant = new Tomato(nullptr);
        inv->add(plant);
    }

    CHECK(inv->getPlantCount("Tomato") == 10);
    CHECK(inv->getStackCount() <= 5);

    delete inv;
}

TEST_CASE("Inventory - Full Check") {
    Inventory *inv = new Inventory(2);

    // Fill inventory (2 slots × 64 capacity = 128 items)
    for (int i = 0; i < 128; i++) {
        Plant *plant = new Lettuce(nullptr);
        if (!inv->add(plant)) {
            delete plant;
            break;
        }
    }

    CHECK(inv->isFull());

    Plant *extraPlant = new Lettuce(nullptr);
    CHECK_FALSE(inv->add(extraPlant));
    delete extraPlant;

    delete inv;
}

// =============================================================================
// GREENHOUSE TESTS
// =============================================================================

TEST_CASE("Greenhouse - Add and Remove Plants") {
    Inventory *inv = new Inventory(10);
    Greenhouse *gh = new Greenhouse(inv);

    SUBCASE("Initial state") {
        CHECK(gh->getCapacity() == 56);
        CHECK(gh->getSize() == 0);
    }

    SUBCASE("Adding plants") {
        Plant *plant = new Lettuce(nullptr);
        CHECK(gh->addPlant(plant, 0));
        CHECK(gh->getSize() == 1);
        CHECK(gh->getPlant(0) == plant);
    }

    SUBCASE("Removing plants") {
        Plant *plant = new Lettuce(nullptr);
        gh->addPlant(plant, 0);
        
        CHECK(gh->removePlant(0));
        CHECK(gh->getSize() == 0);
        CHECK(gh->getPlant(0) == nullptr);
    }

    delete gh;
    delete inv;
}

TEST_CASE("Greenhouse - Harvesting") {
    Inventory *inv = new Inventory(10);
    Greenhouse *gh = new Greenhouse(inv);

    Plant *plant = new Lettuce(nullptr);
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

    CHECK(invCountAfter == invCountBefore + 1);
    CHECK(gh->getSize() == 0);

    delete gh;
    delete inv;
}

TEST_CASE("Greenhouse - Tick All Plants") {
    Inventory *inv = new Inventory(10);
    Greenhouse *gh = new Greenhouse(inv);

    for (int i = 0; i < 5; i++) {
        Plant *plant = new Tomato(nullptr);
        gh->addPlant(plant);
    }

    gh->tickAllPlants();

    for (int i = 0; i < 5; i++) {
        Plant *plant = gh->getPlant(i);
        CHECK(plant->getWater() < 100.0f);
    }

    delete gh;
    delete inv;
}

// =============================================================================
// WORKER TESTS
// =============================================================================

TEST_CASE("Worker - Commands") {
    Inventory *inv = new Inventory(10);
    Greenhouse *gh = new Greenhouse(inv);

    Plant *plant = new Tomato(nullptr);
    gh->addPlant(plant, 0);

    // Deplete water
    for (int i = 0; i < 25; i++) {
        plant->tick();
    }

    float waterBefore = plant->getWater();

    WaterWorker *worker = new WaterWorker();
    gh->attach(worker);
    gh->notify();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    CHECK(plant->getWater() >= waterBefore);

    delete worker;
    delete gh;
    delete inv;
}

// =============================================================================
// COMMAND TESTS
// =============================================================================

TEST_CASE("Commands - Execution") {
    Inventory *inv = new Inventory(10);
    Greenhouse *gh = new Greenhouse(inv);

    Plant *plant = new Lettuce(nullptr);
    gh->addPlant(plant);

    SUBCASE("Water command") {
        float waterBefore = plant->getWater();
        WaterCommand waterCmd(plant, gh);
        waterCmd.execute();
        CHECK(plant->getWater() >= waterBefore);
    }

    delete gh;
    delete inv;
}

// =============================================================================
// CUSTOMER TESTS
// =============================================================================

TEST_CASE("Customer - Types") {
    Plant *requestedPlant = new Lettuce(nullptr);

    SUBCASE("Regular customer") {
        RegularFactory regularFactory;
        Customer *regular = regularFactory.create(requestedPlant);
        CHECK(regular->type() == "Regular");
        delete regular;
    }

    SUBCASE("VIP customer") {
        VIPFactory vipFactory;
        Customer *vip = vipFactory.create(requestedPlant);
        CHECK(vip->type() == "VIP");
        delete vip;
    }

    SUBCASE("Robber") {
        RobberFactory robberFactory;
        Customer *robber = robberFactory.create(requestedPlant);
        CHECK(robber->type() == "Robber");
        delete robber;
    }

    delete requestedPlant;
}

TEST_CASE("Customer - Requested Plant") {
    Plant *plant1 = new Tomato(nullptr);
    Plant *plant2 = new Lettuce(nullptr);

    RegularFactory factory;
    Customer *customer = factory.create(plant1);

    CHECK(customer->getRequestedPlant() == plant1);

    customer->setRequestedPlant(plant2);
    CHECK(customer->getRequestedPlant() == plant2);

    delete customer;
    delete plant1;
    delete plant2;
}

// =============================================================================
// STORE TESTS
// =============================================================================

TEST_CASE("Store - Add Items") {
    Store *store = new Store();

    store->addItem(new SeedAdapter(15.0f, []() { 
        return new Lettuce(nullptr); 
    }));
    CHECK(store->getItemCount() == 1);

    store->addItem(new SeedAdapter(25.0f, []() { 
        return new Carrot(nullptr); 
    }));
    CHECK(store->getItemCount() == 2);

    delete store;
}

TEST_CASE("Store - Purchase") {
    Store *store = new Store();
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    player->setMoney(100.0f);

    store->addItem(new SeedAdapter(15.0f, []() { 
        return new Lettuce(nullptr); 
    }));

    int invCountBefore = player->getInventory()->getPlantCount("Lettuce");
    float moneyBefore = player->getMoney();

    bool purchased = store->purchaseItem(0, player);

    CHECK(purchased);
    CHECK(player->getMoney() < moneyBefore);
    CHECK(player->getInventory()->getPlantCount("Lettuce") > invCountBefore);

    delete store;
}

// =============================================================================
// MEMENTO TESTS
// =============================================================================

TEST_CASE("Memento - Save and Restore") {
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

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

    CHECK(player->getMoney() == 1000.0f);
    CHECK(player->getRating() == 4);
    CHECK(player->getDay() == 5);
    CHECK(player->getHour() == 12);
    CHECK(player->getMinute() == 30);
}

// =============================================================================
// PLAYER TESTS
// =============================================================================

TEST_CASE("Player - Money Management") {
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    SUBCASE("Set money") {
        player->setMoney(100.0f);
        CHECK(player->getMoney() == 100.0f);
    }

    SUBCASE("Add money") {
        player->setMoney(100.0f);
        player->addMoney(50.0f);
        CHECK(player->getMoney() == 150.0f);
    }

    SUBCASE("Subtract money") {
        player->setMoney(150.0f);
        player->subtractMoney(30.0f);
        CHECK(player->getMoney() == 120.0f);
    }

    SUBCASE("Money cannot go negative") {
        player->setMoney(100.0f);
        player->subtractMoney(200.0f);
        CHECK(player->getMoney() == 0.0f);
    }
}

TEST_CASE("Player - Time System") {
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    SUBCASE("Set time") {
        player->setTime(1, 10, 30);
        CHECK(player->getDay() == 1);
        CHECK(player->getHour() == 10);
        CHECK(player->getMinute() == 30);
    }

    SUBCASE("Advance time") {
        player->setTime(1, 10, 30);
        player->advanceTime(45);
        CHECK(player->getHour() == 11);
        CHECK(player->getMinute() == 15);
    }
}

TEST_CASE("Player - Rating System") {
    Game *game = Game::getInstance();
    Player *player = game->getPlayerPtr();

    SUBCASE("Set rating") {
        player->setRating(3.0f);
        CHECK(player->getRating() == 3.0f);
    }

    SUBCASE("Add rating") {
        player->setRating(3.0f);
        player->addRating(1.5f);
        CHECK(player->getRating() == 4.5f);
    }

    SUBCASE("Rating caps at 5") {
        player->setRating(4.5f);
        player->addRating(2.0f);
        CHECK(player->getRating() == 5.0f);
    }

    SUBCASE("Subtract rating") {
        player->setRating(5.0f);
        player->subtractRating(2.0f);
        CHECK(player->getRating() == 3.0f);
    }

    SUBCASE("Rating cannot go negative") {
        player->setRating(2.0f);
        player->subtractRating(5.0f);
        CHECK(player->getRating() == 0.0f);
    }
}

// =============================================================================
// GAME TESTS
// =============================================================================

TEST_CASE("Game - Singleton Pattern") {
    Game *game1 = Game::getInstance();
    Game *game2 = Game::getInstance();

    CHECK(game1 == game2);
    REQUIRE(game1 != nullptr);
}

// =============================================================================
// CLEANUP
// =============================================================================

struct GlobalCleanup {
    ~GlobalCleanup() {
        Game::cleanup();
        // cleanupPlantCatalog();
    }
};

GlobalCleanup g_cleanup;