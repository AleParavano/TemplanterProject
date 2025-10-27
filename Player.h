#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

// Forward declaration to avoid circular dependency
class Store;

class Player
{
private:
    Vector2 position;
    float radius;
    Color color;

public:
    Player();
    void update(Store& store);
    void render();
    Vector2 getPosition() const { return position; }
};

#endif