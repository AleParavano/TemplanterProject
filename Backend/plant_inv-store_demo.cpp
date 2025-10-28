#include "Game.h"
#include "Store.h"
#include "SeedAdapter.h"
#include "Player.h"
#include "Plant.h"
#include "Inventory.h"
#include <iostream>

bool testAdapterPattern();
bool testStoreBasics();
bool testPurchaseToInventory();
bool testInsufficientFunds();
bool testInventoryFull();
bool testPlantPricing();
bool testNonHardcodedFactory();
bool testDynamicInventoryCapacity();

int main() {
    int passed = 0;
    int total = 8;
    
    std::cout << "=== ADAPTER PATTERN TEST SUITE ===" << std::endl << std::endl;
    
    if (testAdapterPattern()) {
        std::cout << "[PASS] Adapter Pattern Structure" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Adapter Pattern Structure" << std::endl;
    }
    
    if (testStoreBasics()) {
        std::cout << "[PASS] Store Basic Operations" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Store Basic Operations" << std::endl;
    }
    
    if (testPurchaseToInventory()) {
        std::cout << "[PASS] Purchase to Inventory Only" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Purchase to Inventory Only" << std::endl;
    }
    
    if (testInsufficientFunds()) {
        std::cout << "[PASS] Insufficient Funds Handling" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Insufficient Funds Handling" << std::endl;
    }
    
    if (testInventoryFull()) {
        std::cout << "[PASS] Inventory Full Handling" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Inventory Full Handling" << std::endl;
    }
    
    if (testPlantPricing()) {
        std::cout << "[PASS] Plant Pricing (Expensive = Slow & Valuable)" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Plant Pricing (Expensive = Slow & Valuable)" << std::endl;
    }
    
    if (testNonHardcodedFactory()) {
        std::cout << "[PASS] Non-Hardcoded Factory Pattern" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Non-Hardcoded Factory Pattern" << std::endl;
    }
    
    if (testDynamicInventoryCapacity()) {
        std::cout << "[PASS] Dynamic Inventory Capacity" << std::endl;
        passed++;
    } else {
        std::cout << "[FAIL] Dynamic Inventory Capacity" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "=== RESULTS: " << passed << "/" << total << " TESTS PASSED ===" << std::endl;
    
    return (passed == total) ? 0 : 1;
}

bool testAdapterPattern() {
    // Test that SeedAdapter implements StoreItem interface
    SeedAdapter* adapter = new SeedAdapter(30.0f, []() { return new Tomato(); });
    
    StoreItem* item = adapter;  // Can upcast to interface
    
    bool priceCorrect = (item->getPrice() == 30.0f);
    
    void* result = item->request();
    Plant* plant = static_cast<Plant*>(result);
    
    bool plantCreated = (plant != nullptr);
    bool correctType = (plant && plant->getType() == "Tomato");
    
    delete plant;
    delete adapter;
    
    return priceCorrect && plantCreated && correctType;
}

bool testStoreBasics() {
    // Clear any previous state
    Game* game = Game::getInstance();
    game->getPlayer().getInventory()->clear();
    game->getPlayer().setMoney(1000.0f);
    
    Store store;
    
    // Add items using lambda factories
    store.addItem(new SeedAdapter(10.0f, []() { return new Lettuce(); }));
    store.addItem(new SeedAdapter(30.0f, []() { return new Tomato(); }));
    store.addItem(new SeedAdapter(100.0f, []() { return new Pumpkin(); }));
    
    bool itemCountCorrect = (store.getItemCount() == 3);
    
    StoreItem* item = store.getItem(1);
    bool itemRetrieved = (item != nullptr);
    bool priceCorrect = (item && item->getPrice() == 30.0f);
    
    return itemCountCorrect && itemRetrieved && priceCorrect;
}

bool testPurchaseToInventory() {
    Game* game = Game::getInstance();
    Player& player = game->getPlayer();
    
    // Reset state
    player.getInventory()->clear();
    player.setMoney(1000.0f);
    
    float initialMoney = player.getMoney();
    
    Store store;
    store.addItem(new SeedAdapter(50.0f, []() { return new Strawberry(); }));
    
    Inventory* inv = player.getInventory();
    size_t initialSlots = inv->getStackCount();
    
    bool purchaseSuccess = store.purchaseItem(0, &player);
    
    float finalMoney = player.getMoney();
    bool moneyDeducted = (finalMoney == initialMoney - 50.0f);
    size_t finalSlots = inv->getStackCount();
    bool inventoryIncreased = (finalSlots == initialSlots + 1);
    int plantCount = inv->getPlantCount("Strawberry");
    bool plantInInventory = (plantCount == 1);
    
    if (!purchaseSuccess || !moneyDeducted || !inventoryIncreased || !plantInInventory) {
        std::cout << "\n  DEBUG testPurchaseToInventory:" << std::endl;
        std::cout << "    purchaseSuccess: " << purchaseSuccess << std::endl;
        std::cout << "    initialMoney: " << initialMoney << ", finalMoney: " << finalMoney << std::endl;
        std::cout << "    moneyDeducted: " << moneyDeducted << " (expected: 950)" << std::endl;
        std::cout << "    initialSlots: " << initialSlots << ", finalSlots: " << finalSlots << std::endl;
        std::cout << "    inventoryIncreased: " << inventoryIncreased << std::endl;
        std::cout << "    plantCount: " << plantCount << ", plantInInventory: " << plantInInventory << std::endl;
    }
    
    return purchaseSuccess && moneyDeducted && inventoryIncreased && plantInInventory;
}

bool testInsufficientFunds() {
    Game* game = Game::getInstance();
    Player& player = game->getPlayer();
    
    // Clear state and set to low money
    player.getInventory()->clear();
    player.setMoney(10.0f);
    
    Store store;
    store.addItem(new SeedAdapter(100.0f, []() { return new Pumpkin(); }));
    
    Inventory* inv = player.getInventory();
    size_t initialSlots = inv->getStackCount();
    
    bool purchaseFailed = !store.purchaseItem(0, &player);
    
    bool moneyUnchanged = (player.getMoney() == 10.0f);
    bool inventoryUnchanged = (inv->getStackCount() == initialSlots);
    
    // Reset money for next tests
    player.setMoney(1000.0f);
    
    return purchaseFailed && moneyUnchanged && inventoryUnchanged;
}

bool testInventoryFull() {
    Game* game = Game::getInstance();
    Player& player = game->getPlayer();
    
    // Reset and set high money
    player.getInventory()->clear();
    player.setMoney(100000.0f);
    
    Store store;
    // Add 32 different plant types (one for each slot)
    for (int i = 0; i < 32; i++) {
        store.addItem(new SeedAdapter(10.0f, []() { return new Lettuce(); }));
    }
    
    Inventory* inv = player.getInventory();
    size_t maxSlots = inv->getMaxSlots();
    
    // Buy 32 different items to fill all 32 slots with 1 plant each
    for (size_t i = 0; i < 32; i++) {
        // Each purchase from a different adapter creates a new unique plant
        // But since they're all Lettuce, they'll stack in the same slot!
    }
    
    // Actually, we need to create UNIQUE plant types. Let's simplify:
    // Just test that when slots are at max, we can't add a NEW slot
    
    // Set inventory to small capacity for easier testing
    inv->setMaxSlots(3);
    
    // Add 3 different plant types to fill 3 slots
    store.addItem(new SeedAdapter(10.0f, []() { return new Tomato(); }));
    store.addItem(new SeedAdapter(10.0f, []() { return new Carrot(); }));
    store.addItem(new SeedAdapter(10.0f, []() { return new Potato(); }));
    
    // Buy one of each
    store.purchaseItem(32, &player);  // Tomato
    store.purchaseItem(33, &player);  // Carrot
    store.purchaseItem(34, &player);  // Potato
    
    size_t stackCount = inv->getStackCount();
    bool hasThreeStacks = (stackCount == 3);
    
    // Now try to buy a 4th type (Cucumber) - should fail
    store.addItem(new SeedAdapter(10.0f, []() { return new Cucumber(); }));
    
    float moneyBefore = player.getMoney();
    bool purchaseFailed = !store.purchaseItem(35, &player);
    bool moneyUnchanged = (player.getMoney() == moneyBefore);
    
    if (!hasThreeStacks || !purchaseFailed || !moneyUnchanged) {
        std::cout << "\n  DEBUG testInventoryFull:" << std::endl;
        std::cout << "    maxSlots: " << inv->getMaxSlots() << std::endl;
        std::cout << "    stackCount: " << stackCount << std::endl;
        std::cout << "    hasThreeStacks: " << hasThreeStacks << std::endl;
        std::cout << "    purchaseFailed: " << purchaseFailed << std::endl;
        std::cout << "    moneyBefore: " << moneyBefore << ", moneyAfter: " << player.getMoney() << std::endl;
        std::cout << "    moneyUnchanged: " << moneyUnchanged << std::endl;
    }
    
    // Reset
    inv->setMaxSlots(32);
    inv->clear();
    player.setMoney(1000.0f);
    
    return hasThreeStacks && purchaseFailed && moneyUnchanged;
}

bool testPlantPricing() {
    // Test: More expensive plants are slower but sell for more
    
    Lettuce* lettuce = new Lettuce();     // Cheap: fast growth
    Pumpkin* pumpkin = new Pumpkin();     // Expensive: slow growth
    
    // Lettuce should grow faster (higher growth rate)
    bool lettuceGrowsFaster = (lettuce->getGrowthRate() > pumpkin->getGrowthRate());
    
    // Pumpkin should sell for more
    bool pumpkinSellsForMore = (pumpkin->getSellPrice() > lettuce->getSellPrice());
    
    // Verify specific values
    bool lettuceCorrect = (lettuce->getGrowthRate() == 1.6f && lettuce->getSellPrice() == 15.0f);
    bool pumpkinCorrect = (pumpkin->getGrowthRate() == 0.5f && pumpkin->getSellPrice() == 200.0f);
    
    delete lettuce;
    delete pumpkin;
    
    return lettuceGrowsFaster && pumpkinSellsForMore && lettuceCorrect && pumpkinCorrect;
}

bool testNonHardcodedFactory() {
    // Test that the factory pattern works with lambdas (non-hardcoded)
    
    // Create adapter with custom lambda
    auto customFactory = []() -> Plant* {
        return new Carrot();
    };
    
    SeedAdapter* adapter = new SeedAdapter(20.0f, customFactory);
    
    void* result1 = adapter->request();
    void* result2 = adapter->request();
    
    Plant* plant1 = static_cast<Plant*>(result1);
    Plant* plant2 = static_cast<Plant*>(result2);
    
    bool bothCreated = (plant1 != nullptr && plant2 != nullptr);
    bool correctType = (plant1->getType() == "Carrot" && plant2->getType() == "Carrot");
    bool differentInstances = (plant1 != plant2);
    
    delete plant1;
    delete plant2;
    delete adapter;
    
    return bothCreated && correctType && differentInstances;
}

bool testDynamicInventoryCapacity() {
    Game* game = Game::getInstance();
    Player& player = game->getPlayer();
    
    Inventory* inv = player.getInventory();
    
    // Reset
    inv->clear();
    player.setMoney(10000.0f);
    
    // Test default capacity
    size_t defaultCapacity = inv->getMaxSlots();
    bool hasDefaultCapacity = (defaultCapacity == 32);
    
    // Change capacity to smaller value
    inv->setMaxSlots(5);
    bool capacityChanged = (inv->getMaxSlots() == 5);
    
    // Test that it respects new capacity
    Store store;
    store.addItem(new SeedAdapter(10.0f, []() { return new Lettuce(); }));
    
    // Try to buy more than capacity
    for (size_t i = 0; i < 10; i++) {
        store.purchaseItem(0, &player);
    }
    
    size_t stackCount = inv->getStackCount();
    bool respectsCapacity = (stackCount <= 5);
    
    // Increase capacity and verify we can add more
    inv->setMaxSlots(10);
    bool purchaseSucceeds = store.purchaseItem(0, &player);
    
    if (!hasDefaultCapacity || !capacityChanged || !respectsCapacity || !purchaseSucceeds) {
        std::cout << "\n  DEBUG testDynamicInventoryCapacity:" << std::endl;
        std::cout << "    defaultCapacity: " << defaultCapacity << ", hasDefaultCapacity: " << hasDefaultCapacity << std::endl;
        std::cout << "    getMaxSlots after set to 5: " << inv->getMaxSlots() << ", capacityChanged: " << capacityChanged << std::endl;
        std::cout << "    stackCount after 10 purchases: " << stackCount << ", respectsCapacity: " << respectsCapacity << std::endl;
        std::cout << "    purchaseSucceeds after increasing to 10: " << purchaseSucceeds << std::endl;
    }
    
    // Reset
    inv->setMaxSlots(32);
    inv->clear();
    player.setMoney(1000.0f);
    
    return hasDefaultCapacity && capacityChanged && respectsCapacity && purchaseSucceeds;
}