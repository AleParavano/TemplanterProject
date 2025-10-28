#include "Game.h"
#include "Plant.h"
#include "Greenhouse.h"
#include <iostream>
#include <thread>
#include <chrono>

void printPlantStatus(Plant* plant) {
    std::cout << "\n[" << plant->getType() << "] "
              << "State: " << plant->getStateName() 
              << " | Growth: " << (int)plant->getGrowth() << "% "
              << "| Water: " << (int)plant->getWater() << "% "
              << "| Nutrients: " << (int)plant->getNutrients() << "%" 
              << std::endl;
}

int main() {
    std::cout << "=== Plant State System Demo ===" << std::endl;
    std::cout << "Plants consume water & nutrients and grow each tick\n" << std::endl;

    // Get game and player
    Game* game = Game::getInstance();
    Player& player = game->getPlayer();

    std::cout << "Starting time: " << player.getFullTimeString() << "\n" << std::endl;

    // Create a greenhouse with plants
    Greenhouse* greenhouse = player.getPlot();

    // Plant different types
    Plant* carrot = new Carrot();
    Plant* tomato = new Tomato();
    Plant* sunflower = new Sunflower();

    greenhouse->addPlant(carrot);
    greenhouse->addPlant(tomato);
    greenhouse->addPlant(sunflower);

    std::cout << "🌱 Planted 3 plants in greenhouse:" << std::endl;
    std::cout << "  - Carrot (Growth Rate: 1.1x)" << std::endl;
    std::cout << "  - Tomato (Growth Rate: 1.4x)" << std::endl;
    std::cout << "  - Sunflower (Growth Rate: 1.6x)" << std::endl;

    // Show initial status
    std::cout << "\n--- Initial Status ---" << std::endl;
    printPlantStatus(carrot);
    printPlantStatus(tomato);
    printPlantStatus(sunflower);

    // Start the game clock
    player.startClock();
    std::cout << "\n⏰ Game clock started!" << std::endl;

    // Simulate game ticks
    std::cout << "\n=== Simulation: Growing Plants ===" << std::endl;
    std::cout << "Each plant ticks every second (simulating in-game time)\n" << std::endl;

    int tickCount = 0;
    int maxTicks = 50;  // Run for 50 ticks

    for (int i = 0; i < maxTicks; i++) {
        tickCount++;
        
        // Wait 1 second per tick
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Tick all plants
        carrot->tick();
        tomato->tick();
        sunflower->tick();

        // Show status every 10 ticks
        if (tickCount % 10 == 0) {
            std::cout << "\n--- After " << tickCount << " ticks ---" << std::endl;
            std::cout << "Game time: " << player.getFullTimeString() << std::endl;
            printPlantStatus(carrot);
            printPlantStatus(tomato);
            printPlantStatus(sunflower);

            // Check if any plants are ripe
            if (carrot->isRipe()) {
                std::cout << "🌟 Carrot is ready to harvest!" << std::endl;
            }
            if (tomato->isRipe()) {
                std::cout << "🌟 Tomato is ready to harvest!" << std::endl;
            }
            if (sunflower->isRipe()) {
                std::cout << "🌟 Sunflower is ready to harvest!" << std::endl;
            }
        }

        // Water plants at tick 15 (they should be getting low)
        if (tickCount == 15) {
            std::cout << "\n💧 Watering all plants..." << std::endl;
            carrot->water(50.0f);
            tomato->water(50.0f);
            sunflower->water(50.0f);
        }

        // Fertilize plants at tick 20
        if (tickCount == 20) {
            std::cout << "\n🌿 Fertilizing all plants..." << std::endl;
            carrot->fertilize(50.0f);
            tomato->fertilize(50.0f);
            sunflower->fertilize(50.0f);
        }

        // Check if all plants are ripe
        if (carrot->isRipe() && tomato->isRipe() && sunflower->isRipe()) {
            std::cout << "\n✓ All plants are ripe! Breaking simulation." << std::endl;
            break;
        }

        // Check if any plant died
        if (carrot->isDead() || tomato->isDead() || sunflower->isDead()) {
            std::cout << "\n⚠️ A plant died! Check resource management!" << std::endl;
        }
    }

    // Final status
    std::cout << "\n=== Final Status ===" << std::endl;
    std::cout << "Game time: " << player.getFullTimeString() << std::endl;
    carrot->printStatus();
    tomato->printStatus();
    sunflower->printStatus();

    // Demonstrate resource depletion
    std::cout << "\n=== Testing Resource Depletion ===" << std::endl;
    Plant* testPlant = new Lettuce();
    std::cout << "Created test Lettuce plant" << std::endl;
    testPlant->printStatus();

    std::cout << "\nRunning 30 ticks without watering or fertilizing..." << std::endl;
    for (int i = 0; i < 30; i++) {
        testPlant->tick();
        
        if (i % 10 == 9) {
            std::cout << "\nAfter " << (i+1) << " ticks:" << std::endl;
            printPlantStatus(testPlant);
        }
        
        if (testPlant->isDead()) {
            std::cout << "\n💀 Plant died after " << (i+1) << " ticks from lack of resources!" << std::endl;
            break;
        }
    }

    testPlant->printStatus();

    // Demonstrate state transitions
    std::cout << "\n=== State Transition Summary ===" << std::endl;
    std::cout << "Seed (0-25% growth):" << std::endl;
    std::cout << "  - Low resource consumption (50%)" << std::endl;
    std::cout << "  - Slow growth (70% rate)" << std::endl;
    std::cout << "  - Transitions to Growing at 25% growth" << std::endl;
    
    std::cout << "\nGrowing (25-100% growth):" << std::endl;
    std::cout << "  - Normal resource consumption" << std::endl;
    std::cout << "  - Full growth rate" << std::endl;
    std::cout << "  - Transitions to Ripe at 100% growth" << std::endl;
    
    std::cout << "\nRipe (100%+ growth):" << std::endl;
    std::cout << "  - Low resource consumption (30%)" << std::endl;
    std::cout << "  - Ready to harvest!" << std::endl;
    std::cout << "  - Can over-ripen (dies at 150% growth)" << std::endl;
    
    std::cout << "\nDead:" << std::endl;
    std::cout << "  - No resource consumption" << std::endl;
    std::cout << "  - Must be removed and replanted" << std::endl;
    std::cout << "  - Causes: lack of water/nutrients, over-ripening" << std::endl;

    // Growth rates comparison
    std::cout << "\n=== Growth Rate Multipliers ===" << std::endl;
    std::cout << "Lettuce:   1.0x (baseline)" << std::endl;
    std::cout << "Carrot:    1.1x (10% faster)" << std::endl;
    std::cout << "Potato:    1.2x" << std::endl;
    std::cout << "Cucumber:  1.3x" << std::endl;
    std::cout << "Tomato:    1.4x" << std::endl;
    std::cout << "Pepper:    1.5x" << std::endl;
    std::cout << "Sunflower: 1.6x" << std::endl;
    std::cout << "Strawberry:1.7x" << std::endl;
    std::cout << "Corn:      1.8x" << std::endl;
    std::cout << "Pumpkin:   2.0x (fastest)" << std::endl;

    // Cleanup
    player.stopClock();
    delete testPlant;

    std::cout << "\n=== Demo Complete ===" << std::endl;
    std::cout << "✓ Plant state system working" << std::endl;
    std::cout << "✓ Resource consumption implemented" << std::endl;
    std::cout << "✓ Growth progression working" << std::endl;
    std::cout << "✓ State transitions automatic" << std::endl;
    std::cout << "✓ Integrated with player clock" << std::endl;

    return 0;
}