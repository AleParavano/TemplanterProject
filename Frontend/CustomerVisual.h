// #ifndef CUSTOMERVISUAL_H
// #define CUSTOMERVISUAL_H

// #include "raylib.h"
// #include "../Backend/Customer.h"
// #include <string>
// #include <random>

// struct CustomerVisual
// {
//     Customer* customer;
//     Vector2 position;
//     float radius;
//     Color color;
//     std::string text;
    
//     // Animation/movement
//     Vector2 targetPosition;
//     float speed;
//     bool isMoving;
    
//     // Interaction
//     Rectangle interactionZone;
//     bool isActive;
    
//     CustomerVisual(Customer* cust, Vector2 pos, float rad = 30.0f)
//         : customer(cust), position(pos), radius(rad), speed(50.0f), isMoving(false), isActive(true)
//     {
//         // Fixed random number generation
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<> dist(0, 255);

//         int redRNG = dist(gen);
//         int greenRNG = dist(gen);
//         int blueRNG = dist(gen);
        
//         // Set color based on random generation
//         if(customer){
//             color = Color{static_cast<unsigned char>(redRNG), 
//                          static_cast<unsigned char>(greenRNG), 
//                          static_cast<unsigned char>(blueRNG), 255};

//             // Set text indicator based on customer type
//             if(customer->type() == "Regular"){
//                 text = "";
//             }
//             else if(customer->type() == "VIP"){
//                 text = "V";
//             }
//             else{
//                 text = "R";
//             }
//         }
        
//         targetPosition = position;
//         updateInteractionZone();
//     }
    
//     // Update customer visual (movement, animation)
//     void update(float deltaTime)
//     {
//         // Always update movement, even when inactive (so they can leave)
        
//         // Move towards target position
//         if(isMoving) {
//             Vector2 direction = {
//                 targetPosition.x - position.x,
//                 targetPosition.y - position.y
//             };
            
//             float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);
            
//             if(distance < 2.0f) {
//                 // Reached target
//                 position = targetPosition;
//                 isMoving = false;
//             } else {
//                 // Move towards target
//                 direction.x /= distance;
//                 direction.y /= distance;
                
//                 position.x += direction.x * speed * deltaTime;
//                 position.y += direction.y * speed * deltaTime;
//             }
//         }
        
//         updateInteractionZone();
//     }
    
//     // Render customer
//     void render() const
//     {
//         // Always render, even when inactive (so we can see them leaving)
        
//         // Draw main circle
//         DrawCircleV(position, radius, color);
        
//         // Draw outline
//         DrawCircleLines(position.x, position.y, radius, BLACK);
        
//         // Draw customer type indicator
//         if(customer && !text.empty()) {
//             int textWidth = MeasureText(text.c_str(), 20);
//             DrawText(text.c_str(), 
//                     position.x - textWidth/2, 
//                     position.y - 10, 
//                     20, WHITE);
//         }
//     }
    
//     // Move customer to target position
//     void moveTo(Vector2 target)
//     {
//         targetPosition = target;
//         isMoving = true;
//     }
    
//     // Check if player can interact
//     bool canInteract(Vector2 playerPos) const
//     {
//         return isActive && CheckCollisionPointRec(playerPos, interactionZone);
//     }
    
//     // Check if mouse is hovering over customer
//     bool isHovered(Vector2 mousePos) const
//     {
//         return CheckCollisionPointCircle(mousePos, position, radius);
//     }
    
// private:
//     void updateInteractionZone()
//     {
//         // Create interaction zone around customer
//         float zoneSize = radius * 3;
//         interactionZone = {
//             position.x - zoneSize/2,
//             position.y - zoneSize/2,
//             zoneSize,
//             zoneSize
//         };
//     }
// };

// #endif

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
