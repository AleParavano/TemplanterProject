#include "PersistenceManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>

PersistenceManager::PersistenceManager(const std::string& filename) 
    : saveFilename(filename) {}

PersistenceManager::~PersistenceManager() {}

std::string PersistenceManager::encodeString(const std::string& str) const {
    std::string encoded;
    for (char c : str) {
        switch (c) {
            case '\n': encoded += "\\n"; break;
            case '\r': encoded += "\\r"; break;
            case '\\': encoded += "\\\\"; break;
            case '|': encoded += "\\|"; break;
            case ':': encoded += "\\:"; break;
            default: encoded += c; break;
        }
    }
    return encoded;
}

std::string PersistenceManager::decodeString(const std::string& str) const {
    std::string decoded;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '\\' && i + 1 < str.length()) {
            char next = str[i + 1];
            switch (next) {
                case 'n': decoded += '\n'; ++i; break;
                case 'r': decoded += '\r'; ++i; break;
                case '\\': decoded += '\\'; ++i; break;
                case '|': decoded += '|'; ++i; break;
                case ':': decoded += ':'; ++i; break;
                default: decoded += str[i]; break;
            }
        } else {
            decoded += str[i];
        }
    }
    return decoded;
}

bool PersistenceManager::saveMementos(const Caretaker* caretaker) {
    if (!caretaker) {
        return false;
    }
    
    std::ofstream file(saveFilename);
    if (!file.is_open()) {
        return false;
    }
    
    // Write header with metadata
    int mementoCount = caretaker->getMementoCount();
    int currentIndex = caretaker->getCurrentIndex();
    
    file << "MEMENTO_SAVE_V1\n";
    file << "COUNT:" << mementoCount << "\n";
    file << "CURRENT_INDEX:" << currentIndex << "\n";
    file << "BEGIN_MEMENTOS\n";
    
    // Write each memento
    for (int i = 0; i < mementoCount; ++i) {
        Memento* memento = caretaker->getMemento(i);
        if (memento) {
            file << "MEMENTO_START\n";
            
            // Write basic player stats
            file << "MONEY:" << memento->getMoney() << "\n";
            file << "RATING:" << memento->getRating() << "\n";
            file << "DAY:" << memento->getDay() << "\n";
            file << "HOUR:" << memento->getHour() << "\n";
            file << "MINUTE:" << memento->getMinute() << "\n";
            
            // Write serialized data (with encoding to handle special characters)
            file << "INVENTORY:" << encodeString(memento->getInventoryData()) << "\n";
            file << "GREENHOUSE:" << encodeString(memento->getGreenhouseData()) << "\n";
            file << "WORKERS:" << encodeString(memento->getWorkerData()) << "\n";
            
            file << "MEMENTO_END\n";
        }
    }
    
    file << "END_MEMENTOS\n";
    file.close();
    
    return true;
}

bool PersistenceManager::loadMementos(Caretaker* caretaker) {
    if (!caretaker || !saveFileExists()) {
        return false;
    }
    
    std::ifstream file(saveFilename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    std::vector<Memento*> loadedMementos;
    
    // Read and validate header
    std::getline(file, line);
    if (line != "MEMENTO_SAVE_V1") {
        file.close();
        return false;
    }
    
    int count = 0;
    int currentIdx = 0;
    
    // Parse metadata
    while (std::getline(file, line)) {
        if (line == "BEGIN_MEMENTOS") break;
        
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            
            if (key == "COUNT") {
                try {
                    count = std::stoi(value);
                } catch (...) {}
            } else if (key == "CURRENT_INDEX") {
                try {
                    currentIdx = std::stoi(value);
                } catch (...) {}
            }
        }
    }
    
    // Parse mementos
    while (std::getline(file, line)) {
        if (line == "END_MEMENTOS") break;
        if (line != "MEMENTO_START") continue;
        
        float money = 0.0f;
        int rating = 0, day = 1, hour = 6, minute = 0;
        std::string invData, ghData, workerData;
        
        // Read memento data
        while (std::getline(file, line)) {
            if (line == "MEMENTO_END") break;
            
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                std::string key = line.substr(0, colonPos);
                std::string value = line.substr(colonPos + 1);
                
                try {
                    if (key == "MONEY") {
                        money = std::stof(value);
                    } else if (key == "RATING") {
                        rating = std::stoi(value);
                    } else if (key == "DAY") {
                        day = std::stoi(value);
                    } else if (key == "HOUR") {
                        hour = std::stoi(value);
                    } else if (key == "MINUTE") {
                        minute = std::stoi(value);
                    } else if (key == "INVENTORY") {
                        invData = decodeString(value);
                    } else if (key == "GREENHOUSE") {
                        ghData = decodeString(value);
                    } else if (key == "WORKERS") {
                        workerData = decodeString(value);
                    }
                } catch (...) {
                    continue;
                }
            }
        }
        
        // Create and add memento
        Memento* memento = new Memento(invData, workerData, ghData, money, rating, day, hour, minute);
        loadedMementos.push_back(memento);
    }
    
    file.close();
    
    // Add all loaded mementos to caretaker
    for (auto memento : loadedMementos) {
        caretaker->addMemento(memento);
    }
    
    return !loadedMementos.empty();
}

bool PersistenceManager::saveFileExists() const {
    return std::filesystem::exists(saveFilename);
}

bool PersistenceManager::deleteSaveFile() {
    try {
        if (saveFileExists()) {
            std::filesystem::remove(saveFilename);
            return true;
        }
        return true;
    } catch (...) {
        return false;
    }
}

void PersistenceManager::setFilename(const std::string& filename) {
    saveFilename = filename;
}

std::string PersistenceManager::getFilename() const {
    return saveFilename;
}