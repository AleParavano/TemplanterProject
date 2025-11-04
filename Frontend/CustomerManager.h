#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "raylib.h"
#include "CustomerVisual.h" // Assumes this includes CustomerFlyweight.h or is accessible
#include "../Backend/CustomerFactory.h" // Assumes RandomFactory is defined here
#include "../Backend/PlantFactory.h" // Assumes RandomPlantFactory and Plant are defined here
#include <vector>
#include <algorithm>

/**
 * @class CustomerManager
 * @brief Manages the lifecycle, spawning, movement, queuing, and rendering of all active customers in the game.
 *
 * This class orchestrates the customer experience, from spawning them via factories to handling their serving 
 * or dismissal, and maintaining their visual queue order.
 */
class CustomerManager
{
private:
    /** @brief Collection of active customers currently in the game world. */
    std::vector<CustomerVisual *> activeCustomers;

    /** @brief Factory responsible for creating random Customer objects (includes concrete Customer type and logic). */
    RandomFactory customerFactory;
    
    /** @brief Factory responsible for creating random Plant objects (the request). */
    RandomPlantFactory plantFactory;

    /** @brief The entry/exit point for customers. */
    Vector2 doorPosition;
    
    /** @brief The base position where the customer queue begins. */
    Vector2 counterWaitPosition;
    
    /** @brief The horizontal distance between customers in the queue. */
    float customerSpacing;
    
    /** @brief Timer to track time until the next customer spawns. */
    float spawnTimer;
    
    /** @brief The required time delay between customer spawns. */
    float spawnInterval;

    /** @brief The maximum number of customers allowed in the game at any time. */
    const int MAX_CUSTOMERS = 5;

public:
    /**
     * @brief Constructor. Initializes positions and timing variables.
     * @param doorPos The position where customers enter/exit. Defaults to {1270, 0}.
     * @param counterPos The position near the counter where the queue waits. Defaults to {1200, 580}.
     */
    CustomerManager(Vector2 doorPos = {1270, 0}, Vector2 counterPos = {1200, 580})
        : doorPosition(doorPos),
          counterWaitPosition(counterPos),
          customerSpacing(80.0f),
          spawnTimer(0.0f),
          spawnInterval(5.0f)
    {
    }

    /**
     * @brief Destructor. Cleans up all dynamic memory allocated for Customer and CustomerVisual objects.
     *
     * Also calls the cleanup function on the singleton CustomerImageFactory to unload textures.
     */
    ~CustomerManager()
    {
        for (auto *customer : activeCustomers)
        {
            // Delete the customer object managed by the visual component
            delete customer->customer; 
            // Delete the visual component itself
            delete customer;
        }
        activeCustomers.clear();

        // Cleanup shared flyweight image resources
        CustomerImageFactory::getInstance().cleanup();
    }

    /**
     * @brief Updates the state of the CustomerManager and all active customers.
     *
     * Handles customer spawning, customer movement updates, and removal of inactive customers.
     * @param deltaTime The time elapsed since the last frame.
     * @param storeOpen A flag indicating if new customers should be spawned.
     */
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

        // Update all active customer visuals (movement, etc.)
        for (auto *custVisual : activeCustomers)
        {
            custVisual->update(deltaTime);
        }

        // Remove customers that have finished their exit movement
        bool removedAny = false;
        activeCustomers.erase(
            std::remove_if(activeCustomers.begin(), activeCustomers.end(),
                           [&removedAny](CustomerVisual *cv)
                           {
                               // Check if the customer is inactive (served/dismissed) and has moved off-screen
                               if (!cv->isActive && cv->position.y <= -50)
                               {
                                   delete cv->customer; // Delete the core customer logic object
                                   delete cv;           // Delete the visual wrapper object
                                   removedAny = true;
                                   return true;
                               }
                               return false;
                           }),
            activeCustomers.end());

