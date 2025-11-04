/**
 * @file Customer.h
 * @brief Customer class hierarchy for the nursery simulation.
 * @details Defines customer types: Regular (buyers), VIP (premium buyers), and Robber (thieves).
 *          Uses the Factory pattern for creation.
 * 
 * @author Team Templation
 * @date November 2025
 * 
 * @see CustomerFactory
 * @see Plant
 */

#pragma once

#include <string>

// Forward declaration
/**
 * @class Plant
 * @brief Forward declaration of Plant class.
 * @details Defined in Plant.h to avoid circular dependencies.
 */
class Plant;

/**
 * @class Customer
 * @brief Abstract base class for all customer types in the nursery.
 * 
 * The Customer class represents a visitor to the nursery who has come to
 * purchase (or in the robber's case, steal) a specific plant. Different customer
 * types behave differently when served by workers.
 * 
 * @par Design Pattern: Factory
 * Concrete customer types are created using the Factory pattern via CustomerFactory
 * and its subclasses (RegularFactory, VIPFactory, RobberFactory).
 * 
 * @par Customer Types
 * - Regular: Standard customer with typical purchasing behavior
 * - VIP: Premium customer with special treatment
 * - Robber: Special "customer" that attempts theft
 * 
 * @par Gameplay
 * Customers are served by workers, and their satisfaction/success depends on:
 * - Whether the requested plant is available
 * - Whether a worker can serve them in time
 * - The type of customer (robbers need to be stopped by patrols)
 * 
 * @see Regular
 * @see VIP
 * @see Robber
 * @see CustomerFactory
 */
class Customer 
{
public:
    /**
     * @brief Constructor with requested plant.
     * @param requestedPlant Pointer to the Plant the customer wants (to buy or steal).
     * 
     * @pre requestedPlant should not be nullptr for typical gameplay.
     */
    Customer(Plant* requestedPlant) : requestedPlant(requestedPlant) {}

    /**
     * @brief Virtual destructor.
     * @details Ensures proper cleanup of derived customer objects.
     * @details Default implementation with no cleanup needed for base class.
     */
    virtual ~Customer() = default;

    /**
     * @brief Returns a string identifier for this customer type.
     * @return String representing the customer type ("Regular", "VIP", or "Robber").
     * 
     * @details Implemented by derived classes to identify their type.
     * 
     * @example
     * @code
     * Customer* customer = factory->create(plant);
     * std::string type = customer->type();  // "Regular", "VIP", or "Robber"
     * @endcode
     */
    virtual std::string type() const = 0;

    /**
     * @brief Sets the plant this customer wants.
     * @param p Pointer to the new Plant to request.
     * 
     * @details Allows changing the requested plant after construction.
     *         Useful for dynamic customer behavior.
     */
    void setRequestedPlant(Plant* p) { requestedPlant = p; }

    /**
     * @brief Gets the plant this customer wants.
     * @return Pointer to the requested Plant.
     */
    Plant* getRequestedPlant() const { return requestedPlant; }

private:
    Plant* requestedPlant;  ///< The plant this customer wants to buy or steal
};


/**
 * @class Regular
 * @brief Standard customer type with typical purchasing behavior.
 * 
 * Regular customers are the most common visitor type to the nursery.
 * They will purchase plants if served in time and the plant is available.
 * They provide standard revenue and customer satisfaction.
 * 
 * @par Gameplay Role
 * Provide steady income for the nursery. Generally contribute positively
 * to ratings if served well.
 * 
 * @par Probability
 * Appears with 85% probability when RandomFactory is used.
 * 
 * @see Customer
 * @see RandomFactory
 */
class Regular : public Customer 
{
public:
    /**
     * @brief Constructor for a Regular customer.
     * @param requestedPlant Pointer to the Plant this regular customer wants.
     */
    Regular(Plant* requestedPlant) : Customer(requestedPlant) {}

    /**
     * @brief Returns the type identifier for this customer.
     * @return The string "Regular".
     * 
     * @override
     */
    std::string type() const override { return "Regular"; }
};

/**
 * @class VIP
 * @brief Premium customer type with special treatment and higher value.
 * 
 * VIP customers are high-value visitors who expect and receive special treatment.
 * They may provide higher profits and significant rating bonuses if served well,
 * but severe penalties if ignored or treated poorly.
 * 
 * @par Gameplay Role
 * Provide premium revenue and significant rating effects. Ignoring a VIP
 * customer can have negative consequences for the player's reputation.
 * 
 * @par Probability
 * Appears with 10% probability when RandomFactory is used (85-95% range).
 * 
 * @see Customer
 * @see RandomFactory
 */
class VIP : public Customer 
{
public:
    /**
     * @brief Constructor for a VIP customer.
     * @param requestedPlant Pointer to the Plant this VIP customer wants.
     */
    VIP(Plant* requestedPlant): Customer(requestedPlant) {}

    /**
     * @brief Returns the type identifier for this customer.
     * @return The string "VIP".
     * 
     * @override
     */
    std::string type() const override { return "VIP"; }
};

/**
 * @class Robber
 * @brief Special "customer" that attempts to steal plants instead of buying them.
 * 
 * Robbers are anti-customers who represent a theft threat to the nursery.
 * Instead of purchasing plants through normal means, they attempt to steal them.
 * Players must use worker patrols or other defenses to prevent theft.
 * 
 * @par Gameplay Role
 * Provide challenge and tension to the gameplay. Successful thefts reduce inventory
 * and negatively impact ratings. Can be deterred by worker patrols.
 * 
 * @par Defense
 * Workers assigned to PatrolCommand can protect against robbers by setting the
 * player's protected flag, which presumably prevents theft.
 * 
 * @par Probability
 * Appears with 5% probability when RandomFactory is used (95-100% range).
 * 
 * @see Customer
 * @see RandomFactory
 * @see PatrolCommand
 */
class Robber : public Customer 
{
public:
    /**
     * @brief Constructor for a Robber customer.
     * @param requestedPlant Pointer to the Plant this robber wants to steal.
     */
    Robber(Plant* requestedPlant) : Customer(requestedPlant) {}

    /**
     * @brief Returns the type identifier for this customer.
     * @return The string "Robber".
     * 
     * @override
     */
    std::string type() const override { return "Robber"; }
};