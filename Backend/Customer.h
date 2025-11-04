#pragma once

#include <string>

// Forward declaration to avoid circular dependencies and just include necessary details.
class Plant;

/**
 * @class Customer
 * @brief The abstract base class representing any type of customer visiting the greenhouse.
 * * It defines the common interface and required item for all customers.
 */
class Customer 
{
    public:
    /**
     * @brief Constructor for the Customer base class.
     * @param requestedPlant A pointer to the specific Plant the customer is requesting/targeting.
     */
    Customer(Plant* requestedPlant) : requestedPlant(requestedPlant) {}
    
    /**
     * @brief Virtual default destructor to ensure proper cleanup of derived classes.
     */
    virtual ~Customer() = default;
    
    /**
     * @brief Pure virtual function to identify the type of the customer.
     * @return A string representing the concrete customer type (e.g., "Regular", "VIP").
     */
    virtual std::string type() const = 0;
    
    /**
     * @brief Sets the plant the customer is requesting.
     * @param p A pointer to the new Plant object.
     */
    void setRequestedPlant(Plant* p) { requestedPlant = p; }
    
    /**
     * @brief Retrieves the plant the customer is currently requesting.
     * @return A pointer to the requested Plant object.
     */
    Plant* getRequestedPlant() const { return requestedPlant; }

    private:
    /**
     * @brief The specific Plant object that this customer is interested in.
     */
    Plant* requestedPlant;
};


// --- Concrete Customer Types ---

/**
 * @class Regular
 * @brief Represents a standard, non-prioritized customer.
 */
class Regular : public Customer 
{
    public:
    /**
     * @brief Constructs a Regular customer.
     * @param requestedPlant The plant this customer wishes to buy.
     */
    Regular(Plant* requestedPlant) : Customer(requestedPlant) {}
    
    /**
     * @brief Returns the type identifier.
     * @return The string "Regular".
     */
    std::string type() const override { return "Regular"; }
};

/**
 * @class VIP
 * @brief Represents a customer with high priority.
 * * May be served before other customer types.
 */
class VIP : public Customer 
{
    public:
    /**
     * @brief Constructs a VIP customer.
     * @param requestedPlant The plant this customer wishes to buy.
     */
    VIP(Plant* requestedPlant): Customer(requestedPlant) {}
    
    /**
     * @brief Returns the type identifier.
     * @return The string "VIP".
     */
    std::string type() const override { return "VIP"; }
};

/**
 * @class Robber
 * @brief Represents an antagonistic entity or a special event customer.
 * * May require special handling or defensive actions by the greenhouse.
 */
class Robber : public Customer 
{
    public:
    /**
     * @brief Constructs a Robber customer.
     * @param requestedPlant The plant the robber is targeting.
     */
    Robber(Plant* requestedPlant) : Customer(requestedPlant) {}
    
    /**
     * @brief Returns the type identifier.
     * @return The string "Robber".
     */
    std::string type() const override { return "Robber"; }
};