        // Reorder the queue if any customer was removed
        if (removedAny)
        {
            reorderQueue();
        }
    }

    /**
     * @brief Renders all active customers and their thought bubbles.
     */
    void render() const
    {
        for (const auto *custVisual : activeCustomers)
        {
            custVisual->render();

            if (custVisual->customer && custVisual->isActive)
            {
                drawThoughtBubble(custVisual);
            }
        }
    }

    /**
     * @brief Creates a new random customer and adds them to the queue.
     *
     * A new requested Plant is generated, a new Customer logic object is created, 
     * and finally a CustomerVisual wrapper is created and added to the list.
     */
    void spawnCustomer()
    {
        if (activeCustomers.size() >= MAX_CUSTOMERS)
            return;

        Plant *requestedPlant = plantFactory.produce();
        Customer *newCustomer = customerFactory.create(requestedPlant);

        CustomerVisual *custVisual = new CustomerVisual(newCustomer, doorPosition);

        Vector2 targetPos = calculateQueuePosition(activeCustomers.size());
        custVisual->moveTo(targetPos);

        activeCustomers.push_back(custVisual);
    }

    /**
     * @brief Checks if a customer is clicked/hovered at the given mouse position.
     * @param mousePos The current position of the mouse.
     * @return A pointer to the active CustomerVisual if clicked, otherwise nullptr.
     */
    CustomerVisual *getClickedCustomer(Vector2 mousePos)
    {
        for (auto *custVisual : activeCustomers)
        {
            if (custVisual->isActive && custVisual->isHovered(mousePos))
            {
                return custVisual;
            }
        }
        return nullptr;
    }

    /**
     * @brief Sets all currently active customers to an inactive (dismissed/leaving) state and sends them toward the exit.
     */
   void dismissAllCustomers()
    {
        for (auto *custVisual : activeCustomers)
        {
            if (custVisual && custVisual->isActive)
            {
                Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100};
                custVisual->moveTo(exitPosition);
                custVisual->isActive = false; // Flag customer for removal in next update
            }
        }
    }

    /**
     * @brief Attempts to serve a customer with a plant of the specified type.
     * @param custVisual The customer being served.
     * @param plantType The type of the plant being offered.
     * @return true if the plant matches the customer's request and they are served/dismissed, false otherwise.
     */
    bool serveCustomer(CustomerVisual *custVisual, const std::string &plantType)
    {
        if (!custVisual || !custVisual->customer)
            return false;

        if (!custVisual->customer->getRequestedPlant())
            return false;

        // Check if the plant type matches the request
        if (custVisual->customer->getRequestedPlant()->getType() == plantType)
        {
            // Success: Move customer to exit and mark inactive
            Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100};
            custVisual->moveTo(exitPosition);
            custVisual->isActive = false;
            return true;
        }

        return false;
    }

    /**
     * @brief Forces a customer to leave (dismissal).
     * @param custVisual The customer to dismiss.
     */
    void dismissCustomer(CustomerVisual *custVisual)
    {
        if (!custVisual)
            return;

        Vector2 exitPosition = {doorPosition.x, doorPosition.y - 100};
        custVisual->moveTo(exitPosition);
        custVisual->isActive = false;
    }

    /**
     * @brief Gets the current number of active customers.
     * @return The count of customers in the `activeCustomers` vector.
     */
    int getCustomerCount() const
    {
        return activeCustomers.size();
    }

    /**
     * @brief Sets the time interval between customer spawns.
     * @param interval The new spawn interval in seconds.
     */
    void setSpawnInterval(float interval)
    {
        spawnInterval = interval;
    }

private:
    /**
     * @brief Calculates the target position for a customer based on their index in the queue.
     * @param queueIndex The zero-based index of the customer in the queue.
     * @return The calculated world position for the customer.
     */
    Vector2 calculateQueuePosition(int queueIndex)
    {
        float startX = 920.0f;
        return {
            startX + (queueIndex * customerSpacing),
            counterWaitPosition.y};
    }

    /**
     * @brief Re-calculates and sets the target positions for all remaining active customers to maintain a tight queue.
     */
    void reorderQueue()
    {
        int activeIndex = 0;
        for (auto *custVisual : activeCustomers)
        {
            if (custVisual->isActive)
            {
                Vector2 newPos = calculateQueuePosition(activeIndex);
                custVisual->moveTo(newPos);
                activeIndex++;
            }
        }
    }

    /**
     * @brief Renders a simple thought bubble above the customer showing their requested plant type.
     * @param custVisual The customer visual object to draw the bubble for.
     */
    void drawThoughtBubble(const CustomerVisual *custVisual) const
    {
        if (!custVisual->customer)
            return;

        Plant *requestedPlant = custVisual->customer->getRequestedPlant();
        if (!requestedPlant)
            return;

        Vector2 bubblePos = {
            custVisual->position.x,
            custVisual->position.y - 60};

        // Draw the main bubble circle and tail circles (raylib drawing)
        DrawCircle(bubblePos.x, bubblePos.y, 25, WHITE);
        DrawCircle(bubblePos.x - 10, bubblePos.y + 15, 10, WHITE);
        DrawCircle(bubblePos.x - 15, bubblePos.y + 25, 5, WHITE);

        // Draw outlines
        DrawCircleLines(bubblePos.x, bubblePos.y, 25, BLACK);
        DrawCircleLines(bubblePos.x - 10, bubblePos.y + 15, 10, BLACK);
        DrawCircleLines(bubblePos.x - 15, bubblePos.y + 25, 5, BLACK);

        // Draw the requested plant type text
        std::string plantName = requestedPlant->getType();
        int textWidth = MeasureText(plantName.c_str(), 12);
        DrawText(plantName.c_str(),
                 bubblePos.x - textWidth / 2,
                 bubblePos.y - 6,
                 12, BLACK);
    }
};

#endif