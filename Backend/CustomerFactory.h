#pragma once

#include <random>
#include "Customer.h"

class CustomerFactory 
{
public:
    virtual ~CustomerFactory();
    virtual Customer* create(Plant* requestedPlant) const = 0;
};

class RegularFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

class VIPFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

class RobberFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

class RandomFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;

    private:
    static std::mt19937& rng();
};
