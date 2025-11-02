// #ifndef SCENEMANAGER_H
// #define SCENEMANAGER_H

// #include "Scene.h"
// #include "UI.h"
// #include "OutdoorScene.h"
// #include "GreenHouseScene.h"
// #include "StoreScene.h"
// #include "WarehouseScene.h"
// #include "../Backend/Game.h"
// #include "../Backend/Player.h"
// #include <map>


// class Demo;
// class SceneManager {
//     friend class Demo;
// private:
//     std::map<SceneType, Scene*> scenes;
//     SceneType currentScene;
//     SceneType nextScene;
//     bool shouldExit;

// public:

//     SceneManager();
//     ~SceneManager();

//     void Update(float dt);
//     void HandleInput();
//     void Draw();
//     bool IsDone() const;
// };

// #endif // SCENEMANAGER_H

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "UI.h"
#include "OutdoorScene.h"
#include "GreenHouseScene.h"
#include "StoreScene.h"
#include "WarehouseScene.h"
#include "../Backend/Game.h"
#include "../Backend/Player.h"
#include <map>

class Demo; // Forward declaration

class SceneManager {
private:
    std::map<SceneType, Scene*> scenes;
    SceneType currentScene;
    SceneType nextScene;
    bool shouldExit;

    friend class Demo; // <<< FIX: Grants Demo access to the 'scenes' map >>>

public:
    SceneManager();
    ~SceneManager();

    void Update(float dt);
    void HandleInput();
    void Draw();
    bool IsDone() const;
};

#endif // SCENEMANAGER_H