#pragma once

#include <string>

class PlantState
{
    public:
    PlantState();
    PlantState(float gr, float wa, float nu);
    virtual ~PlantState() = 0;
    virtual void handle() = 0;
    virtual std::string getState() = 0;
    
    protected:
    float growth;
    float water;
    float nutrients;

    friend class Plant;
};

class SeedState : public PlantState
{
    public:
    SeedState(float gr, float wa, float nu);
    virtual ~SeedState();
    void handle();
    std::string getState();
};

class GrowingState : public PlantState
{
    public:
    GrowingState(float gr, float wa, float nu);
    virtual ~GrowingState();
    void handle();
    std::string getState();
};

class RipeState : public PlantState
{
    public:
    RipeState(float gr, float wa, float nu);
    virtual ~RipeState();
    void handle();
    std::string getState();
};

class DeadState : public PlantState
{
    public:
    DeadState(float gr, float wa, float nu);
    virtual ~DeadState();
    void handle();
    std::string getState();
};