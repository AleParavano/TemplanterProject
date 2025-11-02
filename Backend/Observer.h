#pragma once

// Forward declarations
class Greenhouse;

class Observer {
public:
    Observer();
    virtual ~Observer() = default;
    
    virtual void update() = 0;
    virtual void setSubject(Greenhouse* greenhouse) = 0;
    
    bool operator==(Observer* observer);
    
protected:
    int id;
    
private:
    static int ObserverCount;
};