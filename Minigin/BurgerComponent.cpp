#include "BurgerComponent.h"

#include <iostream>

#include "SceneData.h"
#include "HitBox.h"

BurgerComponent::BurgerComponent(float length, float dropDistance)
    : m_Length(length), m_DropDistance(dropDistance), m_PlayerWalkedDistance(0.0f), m_HasDropped(false) {}

void BurgerComponent::Update() {
    if (!m_HasDropped) {
        if (IsPlayerOverComponent()) {
            m_PlayerWalkedDistance += GetPlayerMovementOverComponent();
            if (m_PlayerWalkedDistance >= m_Length) {
                DropToNextFloor();
                m_HasDropped = true;
            }
        }
        else {
            m_PlayerWalkedDistance = 0.0f; // Reset if player steps off
        }
    }
}

bool BurgerComponent::IsPlayerOverComponent() {
    auto& sceneData = dae::SceneData::GetInstance();
    const auto player = sceneData.GetPlayer();
    if (!player) return false;

    const auto playerHitBox = player->GetComponent<HitBox>();
    const auto burgerHitBox = GetGameObject()->GetComponent<HitBox>();

    return playerHitBox && burgerHitBox && playerHitBox->IsColliding(*burgerHitBox);
}

float BurgerComponent::GetPlayerMovementOverComponent() {
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
    auto& sceneData = dae::SceneData::GetInstance();
    auto* burger = GetGameObject();

    glm::vec3 dropVector(0.0f, m_DropDistance, 0.0f);
    while (!sceneData.IsOnFloor(*burger) &&
        !sceneData.IsOnSpecificObjectType(*burger, sceneData.GetBurgerParts()) &&
        !sceneData.IsInBasket(*burger)) {
        glm::vec3 currentPosition = burger->GetWorldPosition();
        burger->SetLocalPosition(currentPosition + dropVector);
    }
}
