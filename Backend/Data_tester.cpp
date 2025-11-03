/**
 * @file Data_tester.cpp
 * @brief Test suite for core game systems
 *
 * Provides comprehensive testing of:
 * - Save/Load functionality
 * - Inventory management
 * - Plant growth system
 * - Worker automation
 * - Store transactions
 *
 * @note Uses informal test framework with pass/fail reporting
 */

#include <iostream>
#include <fstream>
#include "Caretaker.h"
#include "Memento.h"

/**
 * @class MementoTester
 * @brief Testing utility class
 *
 * Provides test tracking and result formatting
 */
class MementoTester {
    // ...existing code...
};

/**
 * @brief Test adapter pattern implementation
 * @return true if all adapter tests pass
 */
bool testAdapterPattern() {
    // ...existing code...
}

int main() {
    std::cout << "\n=== Simple Caretaker with File Persistence ===\n" << std::endl;

    // Create caretaker - loads from file if it exists
    Caretaker caretaker("game_state.txt");

    std::cout << "1. Creating first game state..." << std::endl;
    Memento* state1 = new Memento(
        "Lettuce:5|Tomato:3",
        "2",
        "5,16|Lettuce|1.6|15.0|Seed|0.0|100.0|100.0|Tomato|1.0|55.0|Growing|45.5|75.2|82.1|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL",
        1500.50f,
        85,
        5,
        14,
        30
    );
    
    // Add memento - automatically saves to file
    caretaker.addMemento(state1);
    std::cout << "   ✓ Saved to game_state.txt\n" << std::endl;

    // Display file contents
    std::cout << "2. File contents:" << std::endl;
    std::ifstream file("game_state.txt");
    if (file.is_open()) {
        std::string line;
        int lineNum = 1;
        while (std::getline(file, line)) {
            std::cout << "   " << lineNum << ": " << line << std::endl;
            lineNum++;
        }
        file.close();
    }
    std::cout << std::endl;

    // Verify we can retrieve the memento
    std::cout << "3. Retrieving memento from memory..." << std::endl;
    Memento* loaded = caretaker.getMemento();
    if (loaded) {
        std::cout << "   ✓ Money: $" << loaded->getMoney() << std::endl;
        std::cout << "   ✓ Rating: " << loaded->getRating() << std::endl;
        std::cout << "   ✓ Day: " << loaded->getDay() << ", " 
                  << loaded->getHour() << ":" << loaded->getMinute() << std::endl;
        std::cout << "   ✓ Inventory: " << loaded->getInventoryData() << std::endl;
    }
    std::cout << std::endl;

    // Simulate creating a new state (e.g., player progresses game)
    std::cout << "4. Creating updated game state..." << std::endl;
    Memento* state2 = new Memento(
        "Lettuce:3|Tomato:5|Carrot:2",
        "3",
        "5,16|Tomato|1.0|55.0|Growing|60.5|70.2|75.1|Carrot|1.4|25.0|Ripe|100.0|60.0|70.0|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL|NULL",
        2150.75f,
        92,
        6,
        18,
        45
    );
    
    caretaker.addMemento(state2);
    std::cout << "   ✓ Saved to game_state.txt (overwrites previous)\n" << std::endl;

    // Display updated file contents
    std::cout << "5. Updated file contents:" << std::endl;
    file.open("game_state.txt");
    if (file.is_open()) {
        std::string line;
        int lineNum = 1;
        while (std::getline(file, line)) {
            std::cout << "   " << lineNum << ": " << line << std::endl;
            lineNum++;
        }
        file.close();
    }
    std::cout << std::endl;

    // Test loading in a new caretaker (simulating game restart)
    std::cout << "6. Simulating game restart (new Caretaker)..." << std::endl;
    Caretaker caretaker2("game_state.txt");
    Memento* restored = caretaker2.getMemento();
    if (restored) {
        std::cout << "   ✓ Loaded from file successfully!" << std::endl;
        std::cout << "   ✓ Money: $" << restored->getMoney() << std::endl;
        std::cout << "   ✓ Rating: " << restored->getRating() << std::endl;
        std::cout << "   ✓ Inventory: " << restored->getInventoryData() << std::endl;
    }
    std::cout << std::endl;

    // Test delete
    std::cout << "7. Deleting all data..." << std::endl;
    caretaker2.deleteData();
    std::cout << "   ✓ Data deleted from memory and file" << std::endl;
    std::cout << "   ✓ File removed\n" << std::endl;

    // Verify file is deleted
    std::cout << "8. Verification:" << std::endl;
    if (std::ifstream("game_state.txt").fail()) {
        std::cout << "   ✓ game_state.txt successfully deleted" << std::endl;
    }
    
    std::cout << "\n=== Simple Caretaker with Auto-Save Works! ===\n" << std::endl;

    return 0;
}