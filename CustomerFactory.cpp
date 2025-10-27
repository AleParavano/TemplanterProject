#include "CustomerFactory.h"
#include <array>
#include <functional>

std::unique_ptr<Customer> RegularFactory::create(Plant* requestedPlant) const 
{
    return std::make_unique<Regular>(requestedPlant);
}

std::unique_ptr<Customer> VIPFactory::create(Plant* requestedPlant) const 
{
    return std::make_unique<VIP>(requestedPlant);
}

std::unique_ptr<Customer> RobberFactory::create(Plant* requestedPlant) const 
{
    return std::make_unique<Robber>(requestedPlant);
}

std::mt19937& RandomFactory::rng() 
{
    static std::mt19937 engine
    { 
        std::random_device{}() 
    };
    return engine;
}

std::unique_ptr<Customer> RandomFactory::create(Plant* requestedPlant) const 
{
    std::uniform_int_distribution<int> dist(0, 2);
    switch (dist(rng())) 
    {
        case 0:  return std::make_unique<Regular>(requestedPlant);
        case 1:  return std::make_unique<VIP>(requestedPlant);
        default: return std::make_unique<Robber>(requestedPlant);
    }
}
