#include "CustomerFlyweight.h"

CustomerImageFactory& CustomerImageFactory::getInstance() 
{
    static CustomerImageFactory instance;
    return instance;
}

std::string CustomerImageFactory::getAssetPath(const std::string& customerType)
{
    // Map customer types to image files in assets folder
    if (customerType == "Regular")
        return "Data/regular.png";
    else if (customerType == "VIP")
        return "Data/vip.png";
    else if (customerType == "Robber")
        return "Data/robber.png";
    
    return "Data/regular.png"; // Default fallback
}

std::shared_ptr<CustomerImage> CustomerImageFactory::getImage(const std::string& customerType) 
{
    // Return existing image if already loaded
    auto it = images.find(customerType);
    if (it != images.end()) 
    {
        return it->second;
    }
    
    // Load and cache new image
    std::string assetPath = getAssetPath(customerType);
    auto image = std::make_shared<CustomerImage>(customerType, assetPath);
    images[customerType] = image;
    
    return image;
}

void CustomerImageFactory::renderCustomer(const std::string& customerType, Vector2 position, float radius)
{
    auto image = getImage(customerType);
    if (image)
    {
        image->render(position, radius);
    }
}

void CustomerImageFactory::cleanup()
{
    images.clear(); // Textures unloaded via destructors
}
