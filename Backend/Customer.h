#pragma once

#include <string>

class Plant;

class Customer 
{
    public:
    Customer(Plant* requestedPlant) : requestedPlant(requestedPlant) {}
    virtual ~Customer() = default;
    virtual std::string type() const = 0;
    void setRequestedPlant(Plant* p) { requestedPlant = p; }
    Plant* getRequestedPlant() const { return requestedPlant; }

    private:
    Plant* requestedPlant;
};


class Regular : public Customer 
{
    public:
    Regular(Plant* requestedPlant) : Customer(requestedPlant) {}
    std::string type() const override { return "Regular"; }
};

class VIP : public Customer 
{
    public:
    VIP(Plant* requestedPlant): Customer(requestedPlant) {}
    std::string type() const override { return "VIP"; }
};

class Robber : public Customer 
{
    public:
    Robber(Plant* requestedPlant) : Customer(requestedPlant) {}
    std::string type() const override { return "Robber"; }
};