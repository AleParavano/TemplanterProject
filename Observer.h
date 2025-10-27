#pragma once
#include "Subject.h"
#include "Plant.h"
class Observer{
    public:
    virtual void update(Plant* Plant)=0;
    Observer(){
        id=ObserverCount++;
    }
    bool operator==(Observer* observer){
        return this->id==observer->id;
    }
    virtual ~Observer(){}
    protected:
    static int ObserverCount;
    int id;
};