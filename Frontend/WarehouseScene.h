// ===== WarehouseScene.h =====
#ifndef WAREHOUSESCENE_H
#define WAREHOUSESCENE_H

#include "Scene.h"

class WarehouseScene : public Scene {
public:
    WarehouseScene() = default;
    ~WarehouseScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    SceneType GetSceneType() const override { return SCENE_WAREHOUSE; }
};

#endif // WAREHOUSESCENE_H