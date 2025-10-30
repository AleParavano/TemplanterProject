#pragma once

#include "Inventory.h"
#include "Worker.h"
#include "Greenhouse.h"
#include "Memento.h"
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

// Frontend
#include "raylib.h"
#include <vector>

class Player
{
private:
    struct Slot
    {
        const InventorySlot *slot;
        Rectangle rect;
        bool selected = false;
        std::string quantity;
        // Image icon;

        Slot(const InventorySlot *slotIn, Rectangle rectIn)
        {
            slot = slotIn;
            rect = rectIn;

            if (slotIn != nullptr)
            {
                quantity = std::to_string(slotIn->getSize());
            }
            else
            {
                quantity = "0";
            }
        }

        bool isClicked(Vector2 mousePos) const
        {
            return CheckCollisionPointRec(mousePos, rect);
        }
    };

    Inventory *inventory;
    Worker *workers;
    Greenhouse *plot;
    float money;
    int rating;
    int day;
    int hour;
    int minute;
    static bool safe;

    // Frontend
    bool inventoryOpen = false;
    std::vector<Slot> slotVector;
    int selectedSlotIndex = -1;

public:
    Player();
    ~Player();

    Inventory *getInventory() const;
    Worker *getWorkers() const;
    Greenhouse *getPlot() const;
    float getMoney() const;
    int getRating() const;

    int getDay() const;
    int getHour() const;
    int getMinute() const;
    std::string getTimeString() const;
    std::string getFullTimeString() const;

    void setInventory(Inventory *inv);
    void setWorkers(Worker *w);
    void setPlot(Greenhouse *gh);
    void setMoney(float m);
    void setRating(int r);

    void setDay(int d);
    void setHour(int h);
    void setMinute(int m);
    bool isNewDay() const;
    static void setProtected(bool prot);
    static bool isProtected();
    Memento *createMemento() const;
    void setMemento(Memento *memento);

    // Frontend methods
    void openInventory();
    void renderInventory();
    void updateInventory();
};