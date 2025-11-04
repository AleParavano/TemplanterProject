#pragma once

class StoreItem 
{
public:
    virtual ~StoreItem() = default;
    virtual float getPrice() const = 0;
    virtual void* request() = 0;
};