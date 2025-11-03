<<<<<<< HEAD
// #ifndef CUSTOMERMANAGER_H
// #define CUSTOMERMANAGER_H

// #include "raylib.h"
// #include "CustomerVisual.h"
// #include "../Backend/CustomerFactory.h"
// #include "../Backend/PlantFactory.h"
// #include <queue>
// #include <vector>
// #include <memory>
// #include <algorithm>

// class CustomerManager
// {
// private:
//     std::vector<CustomerVisual*> activeCustomers; // For rendering and updates
    
//     RandomFactory customerFactory;
//     RandomPlantFactory plantFactory;
    
//     // Spawn settings
//     Vector2 doorPosition;
//     Vector2 counterWaitPosition;
//     float customerSpacing;
//     float spawnTimer;
//     float spawnInterval;
    
//     // Max customers
//     const int MAX_CUSTOMERS = 5;
    
// public:
//     CustomerManager(Vector2 doorPos = {1270, 0}, Vector2 counterPos = {1200, 580})
//         : doorPosition(doorPos), 
//           counterWaitPosition(counterPos),
//           customerSpacing(80.0f),
//           spawnTimer(0.0f),
//           spawnInterval(5.0f) // Spawn every 5 seconds
//     {
//     }
    
//     ~CustomerManager()
//     {
//         // Clean up all customers
//         for (auto* customer : activeCustomers)
//         {
//             delete customer->customer; // Delete backend customer
//             delete customer; // Delete visual
//         }
//         activeCustomers.clear();
//     }
    
//     void update(float deltaTime, bool storeOpen)
//     {
//         // Update spawn timer
//         if (storeOpen && activeCustomers.size() < MAX_CUSTOMERS)
//         {
//             spawnTimer += deltaTime;
            
//             if (spawnTimer >= spawnInterval)
//             {
//                 spawnCustomer();
//                 spawnTimer = 0.0f;
//             }
//         }
        
//         // Update all customers (both active and leaving)
//         for (auto* custVisual : activeCustomers)
//         {
//             custVisual->update(deltaTime);
//         }
        
//         // Remove customers that have left and reorder queue
//         bool removedAny = false;
//         activeCustomers.erase(
//             std::remove_if(activeCustomers.begin(), activeCustomers.end(),
//                 [&removedAny](CustomerVisual* cv) {
//                     // Check if customer has left the screen (walked off the top)
//                     if (!cv->isActive && cv->position.y <= -50) {
//                         delete cv->customer;
//                         delete cv;
//                         removedAny = true;
//                         return true;
//                     }
//                     return false;
//                 }),
//             activeCustomers.end()
//         );
        
//         // If any customer was removed, reorder the queue
//         if (removedAny)
//         {
//             reorderQueue();
//         }
//     }
    
//     void render() const
//     {
//         for (const auto* custVisual : activeCustomers)
//         {
//             // Always render the customer (even when leaving)
//             custVisual->render();
            
//             // Only draw thought bubble for active customers
//             if (custVisual->customer && custVisual->isActive)
//             {
//                 drawThoughtBubble(custVisual);
//             }
//         }
//     }
    
//     void spawnCustomer()
//     {
//         if (activeCustomers.size() >= MAX_CUSTOMERS) return;
        
//         // Create random plant and customer
//         Plant* requestedPlant = plantFactory.produce();
//         Customer* newCustomer = customerFactory.create(requestedPlant);
        
//         // Create visual at door position
//         CustomerVisual* custVisual = new CustomerVisual(newCustomer, doorPosition);
        
//         // Calculate final position for this customer
//         Vector2 targetPos = calculateQueuePosition(activeCustomers.size());
//         custVisual->moveTo(targetPos);
        
//         activeCustomers.push_back(custVisual);
//     }
    
//     CustomerVisual* getClickedCustomer(Vector2 mousePos)
//     {
//         for (auto* custVisual : activeCustomers)
//         {
//             if (custVisual->isActive && custVisual->isHovered(mousePos))
//             {
//                 return custVisual;
//             }
//         }
//         return nullptr;
//     }
    
//     bool serveCustomer(CustomerVisual* custVisual, const std::string& plantType)
//     {
//         if (!custVisual || !custVisual->customer) return false;
        
//         // Safety check: ensure customer has a valid requested plant
//         if (!custVisual->customer->getRequestedPlant()) return false;
        
