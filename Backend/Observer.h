#pragma once

class Plant;

class Observer{
    public:
    virtual void update()=0;
    virtual void update(Plant* changedPlant)=0;
    virtual void setSubject(Plant* plant)=0;
    Observer();
    bool operator==(Observer* observer);
    virtual ~Observer(){}
    protected:
    static int ObserverCount;
    int id;
};