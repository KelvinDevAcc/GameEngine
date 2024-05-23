#include "SceneData.h"
#include <iostream>

#include "SceneHelpers.h"

namespace dae {
    SceneData& SceneData::GetInstance() {
        static SceneData instance;
        return instance;
    }

    void SceneData::AddGameObject(GameObject* gameObject, GameObjectType type) {
        switch (type) {
        case GameObjectType::Floor: m_floors.push_back(gameObject); break;
        case GameObjectType::Ladder: m_ladders.push_back(gameObject); break;
        case GameObjectType::SolidLadder: m_solidLadders.push_back(gameObject); break;
        case GameObjectType::Player: m_players.push_back(gameObject); break;
        case GameObjectType::BurgerPart: m_burgerParts.push_back(gameObject); break;
        case GameObjectType::Basket: m_baskets.push_back(gameObject); break;
        }
    }

    void SceneData::Update() {
        //CheckPlayerCollisions();
    }

    void SceneData::CheckPlayerCollisions() {
        for (const auto player : m_players) {
            const auto playerHitBox = player->GetComponent<HitBox>();
            for (const auto& objects : { m_floors, m_ladders, m_solidLadders }) {
                for (const auto gameObject : objects) {
                    const auto hitBox = gameObject->GetComponent<HitBox>();
                    if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                        OnCollision(player, gameObject, GameObjectType::Floor); // Adjust GameObjectType as needed
                    }
                }
            }
        }
    }

    void SceneData::OnCollision(GameObject* a, GameObject* b, GameObjectType type) {
        switch (type) {
        case GameObjectType::Floor:
            std::cout << "Collision detected between player " << a << " and floor " << b << std::endl;
            break;
        case GameObjectType::Ladder:
            std::cout << "Collision detected between player " << a << " and ladder " << b << std::endl;
            break;
        }
    }

    bool SceneData::IsOnSpecificObjectType(GameObject& player, const std::vector<GameObject*>& objects) const {
        const auto playerHitBox = player.GetComponent<HitBox>();
        for (const auto gameObject : objects) {
            const auto hitBox = gameObject->GetComponent<HitBox>();
            if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                return true;
            }
        }
        return false;
    }
    bool SceneData::IsWithinBounds(float x, float y) const {
        // Define the boundaries of the game world
        const float minX = SceneHelpers::GetMinCoordinates().x;
        const float minY = SceneHelpers::GetMinCoordinates().y;
        const float maxX = SceneHelpers::GetMaxCoordinates().x;
        const float maxY = SceneHelpers::GetMaxCoordinates().y;

        // Check if the given position is within the defined bounds
        return x >= minX && x < maxX && y >= minY && y < maxY;
    }

    bool SceneData::CanEntityMove(float moveX, float moveY, GameObject& entity) const {
        // Get the current position of the entity
        const glm::vec3 currentPosition = entity.GetWorldPosition();

        // Calculate the new position after applying the movement
        const glm::vec3 newPosition = currentPosition + glm::vec3(moveX, moveY, 0.0f);

        // Check if the new position is within the bounds of the game world
        if (!IsWithinBounds(newPosition.x, newPosition.y)) 
        {
            return false; // Movement would go out of bounds
        }

        // Check for collisions with obstacles
       
        return  IsNextObject(newPosition.x, newPosition.y);
    }


    float SceneData::GetLadderCenterX(GameObject& gameObject) const {
        // Placeholder implementation: Return the center position of the ladder
        // You might need to adjust this based on how your ladder GameObject is structured
        const auto hitBox = gameObject.GetComponent<HitBox>();
        if (hitBox) {
            const SDL_Rect rect = hitBox->GetRect();
            const float centerX =static_cast<float>(rect.x);
            return centerX;
        }
        return 0.f; // Default to (0, 0) if no ladder center is found
    }

    bool SceneData::IsNextObject(float x, float y) const {
        auto checkCollisionsWithObjects = [&](const std::vector<GameObject*>& objects) {
            for (const auto gameObject : objects) {
                const auto hitBox = gameObject->GetComponent<HitBox>();
                if (hitBox) {
                    const SDL_Rect rect = hitBox->GetRect();
                    if (x >= rect.x && x < rect.x + rect.w &&
                        y >= rect.y && y < rect.y + rect.h) {
                        return true; // Collision detected
                    }
                }
            }
            return false; // No collision detected
            };

        // Check collisions with different types of objects
        if (checkCollisionsWithObjects(m_solidLadders)) return true;
        if (checkCollisionsWithObjects(m_floors)) return true;
        if (checkCollisionsWithObjects(m_ladders)) return true;

        return false; // No collision detected with any object
    }

    GameObject* SceneData::GetPlayer() const {
        return !m_players.empty() ? m_players.front() : nullptr;
    }

    const std::vector<GameObject*>& SceneData::GetBurgerParts() const {
        return m_burgerParts;
    }

    bool SceneData::IsOnFloor(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_floors);
    }

    bool SceneData::IsOnLadder(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_ladders);
    }

	bool SceneData::IsOnSolidLadder(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_solidLadders);
    }
    bool SceneData::IsInBasket(GameObject& burger) const {
        return IsOnSpecificObjectType(burger, m_baskets);
    }
}