//         // Check if plant matches request
//         if (custVisual->customer->getRequestedPlant()->getType() == plantType)
//         {
//             // Customer is satisfied - make them leave (walk past the door off-screen)
//             Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100}; // Walk past door
//             custVisual->moveTo(exitPosition);
//             custVisual->isActive = false;
//             return true;
//         }
        
//         return false;
//     }
    
//     void dismissCustomer(CustomerVisual* custVisual)
//     {
//         if (!custVisual) return;
        
//         // Make customer walk past the door to exit
//         Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100}; // Walk past door
//         custVisual->moveTo(exitPosition);
//         custVisual->isActive = false;
//     }
    
//     int getCustomerCount() const
//     {
//         return activeCustomers.size();
//     }
    
//     void setSpawnInterval(float interval)
//     {
//         spawnInterval = interval;
//     }
    
// private:
//     Vector2 calculateQueuePosition(int queueIndex)
//     {
//         // Start from leftmost safe position (just past boundary wall at x=876)
//         // and move right for each customer
//         float startX = 920.0f; // Safe distance from boundary wall (823 + 53 = 876)
//         return {
//             startX + (queueIndex * customerSpacing),
//             counterWaitPosition.y
//         };
//     }
    
//     void reorderQueue()
//     {
//         // Move all active customers to their correct queue positions
//         int activeIndex = 0;
//         for (auto* custVisual : activeCustomers)
//         {
//             if (custVisual->isActive)
//             {
//                 Vector2 newPos = calculateQueuePosition(activeIndex);
//                 custVisual->moveTo(newPos);
//                 activeIndex++;
//             }
//         }
//     }
    
//     void drawThoughtBubble(const CustomerVisual* custVisual) const
//     {
//         if (!custVisual->customer) return;
        
//         Plant* requestedPlant = custVisual->customer->getRequestedPlant();
//         if (!requestedPlant) return; // Safety check
        
//         // Thought bubble position (above customer)
//         Vector2 bubblePos = {
//             custVisual->position.x,
//             custVisual->position.y - 60
//         };
        
//         // Draw bubble
//         DrawCircle(bubblePos.x, bubblePos.y, 25, WHITE);
//         DrawCircle(bubblePos.x - 10, bubblePos.y + 15, 10, WHITE);
//         DrawCircle(bubblePos.x - 15, bubblePos.y + 25, 5, WHITE);
        
//         // Draw bubble outline
//         DrawCircleLines(bubblePos.x, bubblePos.y, 25, BLACK);
//         DrawCircleLines(bubblePos.x - 10, bubblePos.y + 15, 10, BLACK);
//         DrawCircleLines(bubblePos.x - 15, bubblePos.y + 25, 5, BLACK);
        
//         // Draw plant name in bubble
//         std::string plantName = requestedPlant->getType();
//         int textWidth = MeasureText(plantName.c_str(), 12);
//         DrawText(plantName.c_str(), 
//                 bubblePos.x - textWidth/2, 
//                 bubblePos.y - 6, 
//                 12, BLACK);
//     }
// };

// #endif

=======
>>>>>>> origin/Frontend
#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "raylib.h"
#include "CustomerVisual.h"
#include "../Backend/CustomerFactory.h"
#include "../Backend/PlantFactory.h"
#include <vector>
#include <algorithm>

class CustomerManager
{
private:
    std::vector<CustomerVisual*> activeCustomers;
    
    RandomFactory customerFactory;
    RandomPlantFactory plantFactory;
    
    Vector2 doorPosition;
    Vector2 counterWaitPosition;
    float customerSpacing;
    float spawnTimer;
    float spawnInterval;
    
    const int MAX_CUSTOMERS = 5;
    
public:
    CustomerManager(Vector2 doorPos = {1270, 0}, Vector2 counterPos = {1200, 580})
        : doorPosition(doorPos), 
          counterWaitPosition(counterPos),
          customerSpacing(80.0f),
          spawnTimer(0.0f),
          spawnInterval(5.0f)
    {
    }
    
    ~CustomerManager()
    {
        for (auto* customer : activeCustomers)
        {
            delete customer->customer;
            delete customer;
        }
        activeCustomers.clear();
        
        // Cleanup image resources
        CustomerImageFactory::getInstance().cleanup();
    }
    
