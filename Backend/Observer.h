#pragma once

class Plant;

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