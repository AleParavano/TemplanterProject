#include "CustomerFactory.h"
#include <array>
#include <functional>
#include <random>

Customer* RegularFactory::create(Plant* requestedPlant) const 
{
    return new Regular(requestedPlant);
}

Customer* VIPFactory::create(Plant* requestedPlant) const 
{
    return new VIP(requestedPlant);
}

Customer* RobberFactory::create(Plant* requestedPlant) const 
{
    return new Robber(requestedPlant);
}

std::mt19937& RandomFactory::rng() 
{
    static std::mt19937 engine{ std::random_device{}() };
    return engine;
}

Customer* RandomFactory::create(Plant* requestedPlant) const 
{
    std::uniform_int_distribution<int> dist(0, 2);

    switch (dist(rng())) 
    {
        case 0:  return new Regular(requestedPlant);
        case 1:  return new VIP(requestedPlant);
        default: return new Robber(requestedPlant);
    }
}
