/**
 * @file CustomerFactory.cpp
 * @brief Implementation of CustomerFactory concrete classes.
 * 
 * This file implements various factory classes that create different types of customers.
 * The RandomFactory uses weighted probabilities to simulate realistic customer distribution
 * in the nursery (85% Regular, 10% VIP, 5% Robber).
 * 
 * @pattern Factory - Creates customer objects based on type
 */

#include "CustomerFactory.h"
#include <array>
#include <functional>
#include <random>

/**
 * @brief Virtual destructor for CustomerFactory.
 * 
 * Ensures proper cleanup of derived factory classes.
 */
CustomerFactory::~CustomerFactory(){}

/**
 * @brief Creates a Regular customer.
 * 
 * Factory method that instantiates a Regular customer requesting the specified plant.
 * 
 * @param requestedPlant Pointer to the plant the customer wants
 * @return Customer* Pointer to the newly created Regular customer
 */
Customer *RegularFactory::create(Plant *requestedPlant) const
{
    return new Regular(requestedPlant);
}

/**
 * @brief Creates a VIP customer.
 * 
 * Factory method that instantiates a VIP customer requesting the specified plant.
 * 
 * @param requestedPlant Pointer to the plant the customer wants
 * @return Customer* Pointer to the newly created VIP customer
 */
Customer *VIPFactory::create(Plant *requestedPlant) const
{
    return new VIP(requestedPlant);
}

/**
 * @brief Creates a Robber customer.
 * 
 * Factory method that instantiates a Robber customer requesting the specified plant.
 * 
 * @param requestedPlant Pointer to the plant the customer wants
 * @return Customer* Pointer to the newly created Robber customer
 */
Customer *RobberFactory::create(Plant *requestedPlant) const
{
    return new Robber(requestedPlant);
}

/**
 * @brief Provides a static random number generator.
 * 
 * Returns a reference to a static Mersenne Twister RNG initialized with
 * a random seed. This ensures consistent random behavior across all
 * RandomFactory instances.
 * 
 * @return std::mt19937& Reference to the static random number generator
 */
std::mt19937 &RandomFactory::rng()
{
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

/**
 * @brief Creates a random customer based on weighted probabilities.
 * 
 * Factory method that randomly creates a Regular (85%), VIP (10%), or Robber (5%)
 * customer requesting the specified plant. Uses a uniform distribution to
 * determine the customer type.
 * 
 * @param requestedPlant Pointer to the plant the customer wants
 * @return Customer* Pointer to the newly created customer of random type
 */
Customer *RandomFactory::create(Plant *requestedPlant) const
{
    std::uniform_int_distribution<int> dist(0, 100);
    int randomValue = dist(rng());  

    if (randomValue <= 85)  
    {
        return new Regular(requestedPlant);
    }
    else if(randomValue <= 95)  
    {
        return new VIP(requestedPlant);
    }
    else  
    {
        return new Robber(requestedPlant);
    }
}