    void update(float deltaTime, bool storeOpen)
    {
        if (storeOpen && activeCustomers.size() < MAX_CUSTOMERS)
        {
            spawnTimer += deltaTime;
            
            if (spawnTimer >= spawnInterval)
            {
                spawnCustomer();
                spawnTimer = 0.0f;
            }
        }
        
        for (auto* custVisual : activeCustomers)
        {
            custVisual->update(deltaTime);
        }
        
        bool removedAny = false;
        activeCustomers.erase(
            std::remove_if(activeCustomers.begin(), activeCustomers.end(),
                [&removedAny](CustomerVisual* cv) {
                    if (!cv->isActive && cv->position.y <= -50) {
                        delete cv->customer;
                        delete cv;
                        removedAny = true;
                        return true;
                    }
                    return false;
                }),
            activeCustomers.end()
        );
        
        if (removedAny)
        {
            reorderQueue();
        }
    }
    
    void render() const
    {
        for (const auto* custVisual : activeCustomers)
        {
            custVisual->render();
            
            if (custVisual->customer && custVisual->isActive)
            {
                drawThoughtBubble(custVisual);
            }
        }
    }
    
    void spawnCustomer()
    {
        if (activeCustomers.size() >= MAX_CUSTOMERS) return;
        
        Plant* requestedPlant = plantFactory.produce();
        Customer* newCustomer = customerFactory.create(requestedPlant);
        
        CustomerVisual* custVisual = new CustomerVisual(newCustomer, doorPosition);
        
        Vector2 targetPos = calculateQueuePosition(activeCustomers.size());
        custVisual->moveTo(targetPos);
        
        activeCustomers.push_back(custVisual);
    }
    
    CustomerVisual* getClickedCustomer(Vector2 mousePos)
    {
        for (auto* custVisual : activeCustomers)
        {
            if (custVisual->isActive && custVisual->isHovered(mousePos))
            {
                return custVisual;
            }
        }
        return nullptr;
    }
    
    bool serveCustomer(CustomerVisual* custVisual, const std::string& plantType)
    {
        if (!custVisual || !custVisual->customer) return false;
        
        if (!custVisual->customer->getRequestedPlant()) return false;
        
        if (custVisual->customer->getRequestedPlant()->getType() == plantType)
        {
            Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100};
            custVisual->moveTo(exitPosition);
            custVisual->isActive = false;
            return true;
        }
        
        return false;
    }
    
    void dismissCustomer(CustomerVisual* custVisual)
    {
        if (!custVisual) return;
        
        Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100};
        custVisual->moveTo(exitPosition);
        custVisual->isActive = false;
    }
    
    int getCustomerCount() const
    {
        return activeCustomers.size();
    }
    
    void setSpawnInterval(float interval)
    {
        spawnInterval = interval;
    }
    
private:
    Vector2 calculateQueuePosition(int queueIndex)
    {
        float startX = 920.0f;
        return {
            startX + (queueIndex * customerSpacing),
            counterWaitPosition.y
        };
    }
    
    void reorderQueue()
    {
        int activeIndex = 0;
        for (auto* custVisual : activeCustomers)
        {
            if (custVisual->isActive)
            {
                Vector2 newPos = calculateQueuePosition(activeIndex);
                custVisual->moveTo(newPos);
                activeIndex++;
            }
        }
    }
    
    void drawThoughtBubble(const CustomerVisual* custVisual) const
    {
        if (!custVisual->customer) return;
        
        Plant* requestedPlant = custVisual->customer->getRequestedPlant();
        if (!requestedPlant) return;
        
        Vector2 bubblePos = {
            custVisual->position.x,
            custVisual->position.y - 60
        };
        
        DrawCircle(bubblePos.x, bubblePos.y, 25, WHITE);
        DrawCircle(bubblePos.x - 10, bubblePos.y + 15, 10, WHITE);
        DrawCircle(bubblePos.x - 15, bubblePos.y + 25, 5, WHITE);
        
        DrawCircleLines(bubblePos.x, bubblePos.y, 25, BLACK);
        DrawCircleLines(bubblePos.x - 10, bubblePos.y + 15, 10, BLACK);
        DrawCircleLines(bubblePos.x - 15, bubblePos.y + 25, 5, BLACK);
        
        std::string plantName = requestedPlant->getType();
        int textWidth = MeasureText(plantName.c_str(), 12);
        DrawText(plantName.c_str(), 
                bubblePos.x - textWidth/2, 
                bubblePos.y - 6, 
                12, BLACK);
    }
};

#endif
