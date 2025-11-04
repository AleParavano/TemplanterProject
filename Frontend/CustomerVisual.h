#ifndef CUSTOMERVISUAL_H
#define CUSTOMERVISUAL_H

#include "raylib.h"
#include "../Backend/Customer.h" // Assumes this defines the Customer class/interface
#include "CustomerFlyweight.h"    // Provides CustomerImageFactory and CustomerImage

/**
 * @struct CustomerVisual
 * @brief Represents the **Extrinsic** state of a customer in the Flyweight pattern context.
 *
 * This structure holds the unique, mutable data for a customer instance 
 * (position, movement, interaction status) and links to the shared intrinsic 
 * state (the CustomerImage flyweight) via the Customer object's type.
 */
struct CustomerVisual
{
    /** @brief Pointer to the core customer logic object (the domain model). */
    Customer* customer;
    
    /** @brief The current world position of the customer (center of the visual). */
    Vector2 position;
    
    /** @brief The radius used for rendering size and collision checks. */
    float radius;
    
    // Animation/movement
    /** @brief The target world position for movement. */
    Vector2 targetPosition;
    
    /** @brief The speed at which the customer moves (units per second). */
    float speed;
    
    /** @brief Flag indicating if the customer is currently moving towards the targetPosition. */
    bool isMoving;
    
    // Interaction
    /** @brief The rectangular area defining the interaction zone around the customer. */
    Rectangle interactionZone;
    
    /** @brief Flag indicating if the customer is active in the game (e.g., waiting in line, not dismissed). */
    bool isActive;
    
    /**
     * @brief Constructor for CustomerVisual.
     * @param cust A pointer to the associated Customer logic object.
     * @param pos The initial spawn position.
     * @param rad The visual radius of the customer. Defaults to 30.0f.
     */
    CustomerVisual(Customer* cust, Vector2 pos, float rad = 30.0f)
        : customer(cust), position(pos), radius(rad), speed(50.0f), 
          isMoving(false), isActive(true)
    {
        targetPosition = position;
        updateInteractionZone();
    }
    
    /**
     * @brief Updates the customer's state, primarily handling movement towards the target position.
     * @param deltaTime The time elapsed since the last frame.
     */
    void update(float deltaTime)
    {
        if(isMoving) {
            Vector2 direction = {
                targetPosition.x - position.x,
                targetPosition.y - position.y
            };
            
            float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
            
            if(distance < 2.0f) {
                // Arrived at target
                position = targetPosition;
                isMoving = false;
            } else {
                // Move towards target
                direction.x /= distance;
                direction.y /= distance;
                
                position.x += direction.x * speed * deltaTime;
                position.y += direction.y * speed * deltaTime;
            }
        }
        
        // Ensure the interaction zone reflects the current position
        updateInteractionZone();
    }
    
    /**
     * @brief Renders the customer using the shared CustomerImage flyweight based on the customer's type.
     */
    void render() const
    {
        if (!customer) return;
        
        // Render customer image using Flyweight factory
        auto& imageFactory = CustomerImageFactory::getInstance();
        std::string custType = customer->type();
        // The factory handles getting the shared flyweight and drawing its texture
        imageFactory.renderCustomer(custType, position, radius); 
    }
    
    /**
     * @brief Sets a new target position and starts the movement animation.
     * @param target The new target position (Vector2).
     */
    void moveTo(Vector2 target)
    {
        targetPosition = target;
        isMoving = true;
    }
    
    /**
     * @brief Checks if a player/mouse position is within the customer's larger interaction zone.
     * @param playerPos The position to check against the zone.
     * @return true if collision occurs and the customer is active, false otherwise.
     */
    bool canInteract(Vector2 playerPos) const
    {
        return isActive && CheckCollisionPointRec(playerPos, interactionZone);
    }
    
    /**
     * @brief Checks if the mouse position is hovering directly over the customer's visual circle.
     * @param mousePos The current mouse position.
     * @return true if the mouse is over the customer, false otherwise.
     */
    bool isHovered(Vector2 mousePos) const
    {
        return CheckCollisionPointCircle(mousePos, position, radius);
    }
    
private:
    /**
     * @brief Private helper function to recalculate the bounding box for the interaction zone.
     */
    void updateInteractionZone()
    {
        float zoneSize = radius * 3;
        interactionZone = {
            position.x - zoneSize/2,
            position.y - zoneSize/2,
            zoneSize,
            zoneSize
        };
    }
};

#endif