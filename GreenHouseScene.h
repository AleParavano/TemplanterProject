#ifndef GREENHOUSESCENE_H
#define GREENHOUSESCENE_H

#include "Scene.h"
#include "Types.h"

#define MAX_PLANTS 250

class GreenHouseScene : public Scene {
private:
    PlantVisual plants[MAX_PLANTS];
    Road paths[10];
    int numPlants;
    int numPaths;

    void InitPlants();
    void InitPaths();
    void DrawPlantDetailed(PlantVisual p);
    void DrawGate(Vector2 position, bool isVertical);
    void DrawGreenhouse();
    float Distance(Vector2 a, Vector2 b);
    int ClampValue(int value, int min, int max);

public:
    GreenHouseScene();
    ~GreenHouseScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw() override;
    void HandleInput() override;
    SceneType GetSceneType() const override { return SCENE_GREENHOUSE; }
};

#endif // GREENHOUSESCENE_H