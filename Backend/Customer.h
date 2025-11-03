/**
 * @file Customer.h
 * @brief Declaration of Customer hierarchy for nursery visitors.
 * 
 * This file defines the Customer base class and concrete customer types (Regular, VIP, Robber).
 * Customers visit the nursery to request specific plants, and their type affects their
 * behavior and impact on the player's rating.
 * 
 * @pattern Visitor - Customers evaluate plants and provide ratings
 * @pattern Factory - Created by CustomerFactory implementations
 */
#pragma once

#include <string>

class Plant;

/**
 * @class Customer
 * @brief Abstract base class representing a customer visiting the nursery.
 * 
 * Customers request specific plants and have different behaviors based on their type.
 * Each customer type affects the player's rating differently when served (or not served).
 * 
 * @pattern Visitor - Evaluates and interacts with plants
 */
class Customer 
{
    public:
    /**
     * @brief Constructs a Customer requesting a specific plant.
     * 
     * @param requestedPlant Pointer to the plant this customer wants to purchase
     */
    Customer(Plant* requestedPlant) : requestedPlant(requestedPlant) {}
    virtual ~Customer() = default;
    /**
     * @brief Returns the type identifier of this customer.
     * 
     * @return std::string The customer type ("Regular", "VIP", or "Robber")
     */
    virtual std::string type() const = 0;
    void setRequestedPlant(Plant* p) { requestedPlant = p; }
    /**
     * @brief Gets the plant this customer is requesting.
     * 
     * @return Plant* Pointer to the requested plant
     */
    Plant* getRequestedPlant() const { return requestedPlant; }

    private:
    Plant* requestedPlant;
};

/**
 * @class Regular
 * @brief A standard customer with normal purchasing behavior.
 * 
 * Regular customers have standard expectations and moderately affect the
 * player's rating when their requests are fulfilled or denied.
 */
class Regular : public Customer 
{
    public:
    Regular(Plant* requestedPlant) : Customer(requestedPlant) {}
    std::string type() const override { return "Regular"; }
};

/**
 * @class VIP
 * @brief A high-value customer with premium expectations.
 * 
 * VIP customers significantly boost the player's rating when satisfied,
 * but cause a larger rating decrease when their requests cannot be fulfilled.
 */
class VIP : public Customer 
{
    public:
    VIP(Plant* requestedPlant): Customer(requestedPlant) {}
    std::string type() const override { return "VIP"; }
};

/**
 * @class Robber
 * @brief A malicious customer who attempts to steal plants.
 * 
 * Robbers negatively impact the player's rating if they successfully
 * steal a plant. They do not make legitimate purchases.
 */
class Robber : public Customer 
{
    public:
    Robber(Plant* requestedPlant) : Customer(requestedPlant) {}
    std::string type() const override { return "Robber"; }
};