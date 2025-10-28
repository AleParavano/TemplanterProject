#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "raymath.h"

class Scene{
public:
    virtual void render() = 0;
};

#endif