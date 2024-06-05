#include "BurgerComponent.h"

#include <iostream>

#include "SceneData.h"
#include "HitBox.h"
#include "SpriteRendererComponent.h"

BurgerComponent::BurgerComponent(float length, float dropDistance)
    : m_IsDropping(false), m_Length(length), m_DropDistance(dropDistance), m_PlayerWalkedDistance(0.0f), m_HasDropped(false) {}

void BurgerComponent::Update() {
    if (m_IsDropping) {
        DropToNextFloor();
    }
    else if (!m_HasDropped) {
        if (IsPlayerOverComponent()) {
            m_IsDropping = true; // Start dropping
        }
        else {
            m_PlayerWalkedDistance = 0.0f; // Reset if player steps off
        }
    }
}

bool BurgerComponent::IsPlayerOverComponent() const
{
	const auto& sceneData = dae::SceneData::GetInstance();
    const auto player = sceneData.GetPlayer();
    if (!player) return false;

    const auto playerHitBox = player->GetComponent<HitBox>();
    const auto burgerHitBox = GetGameObject()->GetComponent<HitBox>();

    return playerHitBox && burgerHitBox && playerHitBox->IsColliding(*burgerHitBox);
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

    constexpr glm::vec3 dropVector(0.0f, 20.0f, 0.0f); // Drop step by step by 50 units
    const glm::vec3 currentPosition = burger->GetWorldPosition();
    const glm::vec3 newPosition = currentPosition + dropVector;
    burger->SetLocalPosition(newPosition);

    // Debug statements
    std::cout << "Dropping burger. Current Position: (" << currentPosition.x << ", " << currentPosition.y << "), New Position: (" << newPosition.x << ", " << newPosition.y << ")\n";

    // Re-check conditions after moving
    const bool isOnFloor = sceneData.IsOnFloor(*burger);
    const bool isInBasket = sceneData.IsInBasket(*burger);
    const bool isOnBurgerParts = sceneData.IsBurgerPartColliding(*burger);

    std::cout << "Checking conditions: IsOnFloor = " << isOnFloor
        << ", IsOnBurgerParts = " << isOnBurgerParts
        << ", IsInBasket = " << isInBasket << "\n";

    // Check conditions
    if (isOnFloor) 
    {
        // If any condition is met, stop dropping
        m_IsDropping = false;
    }
    else if (isInBasket)
    {
        m_IsDropping = false;
    }
    else if (isOnBurgerParts)
    {
	    if (m_IsDropping)
	    {
		    const auto position = GetGameObject()->GetWorldPosition();
            GetGameObject()->SetLocalPosition(glm::vec3(position.x, position.y + GetGameObject()->GetComponent<dae::SpriteRendererComponent>()->GetDimensions().y, position.z));
	    	m_IsDropping = false;
	    }
    }


    // Final debug statement
    std::cout << "Burger final position: (" << burger->GetWorldPosition().x << ", " << burger->GetWorldPosition().y << ")\n";
}
