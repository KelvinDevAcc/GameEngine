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
        BurgerPart,
        Player,
        Basket
    };

    class SceneData : public Singleton<SceneData> {
    public:
        static SceneData& GetInstance();
        SceneData(const SceneData&) = delete;
        void operator=(const SceneData&) = delete;

        void AddGameObject(GameObject* gameObject, GameObjectType type);
        void RemoveAllGameObjects();

        void Update();

        GameObject* GetPlayer() const;
        std::vector<GameObject*> GetPlayers() const {return m_players;}
        const std::vector<GameObject*>& GetBurgerParts() const;
        GameObject* GetFloorAt(const glm::vec3& position) const;

        bool IsOnFloor(GameObject& player) const;
        bool IsOnLadder(GameObject& player) const;
        bool IsOnSolidLadder(GameObject& player) const;
        bool IsInBasket(GameObject& burger) const;
        bool IsBurgerPartColliding(GameObject& burgerPart) const;

        bool CanEntityMove(float moveX, float moveY, GameObject& entity) const;

        bool IsWithinBounds(float x, float y) const;

        bool IsNextObject(float x, float y) const;

        bool IsOnSpecificObjectType(GameObject& player, const std::vector<GameObject*>& objects) const;

    private:
        SceneData() = default;

        std::vector<GameObject*> m_floors;
        std::vector<GameObject*> m_ladders;
        std::vector<GameObject*> m_solidLadders;
        std::vector<GameObject*> m_players;
        std::vector<GameObject*> m_burgerParts;
        std::vector<GameObject*> m_baskets;

        void CheckPlayerCollisions();
        void OnCollision(GameObject* a, GameObject* b, GameObjectType type);

    };
}
