#include "BurgerComponent.h"

#include <iostream>

#include "SceneData.h"
#include "HitBox.h"
#include "PointComponent.h"
#include "SpriteRendererComponent.h"
#include "../BugerTime/Player.h"

namespace game
{
	class Player;
}

BurgerComponent::BurgerComponent(float length, float dropDistance)
	: m_DroppingPlayer(nullptr), m_IsDropping(false), m_Length(length), m_DropDistance(dropDistance),
	  m_PlayerWalkedDistance(0.0f), m_HasDropped(false)
{
}

void BurgerComponent::Update() {
    if (m_IsDropping) {
        DropToNextFloor();
    }
    else if (!m_IsDropping) {
        if (IsPlayerOverComponent()) {
            m_IsDropping = true; // Start dropping
            if (m_DroppingPlayer)
            {
                const int score = m_DroppingPlayer->GetComponent<dae::PointComponent>()->GetScore();
                m_DroppingPlayer->GetComponent<dae::PointComponent>()->SetScore(score + 50);
                m_DroppingPlayer = nullptr;
            }
        }
        else {
            m_PlayerWalkedDistance = 0.0f; // Reset if player steps off
        }
    }
}

bool BurgerComponent::IsPlayerOverComponent() 
{
    const auto& sceneData = dae::SceneData::GetInstance();
    const auto players = sceneData.GetPlayers();
    if (players.empty()) return false;

    const auto burgerPosition = GetGameObject()->GetWorldPosition();
    float minDistance = std::numeric_limits<float>::max();
    dae::GameObject* closestPlayer = nullptr;

    for (const auto player : players)
    {
        const auto playerHitBox = player->GetComponent<HitBox>();
        if (!playerHitBox) continue;

        const auto playerPosition = player->GetWorldPosition();
        const float distance = glm::distance(playerPosition, burgerPosition);
        if (distance < minDistance)
        {
            minDistance = distance;
            closestPlayer = player;
        }
    }

    if (!closestPlayer) return false;
    m_DroppingPlayer = closestPlayer;
    const auto burgerHitBox = GetGameObject()->GetComponent<HitBox>();
    return burgerHitBox && closestPlayer->GetComponent<HitBox>() && burgerHitBox->IsColliding(*closestPlayer->GetComponent<HitBox>());
}

float BurgerComponent::GetPlayerMovementOverComponent() const
{
    auto& sceneData = dae::SceneData::GetInstance();
    const auto player = sceneData.GetPlayer();
    if (!player) {
        std::cout << "Error: Player is nullptr\n";
        return 0.0f;
    }

    const glm::vec3 playerMovement = player->GetWorldPosition();
    const auto playerHitBox = player->GetComponent<HitBox>();
    const auto burgerHitBox = GetGameObject()->GetComponent<HitBox>();

    if (!playerHitBox) {
        std::cout << "Error: Player HitBox is nullptr\n";
        return 0.0f;
    }
    if (!burgerHitBox) {
        std::cout << "Error: Burger HitBox is nullptr\n";
        return 0.0f;
    }

    // Log the positions and sizes of the hitbox rectangles
    std::cout << "Player HitBox: x=" << playerHitBox->GetRect().x << ", y=" << playerHitBox->GetRect().y << ", w=" << playerHitBox->GetRect().w << ", h=" << playerHitBox->GetRect().h << "\n";
    std::cout << "Burger HitBox: x=" << burgerHitBox->GetRect().x<< ", y=" << burgerHitBox->GetRect().y << ", w=" << burgerHitBox->GetRect().w << ", h=" << burgerHitBox->GetRect().h << "\n";

    // Check if the hitboxes are colliding
    if (playerHitBox->IsColliding(*burgerHitBox)) {
        std::cout << "Collision detected!\n";
        return glm::length(playerMovement); // Length of the movement vector
    }

    return 0.0f;
}


void BurgerComponent::StartDropping() {
    m_IsDropping = true;
}


void BurgerComponent::DropToNextFloor() {
    const auto& sceneData = dae::SceneData::GetInstance();
    auto* burger = GetGameObject();
    // Retrieve the burger's hitbox
    const auto burgerHitBox = burger->GetComponent<HitBox>();
    if (!burgerHitBox) {
        std::cout << "Error: Burger HitBox is nullptr\n";
        m_IsDropping = false;
        return;
    }

    constexpr glm::vec3 dropVector(0.0f, 20.0f, 0.0f); // Drop step by step by 20 units
    const glm::vec3 currentPosition = burger->GetWorldPosition();
    const glm::vec3 newPosition = currentPosition + dropVector;
    burger->SetLocalPosition(newPosition);

    // Debug statements
    std::cout << "Dropping burger. Current Position: (" << currentPosition.x << ", " << currentPosition.y << "), New Position: (" << newPosition.x << ", " << newPosition.y << ")\n";

    // Re-check conditions after moving
    const bool isOnFloor = sceneData.IsOnFloor(*burger);
    const bool isInBasket = sceneData.IsInBasket(*burger);
    const bool isOnBurgerParts = sceneData.IsBurgerPartColliding(*burger);
    const bool isOnEnemy = sceneData.isOnEnemy(*burger);


    std::cout << "Checking conditions: IsOnFloor = " << isOnFloor
        << ", IsOnBurgerParts = " << isOnBurgerParts
        << ", IsInBasket = " << isInBasket << "\n";

    int enemyCount = 0; // Counter for enemies on the burger

    if (isOnEnemy) {
        // Increment enemy count
        enemyCount++;
    }

    if (isInBasket) {
        // Give points based on the number of enemies
        int points = 500 * (1 << (enemyCount - 1)); // Using bitwise left shift for exponential calculation
        std::cout << "Points earned: " << points << std::endl;
        m_IsDropping = false;
    }
    // Check conditions
    else if (isOnBurgerParts && !isInBasket) {
        // Drop other burger parts if they are colliding
        const auto& burgerParts = sceneData.GetBurgerParts();
        for (auto part : burgerParts) {
            if (part != burger && sceneData.IsBurgerPartColliding(*part)) {
                auto* partBurgerComponent = part->GetComponent<BurgerComponent>();
                if (partBurgerComponent) {
                    partBurgerComponent->StartDropping();
                   // int points = 500 * (1 << (enemyCount - 1)); // Using bitwise left shift for exponential calculation
                    m_IsDropping = false;
                }
            }
        }
    }
    else if (isOnFloor) {
        // If any condition is met, stop dropping
       // int points = 500 * (1 << (enemyCount - 1)); // Using bitwise left shift for exponential calculation
        m_IsDropping = false;
    }

    // Final debug statement
    std::cout << "Burger final position: (" << burger->GetWorldPosition().x << ", " << burger->GetWorldPosition().y << ")\n";
}
