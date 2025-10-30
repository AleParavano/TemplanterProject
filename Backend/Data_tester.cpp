#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>
#include "PersistenceManager.h"
#include "Caretaker.h"
#include "Memento.h"

class PersistenceManagerTester {
private:
    int testsRun;
    int testsPassed;
    int testsFailed;
    const std::string TEST_FILENAME = "test_saves.txt";

public:
    PersistenceManagerTester() : testsRun(0), testsPassed(0), testsFailed(0) {}

    void runAllTests() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "PERSISTENCEMANAGER UNIT TESTS" << std::endl;
        std::cout << std::string(60, '=') << "\n" << std::endl;

        testFileCreation();
        testSingleMementoSave();
        testMultipleMementosSave();
        testMementoLoad();
        testCurrentIndexPreservation();
        testSpecialCharacterEncoding();
        testEmptyCaretakerSave();
        testFileNotFoundLoad();
        testFilenameChange();
        testSaveFileExists();
        testDeleteSaveFile();
        testCorruptedFileHandling();
        testMaxMementoLimit();

        printSummary();
    }

private:
    void testFileCreation() {
        std::cout << "TEST 1: File Creation" << std::endl;
        testsRun++;

        cleanupTestFile();
        
        Caretaker caretaker;
        Memento* memento = new Memento("inv_data", "worker_data", "gh_data", 100.0f, 50, 1, 6, 0);
        caretaker.addMemento(memento);

        PersistenceManager pm(TEST_FILENAME);
        bool result = pm.saveMementos(&caretaker);

        if (result && std::filesystem::exists(TEST_FILENAME)) {
            std::cout << "  ✓ File created successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ File creation failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testSingleMementoSave() {
        std::cout << "TEST 2: Single Memento Save" << std::endl;
        testsRun++;

        cleanupTestFile();

        Caretaker caretaker;
        Memento* memento = new Memento("test_inv", "test_workers", "test_gh", 250.5f, 75, 3, 14, 30);
        caretaker.addMemento(memento);

        PersistenceManager pm(TEST_FILENAME);
        bool saveResult = pm.saveMementos(&caretaker);

        if (saveResult && caretaker.getMementoCount() == 1) {
            std::cout << "  ✓ Single memento saved successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Single memento save failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testMultipleMementosSave() {
        std::cout << "TEST 3: Multiple Mementos Save" << std::endl;
        testsRun++;

        cleanupTestFile();

        Caretaker caretaker;
        
        Memento* m1 = new Memento("inv1", "work1", "gh1", 100.0f, 50, 1, 6, 0);
        Memento* m2 = new Memento("inv2", "work2", "gh2", 200.0f, 60, 2, 12, 30);
        Memento* m3 = new Memento("inv3", "work3", "gh3", 300.0f, 70, 3, 18, 45);
        
        caretaker.addMemento(m1);
        caretaker.addMemento(m2);
        caretaker.addMemento(m3);

        PersistenceManager pm(TEST_FILENAME);
        bool result = pm.saveMementos(&caretaker);

        if (result && caretaker.getMementoCount() == 3) {
            std::cout << "  ✓ Multiple mementos saved successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Multiple mementos save failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testMementoLoad() {
        std::cout << "TEST 4: Memento Load" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Save phase
        Caretaker saveCaretaker;
        Memento* m1 = new Memento("loaded_inv", "loaded_work", "loaded_gh", 500.0f, 85, 5, 10, 15);
        saveCaretaker.addMemento(m1);

        PersistenceManager pm(TEST_FILENAME);
        pm.saveMementos(&saveCaretaker);

        // Load phase
        Caretaker loadCaretaker;
        bool loadResult = pm.loadMementos(&loadCaretaker);

        if (loadResult && loadCaretaker.getMementoCount() == 1) {
            Memento* loaded = loadCaretaker.getMemento(0);
            if (loaded && loaded->getMoney() == 500.0f && loaded->getRating() == 85) {
                std::cout << "  ✓ Memento loaded successfully with correct data\n" << std::endl;
                testsPassed++;
            } else {
                std::cout << "  ✗ Loaded memento has incorrect data\n" << std::endl;
                testsFailed++;
            }
        } else {
            std::cout << "  ✗ Memento load failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testCurrentIndexPreservation() {
        std::cout << "TEST 5: Current Index Preservation" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Save phase
        Caretaker saveCaretaker;
        Memento* m1 = new Memento("inv1", "work1", "gh1", 100.0f, 50, 1, 6, 0);
        Memento* m2 = new Memento("inv2", "work2", "gh2", 200.0f, 60, 2, 12, 0);
        Memento* m3 = new Memento("inv3", "work3", "gh3", 300.0f, 70, 3, 18, 0);

        saveCaretaker.addMemento(m1);
        saveCaretaker.addMemento(m2);
        saveCaretaker.addMemento(m3);
        
        int savedIndex = saveCaretaker.getCurrentIndex();

        PersistenceManager pm(TEST_FILENAME);
        pm.saveMementos(&saveCaretaker);

        // Load phase
        Caretaker loadCaretaker;
        pm.loadMementos(&loadCaretaker);

        if (loadCaretaker.getCurrentIndex() == savedIndex) {
            std::cout << "  ✓ Current index preserved correctly (Index: " << loadCaretaker.getCurrentIndex() << ")\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Current index not preserved (Expected: " << savedIndex 
                      << ", Got: " << loadCaretaker.getCurrentIndex() << ")\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testSpecialCharacterEncoding() {
        std::cout << "TEST 6: Special Character Encoding" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Create data with special characters
        std::string dataWithSpecialChars = "Lettuce:2|Tomato:1\nCarrot|data:with:colons";

        Caretaker saveCaretaker;
        Memento* memento = new Memento(dataWithSpecialChars, "workers", "greenhouse", 100.0f, 50, 1, 6, 0);
        saveCaretaker.addMemento(memento);

        PersistenceManager pm(TEST_FILENAME);
        pm.saveMementos(&saveCaretaker);

        Caretaker loadCaretaker;
        pm.loadMementos(&loadCaretaker);

        Memento* loaded = loadCaretaker.getMemento(0);
        if (loaded && loaded->getInventoryData() == dataWithSpecialChars) {
            std::cout << "  ✓ Special characters encoded and decoded correctly\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Special character encoding failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testEmptyCaretakerSave() {
        std::cout << "TEST 7: Empty Caretaker Save" << std::endl;
        testsRun++;

        cleanupTestFile();

        Caretaker emptyCaretaker;
        PersistenceManager pm(TEST_FILENAME);
        bool result = pm.saveMementos(&emptyCaretaker);

        if (result) {
            std::cout << "  ✓ Empty caretaker saved successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Empty caretaker save failed\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testFileNotFoundLoad() {
        std::cout << "TEST 8: File Not Found Load" << std::endl;
        testsRun++;

        cleanupTestFile();

        Caretaker caretaker;
        PersistenceManager pm("nonexistent_file_12345.txt");
        bool result = pm.loadMementos(&caretaker);

        if (!result && caretaker.getMementoCount() == 0) {
            std::cout << "  ✓ Correctly handled missing file\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Failed to handle missing file properly\n" << std::endl;
            testsFailed++;
        }
    }

    void testFilenameChange() {
        std::cout << "TEST 9: Filename Change" << std::endl;
        testsRun++;

        cleanupTestFile();
        std::string altFilename = "alt_test_saves.txt";
        if (std::filesystem::exists(altFilename)) {
            std::filesystem::remove(altFilename);
        }

        PersistenceManager pm(TEST_FILENAME);
        pm.setFilename(altFilename);

        if (pm.getFilename() == altFilename) {
            std::cout << "  ✓ Filename changed successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Filename change failed\n" << std::endl;
            testsFailed++;
        }

        if (std::filesystem::exists(altFilename)) {
            std::filesystem::remove(altFilename);
        }
    }

    void testSaveFileExists() {
        std::cout << "TEST 10: Save File Exists Check" << std::endl;
        testsRun++;

        cleanupTestFile();

        PersistenceManager pm(TEST_FILENAME);

        // Before save
        if (!pm.saveFileExists()) {
            std::cout << "  ✓ Correctly detected non-existent file" << std::endl;
        } else {
            std::cout << "  ✗ Failed to detect non-existent file" << std::endl;
            testsFailed++;
            cleanupTestFile();
            return;
        }

        // After save
        Caretaker caretaker;
        Memento* m = new Memento("inv", "work", "gh", 100.0f, 50, 1, 6, 0);
        caretaker.addMemento(m);
        pm.saveMementos(&caretaker);

        if (pm.saveFileExists()) {
            std::cout << "  ✓ Correctly detected existing file\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Failed to detect existing file\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testDeleteSaveFile() {
        std::cout << "TEST 11: Delete Save File" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Create file
        Caretaker caretaker;
        Memento* m = new Memento("inv", "work", "gh", 100.0f, 50, 1, 6, 0);
        caretaker.addMemento(m);

        PersistenceManager pm(TEST_FILENAME);
        pm.saveMementos(&caretaker);

        // Delete file
        bool deleteResult = pm.deleteSaveFile();

        if (deleteResult && !std::filesystem::exists(TEST_FILENAME)) {
            std::cout << "  ✓ Save file deleted successfully\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Save file deletion failed\n" << std::endl;
            testsFailed++;
        }
    }

    void testCorruptedFileHandling() {
        std::cout << "TEST 12: Corrupted File Handling" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Create a corrupted file
        std::ofstream corruptFile(TEST_FILENAME);
        corruptFile << "INVALID_HEADER\n";
        corruptFile << "GARBAGE_DATA\n";
        corruptFile.close();

        Caretaker caretaker;
        PersistenceManager pm(TEST_FILENAME);
        bool result = pm.loadMementos(&caretaker);

        if (!result) {
            std::cout << "  ✓ Correctly handled corrupted file\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Failed to handle corrupted file\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void testMaxMementoLimit() {
        std::cout << "TEST 13: Max Memento Limit" << std::endl;
        testsRun++;

        cleanupTestFile();

        // Try to exceed MAX_MEMENTOS (3)
        Caretaker caretaker;
        for (int i = 0; i < 5; ++i) {
            Memento* m = new Memento("inv" + std::to_string(i), "work" + std::to_string(i), 
                                    "gh" + std::to_string(i), 100.0f * (i + 1), 50 + i, i + 1, 6, 0);
            caretaker.addMemento(m);
        }

        PersistenceManager pm(TEST_FILENAME);
        bool result = pm.saveMementos(&caretaker);

        Caretaker loadCaretaker;
        pm.loadMementos(&loadCaretaker);

        if (result && loadCaretaker.getMementoCount() <= 3) {
            std::cout << "  ✓ Max memento limit respected (Loaded: " << loadCaretaker.getMementoCount() << "/3)\n" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ✗ Max memento limit exceeded\n" << std::endl;
            testsFailed++;
        }

        cleanupTestFile();
    }

    void cleanupTestFile() {
        if (std::filesystem::exists(TEST_FILENAME)) {
            std::filesystem::remove(TEST_FILENAME);
        }
    }

    void printSummary() {
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "TEST SUMMARY" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Tests Run:    " << testsRun << std::endl;
        std::cout << "Tests Passed: " << testsPassed << " ✓" << std::endl;
        std::cout << "Tests Failed: " << testsFailed << " ✗" << std::endl;

        float passRate = (testsRun > 0) ? (float)testsPassed / testsRun * 100.0f : 0.0f;
        std::cout << "Pass Rate:    " << passRate << "%" << std::endl;

        if (testsFailed == 0) {
            std::cout << "\n✓ ALL TESTS PASSED!" << std::endl;
        } else {
            std::cout << "\n✗ SOME TESTS FAILED" << std::endl;
        }
        std::cout << std::string(60, '=') << "\n" << std::endl;
    }
};

// Main test runner
int main() {
    PersistenceManagerTester tester;
    tester.runAllTests();
    return 0;
}