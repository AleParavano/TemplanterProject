#pragma once

#include <string>
#include <vector>
#include "Inventory.h"
#include "Greenhouse.h"
#include "Worker.h"
#include "Memento.h"
#include "../Frontend/InventoryUI.h" // <<< Final Check: InventoryUI included >>>

class Player 
{
public:
    Player();
    ~Player();
    
    float getMoney() const;
    void setMoney(float amount);
    void addMoney(float amount);
    void subtractMoney(float amount);
    
    float getRating() const;
    void setRating(float r);
    void addRating(float r);
    void subtractRating(float r);
    
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    void setTime(int d, int h, int m);
    void advanceTime(int minutes);
    void UpdateGameTime(float dt); // <<< UpdateGameTime added >>>

    // <<< Final Check: Inventory UI Getter >>>
    InventoryUI* getInventoryUI() const { return inventoryUI; }
    
    Inventory* getInventory() const;
    Greenhouse* getPlot() const;
    
    void addWorker(Worker* worker); // <<< addWorker added >>>
    void fireWorker(int index);
    Worker* getWorker(int index) const;
    int getWorkerCount() const;
    void pauseWorkers();
    void startWorkers() ;
    const std::vector<Worker*>& getWorkers() ;
    
    std::string getTimeString() const; // <<< getTimeString added >>>
    
    void setProtected(bool prot);
    bool isProtected();

    Memento* createMemento() const;
    void setMemento(Memento* memento);

private:
    float money;
    float rating;
    int day;
    int hour;
    int minute;
    bool safe;
    
    float timeAccumulator; // <<< timeAccumulator added >>>
    
    Inventory* inventory;
    Greenhouse* plot;
    std::vector<Worker*> workers;
    InventoryUI* inventoryUI; // <<< InventoryUI member added >>>
};