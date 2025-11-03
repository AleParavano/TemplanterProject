/**
 * @file CustomerFactory.h
 * @brief Declaration of factory classes for creating customers.
 * 
 * This file defines the abstract CustomerFactory and concrete factory implementations
 * for creating different types of customers. The RandomFactory provides weighted
 * random customer generation for realistic nursery simulation.
 * 
 * @pattern Factory - Abstract factory for customer creation
 */

#pragma once

#include <random>
#include "Customer.h"

/**
 * @class CustomerFactory
 * @brief Abstract factory for creating Customer objects.
 * 
 * Defines the interface for customer creation. Concrete factories implement
 * the create() method to instantiate specific customer types.
 * 
 * @pattern Factory - Abstract factory interface
 */
class CustomerFactory 
{
public:
    virtual ~CustomerFactory();
    virtual Customer* create(Plant* requestedPlant) const = 0;
};

/**
 * @class RegularFactory
 * @brief Factory for creating Regular customers.
 * 
 * Concrete factory that creates standard customers with normal behavior.
 * 
 * @pattern Factory - Concrete factory
 */
class RegularFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class VIPFactory
 * @brief Factory for creating VIP customers.
 * 
 * Concrete factory that creates high-value customers with premium expectations.
 * 
 * @pattern Factory - Concrete factory
 */
class VIPFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RobberFactory
 * @brief Factory for creating Robber customers.
 * 
 * Concrete factory that creates malicious customers who attempt theft.
 * 
 * @pattern Factory - Concrete factory
 */
class RobberFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RandomFactory
 * @brief Factory for creating random customers with weighted distribution.
 * 
 * Uses probability-based selection to create customers:
 * - 85% Regular
 * - 10% VIP
 * - 5% Robber
 * 
 * This provides realistic customer variety in the simulation.
 * 
 * @pattern Factory - Concrete factory with random selection
 */
class RandomFactory : public CustomerFactory 
{
    public:
    Customer* create(Plant* requestedPlant) const override;

    private:
    static std::mt19937& rng();
};
