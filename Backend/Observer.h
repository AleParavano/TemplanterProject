#pragma once
#include "Subject.h"
#include "Plant.h"
class Observer{
    public:
    virtual void update(Plant* Plant)=0;
    Observer();
    bool operator==(Observer* observer);
    virtual ~Observer(){}
    protected:
    static int ObserverCount;
    int id;
};