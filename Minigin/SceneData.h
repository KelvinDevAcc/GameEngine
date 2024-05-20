#pragma once
#include <vector>
#include "GameObject.h"
#include "HitBox.h"
#include "Singleton.h"

namespace dae {
    enum class GameObjectType {
        Floor,
        Ladder,
        SolidLadder,
        PlatformLeft,
        PlatformMiddle,
        PlatformRight,
        PlatformCombined,
        Player
    };

    class SceneData : Singleton<SceneData> {
    public:
        static SceneData& GetInstance();
        SceneData(const SceneData&) = delete;
        void operator=(const SceneData&) = delete;

        void AddGameObject(GameObject* gameObject, GameObjectType type);
        void Update();

        bool CanEntityMove(float move_x, float move_y,GameObject& entity) const;

        bool IsOnLadder(GameObject& player) const;
        bool IsOnSolidLadder(GameObject& player) const;
        float GetLadderCenterX(GameObject& player) const;
        bool IsOnFloor(GameObject& player) const;

    private:
        SceneData() = default;

        std::vector<GameObject*> m_players;
        std::vector<GameObject*> m_floors;
        std::vector<GameObject*> m_ladders;
        std::vector<GameObject*> m_solidLadders;
        std::vector<GameObject*> m_platformsLeft;
        std::vector<GameObject*> m_platformsMiddle;
        std::vector<GameObject*> m_platformsRight;
        std::vector<GameObject*> m_platformsCombined;

        void CheckPlayerCollisions();
        void CheckCollisionsWithPlayer(GameObject* player);
        void OnCollision(GameObject* a, GameObject* b, GameObjectType type);


       
        bool IsObstacle(float x, float y) const;
        bool IsWithinBounds(float x, float y) const;



    };
}
