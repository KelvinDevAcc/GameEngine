#include "SceneData.h"
#include <iostream>

namespace dae {

    SceneData& SceneData::GetInstance() {
        static SceneData instance;
        return instance;
    }


    void SceneData::AddGameObject(GameObject* gameObject, GameObjectType type) {
        switch (type) {
        case GameObjectType::Floor:
            m_floors.push_back(gameObject);
            break;
        case GameObjectType::Ladder:
            m_ladders.push_back(gameObject);
            break;
        case GameObjectType::SolidLadder:
            m_solidLadders.push_back(gameObject);
            break;
        case GameObjectType::PlatformLeft:
            m_platformsLeft.push_back(gameObject);
            break;
        case GameObjectType::PlatformMiddle:
            m_platformsMiddle.push_back(gameObject);
            break;
        case GameObjectType::PlatformRight:
            m_platformsRight.push_back(gameObject);
            break;
        case GameObjectType::PlatformCombined:
            m_platformsCombined.push_back(gameObject);
            break;
        case GameObjectType::Player:
            m_players.push_back(gameObject);
            break;
        }
    }

    void SceneData::Update() {
        // Check for player collisions
        CheckPlayerCollisions();
    }

    void SceneData::CheckPlayerCollisions() {
        for (const auto player : m_players) {
            CheckCollisionsWithPlayer(player);
        }
    }

    void SceneData::CheckCollisionsWithPlayer(GameObject* player) {
        const auto playerHitBox = player->GetComponent<HitBox>();

        auto checkCollisionsWithObjects = [&](const std::vector<GameObject*>& objects, GameObjectType type) {
            for (const auto gameObject : objects) {
                const auto hitBox = gameObject->GetComponent<HitBox>();
                if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                    OnCollision(player, gameObject, type);
                }
            }
            };

        checkCollisionsWithObjects(m_floors, GameObjectType::Floor);
        checkCollisionsWithObjects(m_ladders, GameObjectType::Ladder);
        checkCollisionsWithObjects(m_solidLadders, GameObjectType::SolidLadder);
        checkCollisionsWithObjects(m_platformsLeft, GameObjectType::PlatformLeft);
        checkCollisionsWithObjects(m_platformsMiddle, GameObjectType::PlatformMiddle);
        checkCollisionsWithObjects(m_platformsRight, GameObjectType::PlatformRight);
        checkCollisionsWithObjects(m_platformsCombined, GameObjectType::PlatformCombined);
    }

    void SceneData::OnCollision(GameObject* a, GameObject* b, GameObjectType type) {
        if (type == GameObjectType::Floor) {
            std::cout << "Collision detected between player " << a << " and floor " << b << std::endl;
        }

        if (type == GameObjectType::Ladder) {
            std::cout << "Collision detected between player " << a << " and ladder " << b << std::endl;
        }
    }

    bool SceneData::CanEntityMove(float move_x, float move_y, GameObject& entity) const {
        const glm::vec2 current_pos = entity.GetWorldPosition();
        const glm::vec2 new_pos = current_pos + glm::vec2(move_x, move_y);
        return !IsObstacle(new_pos.x, new_pos.y);
    }

    bool SceneData::IsObstacle(float x, float y) const {
        if (!IsWithinBounds(x, y)) {
            return true;
        }

        auto checkCollisionsWithObjects = [&](const std::vector<GameObject*>& objects) {
            for (const auto gameObject : objects) {
                const auto hitBox = gameObject->GetComponent<HitBox>();
                if (hitBox) {
                    SDL_Rect rect = hitBox->GetRect();
                    if (x >= rect.x && x < rect.x + rect.w &&
                        y >= rect.y && y < rect.y + rect.h) {
                        return true;
                    }
                }
            }
            return false;
            };

        //if (checkCollisionsWithObjects(m_solidLadders)) return true;

        return false;
    }

    bool SceneData::IsWithinBounds(float x, float y) const {
        // Define your world bounds here. Example:
        const float worldWidth = 1000.0f;  // Example width
        const float worldHeight = 1000.0f; // Example height

        return (x >= 0 && x < worldWidth && y >= 0 && y < worldHeight);
    }

    bool SceneData::IsOnLadder(GameObject& player) const {
        const auto playerHitBox = player.GetComponent<HitBox>();
        for (const auto gameObject : m_ladders) {
            const auto hitBox = gameObject->GetComponent<HitBox>();
            if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                return true;
            }
        }
        return false;
    }

    bool SceneData::IsOnSolidLadder(GameObject& player) const {
        const auto playerHitBox = player.GetComponent<HitBox>();
        for (const auto gameObject : m_solidLadders) {
            const auto hitBox = gameObject->GetComponent<HitBox>();
            if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                return true;
            }
        }
        return false;
    }

    bool SceneData::IsOnFloor(GameObject& player) const {
        const auto playerHitBox = player.GetComponent<HitBox>();
        for (const auto gameObject : m_floors) {
            const auto hitBox = gameObject->GetComponent<HitBox>();
            if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                return true;
            }
        }
        return false;
    }

    float SceneData::GetLadderCenterX(GameObject& player) const {
        const auto playerHitBox = player.GetComponent<HitBox>();
        for (const auto gameObject : m_ladders) {
            const auto hitBox = gameObject->GetComponent<HitBox>();
            if (hitBox && playerHitBox->IsColliding(*hitBox)) {
                SDL_Rect ladderRect = hitBox->GetRect();
                return static_cast<float>(ladderRect.x + ladderRect.w / 2.0f); // Calculate center X of the ladder
            }
        }
        return player.GetWorldPosition().x; // Default to current position if not colliding with any ladder
    }

}