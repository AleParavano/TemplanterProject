#ifndef SCENE_H
#define SCENE_H

#include "raylib.h"
#include "raymath.h"
#include <string>

using namespace std;

class Scene{
private:
    string type;
    public:
    virtual void render() = 0;
    virtual string getType() = 0;
};

#endif