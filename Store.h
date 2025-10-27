#ifndef STORE_H
#define STORE_H

#include "raylib.h"
#include "raymath.h"

class Store
{
private:
    bool plants[10][10];
    int inventory[5];
    
    // Modal state
    bool showModal;
    int selectedInventorySlot;
    bool selectedPlantFromGrid;
    int selectedGridX;
    int selectedGridY;
    
    Rectangle manageToggle;

public:
    // Collision rectangles (public so Player can access them)
    Rectangle counterHitBox;
    Rectangle sDoor;
    Rectangle plotHitBox;
    Rectangle boundaryWall;
    
    Store();
    void update();
    void render();
    void renderModal(int width, int height);
};

#endif