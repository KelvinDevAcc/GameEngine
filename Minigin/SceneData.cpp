#include "SceneData.h"
#include <iostream>

#include "SceneHelpers.h"
#include "../BugerTime/Player.h"

namespace dae {
    SceneData& SceneData::GetInstance() {
        static SceneData instance;
        return instance;
    }

    void SceneData::AddGameObject(GameObject* gameObject, GameObjectType type) {
        switch (type) {
        case GameObjectType::Floor: m_floors.push_back(gameObject); break;
        case GameObjectType::LadderUp: m_ladderUp.push_back(gameObject); break;
        case GameObjectType::LadderUpDown: m_ladderUpDown.push_back(gameObject); break;
        case GameObjectType::LadderDown: m_ladderDown.push_back(gameObject); break;
        case GameObjectType::SolidLadder: m_solidLadders.push_back(gameObject); break;
        case GameObjectType::Player: m_players.push_back(gameObject); break;
        case GameObjectType::enemy: m_enemys.push_back(gameObject); break;
        case GameObjectType::BurgerPart: m_burgerParts.push_back(gameObject); break;
        case GameObjectType::Basket: m_baskets.push_back(gameObject); break;
        }
    }

    void SceneData::RemoveAllGameObjects()
    {
        m_floors.clear();
        m_ladderUp.clear();
        m_ladderDown.clear();
        m_ladderUpDown.clear();
        m_solidLadders.clear();
        m_players.clear();
        m_enemys.clear();
        m_burgerParts.clear();
        m_baskets.clear();
    }

    void SceneData::Update()
    {
        // Loop through each player
        for (GameObject* player : GetPlayers()) {
            // Check if the player is colliding with an enemy
            if (player && isOnEnemy(*player)) {
                // Handle player-enemy collision
                player->GetComponent<game::Player>()->Die(); // Example function to handle player taking damage
            }
        }
    }

    bool SceneData::IsOnSpecificObjectType(GameObject& object, const std::vector<GameObject*>& objects) const {
        const auto hitBox = object.GetComponent<HitBox>();
        if (!hitBox) return false;

        for (const auto& gameObject : objects) {
            // Skip the object itself
            if (gameObject == &object) continue;

            const auto otherHitBox = gameObject->GetComponent<HitBox>();
            if (otherHitBox && hitBox->IsColliding(*otherHitBox)) {

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
        const float maxY = SceneHelpers::GetMaxCoordinates().y - (SceneHelpers::GetCellSize().y*4 + 5);

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

    GameObject* SceneData::GetFloorAt(const glm::vec3& position) const
    {
        // Iterate through all floor objects
        for (const auto& floor : m_floors) {
	        if (const auto hitBox = floor->GetComponent<HitBox>()) {
                const SDL_Rect rect = hitBox->GetRect();
                // Check if the position is within the bounds of the current floor
                if (position.x >= rect.x && position.x < rect.x + rect.w &&
                    position.y >= rect.y && position.y < rect.y + rect.h) {
                    return floor;
                }
            }
        }
        // If no floor is found at the given position, return nullptr
        return nullptr;
    }

    bool SceneData::IsNextObject(float x, float y) const {
        auto checkCollisionsWithObjects = [&](const std::vector<GameObject*>& objects) {
            for (const auto gameObject : objects) {
	            if (const auto hitBox = gameObject->GetComponent<HitBox>()) {
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
        if (checkCollisionsWithObjects(m_ladderUp)) return true;
        if (checkCollisionsWithObjects(m_ladderUpDown)) return true;
        if (checkCollisionsWithObjects(m_ladderDown)) return true;

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

    bool SceneData::IsOnLadderUp(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_ladderUp);
    }

    bool SceneData::IsOnLadderUpDown(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_ladderUpDown);
    }

    bool SceneData::IsOnLadderDown(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_ladderDown);
    }

	bool SceneData::IsOnSolidLadder(GameObject& player) const {
        return IsOnSpecificObjectType(player, m_solidLadders);
    }
    bool SceneData::IsInBasket(GameObject& burger) const {
        return IsOnSpecificObjectType(burger, m_baskets);
    }

    bool SceneData::IsBurgerPartColliding(GameObject& burgerPart) const {
        return IsOnSpecificObjectType(burgerPart, m_burgerParts);
    }

    bool SceneData::isOnEnemy(GameObject& burgerPart) const {
        return IsOnSpecificObjectType(burgerPart, m_enemys);
    }
}
