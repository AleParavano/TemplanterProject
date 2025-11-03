#ifndef CUSTOMERVISUAL_H
#define CUSTOMERVISUAL_H

#include "raylib.h"
#include "../Backend/Customer.h"
#include "CustomerFlyweight.h"

struct CustomerVisual
{
    Customer* customer;
    Vector2 position;
    float radius;
    
    // Animation/movement
    Vector2 targetPosition;
    float speed;
    bool isMoving;
    
    // Interaction
    Rectangle interactionZone;
    bool isActive;
    
    CustomerVisual(Customer* cust, Vector2 pos, float rad = 30.0f)
        : customer(cust), position(pos), radius(rad), speed(50.0f), 
          isMoving(false), isActive(true)
    {
        targetPosition = position;
        updateInteractionZone();
    }
    
    void update(float deltaTime)
    {
        if(isMoving) {
            Vector2 direction = {
                targetPosition.x - position.x,
                targetPosition.y - position.y
            };
            
            float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
            
            if(distance < 2.0f) {
                position = targetPosition;
                isMoving = false;
            } else {
                direction.x /= distance;
                direction.y /= distance;
                
                position.x += direction.x * speed * deltaTime;
                position.y += direction.y * speed * deltaTime;
            }
        }
        
        updateInteractionZone();
    }
    
    void render() const
    {
        if (!customer) return;
        
        // Render customer image using Flyweight factory
        auto& imageFactory = CustomerImageFactory::getInstance();
        std::string custType = customer->type();
        imageFactory.renderCustomer(custType, position, radius);
    }
    
    void moveTo(Vector2 target)
    {
        targetPosition = target;
        isMoving = true;
    }
    
    bool canInteract(Vector2 playerPos) const
    {
        return isActive && CheckCollisionPointRec(playerPos, interactionZone);
    }
    
    bool isHovered(Vector2 mousePos) const
    {
        return CheckCollisionPointCircle(mousePos, position, radius);
    }
    
private:
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
