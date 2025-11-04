/**
 * @file CustomerFactory.h
 * @brief Factory pattern implementation for creating customer objects.
 * @details Provides factories to create different types of customers: Regular, VIP, and Robber.
 *          Includes a RandomFactory for dynamic customer type generation based on probabilities.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see Customer
 * @see Regular
 * @see VIP
 * @see Robber
 */

#pragma once

#include <random>
#include "Customer.h"

/**
 * @class CustomerFactory
 * @brief Abstract base class for customer factories.
 * 
 * Defines the interface for creating customer objects of various types.
 * Each concrete factory specializes in creating a specific customer type.
 * 
 * @par Design Pattern: Factory
 * Encapsulates object creation logic, allowing subclasses to specify the exact
 * type of customer to create. This promotes loose coupling and code reusability.
 * 
 * @see RegularFactory
 * @see VIPFactory
 * @see RobberFactory
 * @see RandomFactory
 */
class CustomerFactory 
{
public:
    /**
     * @brief Virtual destructor.
     * @details Ensures proper cleanup of derived factory objects.
     */
    virtual ~CustomerFactory();

    /**
     * @brief Creates a customer object.
     * @param requestedPlant Pointer to the Plant that the customer is interested in.
     * @return Pointer to a newly allocated Customer object.
     * 
     * @details The exact type of customer created depends on the concrete factory class.
     * @note The caller is responsible for deleting the returned customer object.
     */
    virtual Customer* create(Plant* requestedPlant) const = 0;
};

/**
 * @class RegularFactory
 * @brief Factory for creating Regular customer objects.
 * 
 * Creates instances of Regular customers, which are the standard customer type
 * with typical purchasing behavior and ratings.
 * 
 * @see Regular
 */
class RegularFactory : public CustomerFactory 
{
public:
    /**
     * @brief Creates a Regular customer.
     * @param requestedPlant Pointer to the Plant the customer wants to purchase.
     * @return Pointer to a newly allocated Regular customer object.
     * 
     * @note The customer is created with the specified plant as their purchase target.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class VIPFactory
 * @brief Factory for creating VIP customer objects.
 * 
 * Creates instances of VIP customers, which are premium customers with special
 * benefits such as higher ratings for good service or better purchasing power.
 * 
 * @see VIP
 */
class VIPFactory : public CustomerFactory 
{
public:
    /**
     * @brief Creates a VIP customer.
     * @param requestedPlant Pointer to the Plant the customer wants to purchase.
     * @return Pointer to a newly allocated VIP customer object.
     * 
     * @note The customer is created with the specified plant as their purchase target.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RobberFactory
 * @brief Factory for creating Robber customer objects.
 * 
 * Creates instances of Robber customers, which attempt to steal plants from
 * the inventory instead of purchasing them. They represent a gameplay challenge
 * that requires player vigilance or worker patrols.
 * 
 * @see Robber
 */
class RobberFactory : public CustomerFactory 
{
public:
    /**
     * @brief Creates a Robber customer.
     * @param requestedPlant Pointer to the Plant the customer wants to steal.
     * @return Pointer to a newly allocated Robber customer object.
     * 
     * @note The customer is created with the specified plant as their theft target.
     */
    Customer* create(Plant* requestedPlant) const override;
};

/**
 * @class RandomFactory
 * @brief Factory for creating customers with random types based on probabilities.
 * 
 * Creates customer objects with randomly selected types according to the following
 * probability distribution:
 * - Regular: 85% probability
 * - VIP: 10% probability (85-95%)
 * - Robber: 5% probability (95-100%)
 * 
 * @par Randomness
 * Uses C++ std::mt19937 (Mersenne Twister) PRNG with a static instance for
 * consistent random behavior across multiple calls.
 * 
 * @par Thread Safety
 * The static RNG is created once and reused. This implementation is not
 * thread-safe for concurrent calls.
 * 
 * @example
 * @code
 * RandomFactory factory;
 * Customer* customer = factory.create(plant);
 * 
 * // customer could be Regular (85%), VIP (10%), or Robber (5%)
 * std::string type = customer->type();
 * @endcode
 * 
 * @see Regular
 * @see VIP
 * @see Robber
 */
class RandomFactory : public CustomerFactory 
{
public:
    /**
     * @brief Creates a customer with random type based on probabilities.
     * @param requestedPlant Pointer to the Plant to assign to the customer.
     * @return Pointer to a newly allocated customer of Random type.
     * 
     * @details Type distribution:
     *         - Probability [0-85]: Regular customer
     *         - Probability [86-95]: VIP customer
     *         - Probability [96-100]: Robber customer
     * 
     * @note Each call generates a new random value for type selection.
     */
    Customer* create(Plant* requestedPlant) const override;

private:
    /**
     * @brief Gets the static random number generator instance.
     * @return Reference to the static Mersenne Twister engine.
     * 
     * @details Creates the RNG on first call and returns the same instance for
     *         all subsequent calls. Seeded with std::random_device for variation.
     */
    static std::mt19937& rng();
};