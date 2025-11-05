#pragma once

#include "raylib.h"
#include <string>
#include <memory>
#include <unordered_map>

// Flyweight: Shared image resource for each customer type
class CustomerImage 
{
public:
    Texture2D texture;
    std::string customerType;
    
    CustomerImage(const std::string& type, const std::string& imagePath)
        : customerType(type)
    {
        // Load texture from assets folder
        texture = LoadTexture(imagePath.c_str());
    }
    
    ~CustomerImage()
    {
        if (texture.id != 0)
        {
            UnloadTexture(texture);
        }
    }
    
    // Delete copy operations - textures shouldn't be copied
    CustomerImage(const CustomerImage&) = delete;
    CustomerImage& operator=(const CustomerImage&) = delete;
    
    void render(Vector2 position, float radius) const
    {
        if (texture.id == 0) return;
        
        // Draw texture centered at position, scaled to radius size
        float scale = (radius * 2.0f) / texture.width;
        DrawTextureEx(texture, 
                     {position.x - radius, position.y - radius},
                     0.0f,
                     scale,
                     WHITE);
    }
};

// Singleton factory that manages shared flyweight images
class CustomerImageFactory 
{
public:
    static CustomerImageFactory& getInstance();
    
    // Get shared flyweight image - loads once, reuses for all instances
    std::shared_ptr<CustomerImage> getImage(const std::string& customerType);
    
    // Render customer using shared flyweight
    void renderCustomer(const std::string& customerType, Vector2 position, float radius);
    
    // Cleanup all loaded textures
    void cleanup();
    
private:
    CustomerImageFactory() = default;
    std::unordered_map<std::string, std::shared_ptr<CustomerImage>> images;
    
    // Map customer types to asset file paths
    std::string getAssetPath(const std::string& customerType);
};
