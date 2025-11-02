#include "CustomerFactory.h"
#include <array>
#include <functional>
#include <random>

CustomerFactory::~CustomerFactory() {}

Customer *RegularFactory::create(Plant *requestedPlant) const
{
    return new Regular(requestedPlant);
}

Customer *VIPFactory::create(Plant *requestedPlant) const
{
    return new VIP(requestedPlant);
}

Customer *RobberFactory::create(Plant *requestedPlant) const
{
    return new Robber(requestedPlant);
}

std::mt19937 &RandomFactory::rng()
{
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

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
