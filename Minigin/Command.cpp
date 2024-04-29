#include "Command.h"

#include <iostream>

#include "EnventQueue.h"
#include "SceneManager.h"
#include "servicelocator.h"


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

GoToNextSceneCommand::GoToNextSceneCommand() = default;

void GoToNextSceneCommand::Execute()
{
    auto& sceneManager = dae::SceneManager::GetInstance();
    sceneManager.GoToNextScene();
   
}

PlaySoundCommand::PlaySoundCommand() = default;

void PlaySoundCommand::Execute() {

    dae::Message message;

    message.type = dae::PlaySoundMessageType::deathSound;

    message.arguments.emplace_back(static_cast<sound_id>(1)); // sound ID
    message.arguments.emplace_back(50.f); // volume

    dae::EventQueue::Broadcast(message);
}