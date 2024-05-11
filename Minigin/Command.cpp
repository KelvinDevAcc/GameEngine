#include "Command.h"

#include <iostream>

#include "EnventQueue.h"
#include "SceneManager.h"
#include "servicelocator.h"


MoveCommand::MoveCommand(dae::GameObject* gameObject, float deltaX, float deltaY, dae::AnimationComponent* animationComponent)
    : m_gameObject(gameObject), m_deltaX(deltaX), m_deltaY(deltaY),
      m_animationComponent(animationComponent) {}

void MoveCommand::Execute() {
    if (m_gameObject && m_animationComponent) {
        // Update position
        glm::vec3 currentPosition = m_gameObject->GetLocalPosition();
        currentPosition.x += m_deltaX;
        currentPosition.y += m_deltaY;
        m_gameObject->SetLocalPosition(currentPosition);

        // Determine the movement direction
        DetermineMovementDirection(m_deltaX, m_deltaY);

        if (!m_animationComponent->IsPlaying()) {
            m_animationComponent->Play();
        }
    }
}

void MoveCommand::DetermineMovementDirection(float deltaX, float deltaY) const
{
    // Determine movement direction based on deltaX and deltaY values
    // Set the start and end frames based on the movement direction
    if (deltaX > 0) {
       m_animationComponent->SetAnimationRange(3, 6); // Starting frame index for right animation
    }
    else if (deltaX < 0) {
        m_animationComponent->SetAnimationRange(3, 6);
        m_animationComponent->FlipSprite(true, false);
    }
    else if (deltaY > 0) {
        m_animationComponent->SetAnimationRange(0, 3);
    }
    else if (deltaY < 0) {
        m_animationComponent->SetAnimationRange(6, 9);

    }
    else {
        // No movement
        m_animationComponent->SetAnimationRange(0, 0);
    }
}


DamageCommand::DamageCommand(dae::GameObject* gameObject, int damageAmount)
    : m_gameObject(gameObject), m_damageAmount(damageAmount)
{
    m_healthComponent = m_gameObject->GetComponent<dae::HealthComponent>();
}

void DamageCommand::Execute()
{
    // Reduce health by damage amount
    const int newHealth = m_healthComponent->GetHealth() - m_damageAmount;
    m_healthComponent->SetHealth(newHealth);
}


ScorePointCommand::ScorePointCommand(dae::GameObject* gameObject, int scoreAmount)
    : m_gameObject(gameObject), m_scoreAmount(scoreAmount)
{
    m_pointComponent = m_gameObject->GetComponent<dae::PointComponent>();
}

void ScorePointCommand::Execute()
{
    // Increase score by score amount
    if (m_pointComponent)
    {
        const int newScore = m_pointComponent->GetScore() + m_scoreAmount;
        m_pointComponent->SetScore(newScore);
    }
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