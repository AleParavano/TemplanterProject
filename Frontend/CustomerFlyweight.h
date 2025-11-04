#pragma once

#include "raylib.h"
#include <string>
#include <memory>
#include <unordered_map>

/**
 * @class CustomerImage
 * @brief Flyweight class: Represents the **Extrinsic** state (shared data) 
 * of a customer, specifically the image (Texture2D) associated with
 * a particular customer type.
 *
 * This class acts as the **Flyweight**. Instances of this class are shared 
 * across many `Customer` objects of the same type, saving memory by loading 
 * and storing the image texture only once.
 */
class CustomerImage 
{
public:
    /** @brief The raylib texture representing the customer type's image. */
    Texture2D texture;
    
    /** @brief The type of the customer (e.g., "Standard", "Premium"). 
     * This is part of the **Intrinsic** state. 
     */
    std::string customerType;
    
    /**
     * @brief Constructor. Loads the texture from the specified file path.
     * @param type The string identifier for the customer type.
     * @param imagePath The file path to the image asset.
     */
    CustomerImage(const std::string& type, const std::string& imagePath)
        : customerType(type)
    {
        // Load texture from assets folder
        texture = LoadTexture(imagePath.c_str());
    }
    
    /**
     * @brief Destructor. Unloads the raylib texture resource if it was loaded.
     */
    ~CustomerImage()
    {
        if (texture.id != 0)
        {
            UnloadTexture(texture);
        }
    }
    
    /// @cond
    // Delete copy operations - textures shouldn't be copied
    CustomerImage(const CustomerImage&) = delete;
    CustomerImage& operator=(const CustomerImage&) = delete;
    /// @endcond
    
    /**
     * @brief Renders the customer image at a given position and size.
     * @param position The center coordinates (x, y) where the image should be drawn.
     * @param radius The radius defining the size/scale of the image.
     */
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

/**
 * @class CustomerImageFactory
 * @brief Singleton factory that manages and provides shared CustomerImage flyweights.
 *
 * Implements the **Flyweight Factory** part of the pattern, ensuring that 
 * for any given customer type, only one `CustomerImage` object (flyweight) 
 * is created and reused.
 */
class CustomerImageFactory 
{
public:
    /**
     * @brief Gets the singleton instance of the factory.
     * @return A reference to the single CustomerImageFactory instance.
     */
    static CustomerImageFactory& getInstance();
    
    /**
     * @brief Retrieves the shared flyweight image for a given customer type.
     *
     * If the image for the specified type hasn't been created yet, it loads 
     * it, stores it, and returns it. Otherwise, it returns the existing shared instance.
     * @param customerType The type of the customer (e.g., "Standard").
     * @return A shared pointer to the CustomerImage flyweight.
     */
    std::shared_ptr<CustomerImage> getImage(const std::string& customerType);
    
    /**
     * @brief Convenience function to render a customer using the shared flyweight.
     * @param customerType The type of the customer to render.
     * @param position The center position for rendering.
     * @param radius The size/scale for rendering.
     */
    void renderCustomer(const std::string& customerType, Vector2 position, float radius);
    
    /**
     * @brief Cleans up all loaded textures managed by the factory.
     *
     * Should be called upon application shutdown or when textures are no longer needed.
     */
    void cleanup();
    
private:
    /**
     * @brief Private default constructor to enforce the Singleton pattern.
     */
    CustomerImageFactory() = default;
    
    /** @brief Map storing the shared CustomerImage flyweights, keyed by customer type. */
    std::unordered_map<std::string, std::shared_ptr<CustomerImage>> images;
    
    /**
     * @brief Maps a customer type string to its corresponding asset file path.
     *
     * **NOTE:** The implementation of this function must be provided in the .cpp file.
     * @param customerType The type of the customer.
     * @return The string path to the image file.
     */
    std::string getAssetPath(const std::string& customerType);
};

// Note: If this file is intended to be included in a namespace, 
// the closing brace for that namespace is missing at the end.