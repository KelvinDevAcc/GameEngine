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

    void SceneData::RemoveAllGameObjects()
    {
        m_floors.clear();
        m_ladders.clear();
        m_solidLadders.clear();
        m_players.clear();
        m_burgerParts.clear();
        m_baskets.clear();
    }

    void SceneData::Update() {
       // CheckPlayerCollisions();
    }

    void SceneData::CheckPlayerCollisions() {
        for (const auto player : m_players) {
            if (const auto playerHitBox = player->GetComponent<HitBox>()) {
                for (const auto& objects : { m_floors, m_ladders, m_solidLadders }) {
                    for (const auto gameObject : objects) {
                        if (const auto hitBox = gameObject->GetComponent<HitBox>()) {
                            if (playerHitBox->IsColliding(*hitBox)) {
                                // Determine the type based on the current object list
                                GameObjectType type;
                                if (objects == m_floors) type = GameObjectType::Floor;
                                else if (objects == m_ladders) type = GameObjectType::Ladder;
                                else if (objects == m_solidLadders) type = GameObjectType::SolidLadder;
                                else continue; // If none match, skip to the next

                                OnCollision(player, gameObject, type);
                            }
                        }
                    }
                }
            }
        }
    }

    void SceneData::OnCollision(GameObject* a, GameObject* b, GameObjectType type) {
        // Retrieve positions
        const glm::vec3 posA = a->GetWorldPosition();
        const glm::vec3 posB = b->GetWorldPosition();

        // Retrieve hitbox dimensions
        const auto hitBoxA = a->GetComponent<HitBox>();
        const auto hitBoxB = b->GetComponent<HitBox>();

        if (!hitBoxA || !hitBoxB) return;

        const SDL_Rect rectA = hitBoxA->GetRect();
        const SDL_Rect rectB = hitBoxB->GetRect();

        switch (type) {
        case GameObjectType::Floor:
            std::cout << "Collision detected between player " << a << " and floor " << b
                << " at positions (" << posA.x << ", " << posA.y << ") and ("
                << posB.x << ", " << posB.y << ")\n"
                << "Hitbox A: (" << rectA.x << ", " << rectA.y << ", " << rectA.w << ", " << rectA.h << ")\n"
                << "Hitbox B: (" << rectB.x << ", " << rectB.y << ", " << rectB.w << ", " << rectB.h << ")\n";
            break;
        case GameObjectType::Ladder:
            std::cout << "Collision detected between player " << a << " and ladder " << b
                << " at positions (" << posA.x << ", " << posA.y << ") and ("
                << posB.x << ", " << posB.y << ")\n"
                << "Hitbox A: (" << rectA.x << ", " << rectA.y << ", " << rectA.w << ", " << rectA.h << ")\n"
                << "Hitbox B: (" << rectB.x << ", " << rectB.y << ", " << rectB.w << ", " << rectB.h << ")\n";
            break;
        case GameObjectType::SolidLadder:
            std::cout << "Collision detected between player " << a << " and solid ladder " << b
                << " at positions (" << posA.x << ", " << posA.y << ") and ("
                << posB.x << ", " << posB.y << ")\n"
                << "Hitbox A: (" << rectA.x << ", " << rectA.y << ", " << rectA.w << ", " << rectA.h << ")\n"
                << "Hitbox B: (" << rectB.x << ", " << rectB.y << ", " << rectB.w << ", " << rectB.h << ")\n";
            break;
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
        const float maxY = SceneHelpers::GetMaxCoordinates().y - (SceneHelpers::GetCellSize().y*3);

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

    bool SceneData::IsBurgerPartColliding(GameObject& burgerPart) const {
        return IsOnSpecificObjectType(burgerPart, m_burgerParts);
    }
}
