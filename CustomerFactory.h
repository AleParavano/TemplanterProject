#pragma once

#include <memory>
#include <random>
#include "Customer.h"

class CustomerFactory 
{
    public:
    virtual ~CustomerFactory() = default;
    virtual std::unique_ptr<Customer> create(Plant* requestedPlant = nullptr) const = 0;
};

class RegularFactory : public CustomerFactory 
{
    public:
    std::unique_ptr<Customer> create(Plant* requestedPlant = nullptr) const override;
};

class VIPFactory : public CustomerFactory 
{
    public:
    std::unique_ptr<Customer> create(Plant* requestedPlant = nullptr) const override;
};

class RobberFactory : public CustomerFactory 
{
    public:
    std::unique_ptr<Customer> create(Plant* requestedPlant = nullptr) const override;
};

class RandomFactory : public CustomerFactory {
    public:
    std::unique_ptr<Customer> create(Plant* requestedPlant = nullptr) const override;

private:
    static std::mt19937& rng();
};