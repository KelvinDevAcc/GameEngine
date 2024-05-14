#pragma once
#include "LoadMap.h"
#include "Scene.h" 
#include "GameObject.h"

class SceneHelpers {
public:
    static void LoadMapIntoScene(const LoadMap& loadMap, dae::Scene* scene, const glm::vec3& startPos, glm::vec2 scale);

private:
    static void CreatePlatformLeft(dae::Scene* scene, float x, float y, glm::vec2 scale);
    static void CreatePlatformMiddle(dae::Scene* scene, float x, float y, glm::vec2 scale);
    static void CreatePlatformRight(dae::Scene* scene, float x, float y, glm::vec2 scale);
    static void CreatePlatformCombined(dae::Scene* scene, float x, float y, glm::vec2 scale);
    static void CreateLadder(dae::Scene* scene, float x, float y, bool isUp, glm::vec2 scale);
    static void CreateSolidLadder(dae::Scene* scene, float x, float y, glm::vec2 scale);
    static void CreateFloor(dae::Scene* scene, float x, float y, glm::vec2 scale);
};