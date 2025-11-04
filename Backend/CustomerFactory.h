#pragma once

#include <random>
#include "Customer.h"

/**
 * @class CustomerFactory
 * @brief The abstract base class for creating different types of Customer objects.
 * * This implements the Factory Method design pattern.
 */
class CustomerFactory 
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived factory objects.
     */
    virtual ~CustomerFactory();
    
    /**
     * @brief Pure virtual method to create a new Customer object.
     * @param requestedPlant The Plant object the new Customer will be interested in.
     * @return A pointer to the newly created Customer object.
     */
    virtual Customer* create(Plant* requestedPlant) const = 0;
};

// --- Concrete Factory Implementations ---

/**
 * @class RegularFactory
 * @brief A concrete factory that specializes in creating Regular Customer objects.
 */
class RegularFactory : public CustomerFactory 
{
    public:
    /**
     * @brief Creates a new Regular Customer.
     * @param requestedPlant The plant the customer is interested in.
     * @return A pointer to a new Regular object.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class VIPFactory
 * @brief A concrete factory that specializes in creating VIP Customer objects.
 */
class VIPFactory : public CustomerFactory 
{
    public:
    /**
     * @brief Creates a new VIP Customer.
     * @param requestedPlant The plant the customer is interested in.
     * @return A pointer to a new VIP object.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RobberFactory
 * @brief A concrete factory that specializes in creating Robber Customer objects.
 */
class RobberFactory : public CustomerFactory 
{
    public:
    /**
     * @brief Creates a new Robber Customer.
     * @param requestedPlant The plant the robber is targeting.
     * @return A pointer to a new Robber object.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RandomFactory
 * @brief A concrete factory that creates a random type of Customer (Regular, VIP, or Robber).
 */
class RandomFactory : public CustomerFactory 
{
    public:
    /**
     * @brief Creates a random Customer type.
     * @param requestedPlant The plant the customer is interested in.
     * @return A pointer to a randomly selected concrete Customer object.
     */
    Customer* create(Plant* requestedPlant) const override;

    private:
    /**
     * @brief Provides access to the static random number generator engine.
     * @return A reference to the initialized std::mt19937 engine.
     */
    static std::mt19937& rng();
};