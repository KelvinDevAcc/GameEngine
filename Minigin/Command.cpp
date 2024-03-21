#include "Command.h"

#include <iostream>


MoveCommand::MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY)
    : m_gameObject(gameObject), m_deltaX(deltaX), m_deltaY(deltaY) {}

void MoveCommand::Execute() {
    if (m_gameObject) {
        glm::vec3 currentPosition = m_gameObject->GetLocalPosition();
        currentPosition.x += m_deltaX;
        currentPosition.y += m_deltaY;
        m_gameObject->SetLocalPosition(currentPosition);
    }
}


DamageCommand::DamageCommand(dae::HealthComponent* healthComponent, int damageAmount)
    : m_healthComponent(healthComponent), m_damageAmount(damageAmount)
{
}

void DamageCommand::Execute()
{
    // Reduce health by damage amount
    const int newHealth = m_healthComponent->GetHealth() - m_damageAmount;
    m_healthComponent->SetHealth(newHealth);
}


ScorePointCommand::ScorePointCommand(dae::PointComponent* pointComponent, int scoreAmount)
    : m_pointComponent(pointComponent), m_scoreAmount(scoreAmount)
{
}

void ScorePointCommand::Execute()
{
    // Increase score by score amount
    const int newScore = m_pointComponent->GetScore() + m_scoreAmount;
    m_pointComponent->SetScore(newScore);
}