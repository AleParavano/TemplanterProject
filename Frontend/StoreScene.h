#ifndef STORESCENE_H
#define STORESCENE_H

#include "Scene.h"

class StoreScene : public Scene{
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
    
    StoreScene();
    void update();
    void render();
    void renderModal(int width, int height);
    string getType();
};

#endif