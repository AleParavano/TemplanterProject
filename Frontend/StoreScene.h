// ===== StoreScene.h =====
#ifndef STORSCENE_H
#define STORSCENE_H

#include "Scene.h"

class StoreScene : public Scene {
public:
    StoreScene() = default;
    ~StoreScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    SceneType GetSceneType() const override { return SCENE_STORE; }
};

#endif // STORSCENE_H
