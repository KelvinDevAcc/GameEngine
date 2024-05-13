#include "Player.h"

#include "EnventQueue.h"
#include "sound_system.h"

namespace game
{
    Player::Player(dae::GameObject* gameObject) : m_CurrentState(nullptr), m_GameObject(gameObject)
    {

        m_animationComponent = m_GameObject->GetComponent<dae::AnimationComponent>();
        m_healthComponent = m_GameObject->GetComponent<dae::HealthComponent>();
        m_pointComponent = m_GameObject->GetComponent<dae::PointComponent>();

        m_startPosition = m_GameObject->GetWorldPosition();

        SetState(m_idleState.get());
    }

    void Player::SetState(PlayerState* state)
    {
	    if (m_CurrentState == state)
            return;

        if (m_CurrentState)
        {
            m_CurrentState->OnExitState(*this); // Exit the current state
        }
        m_CurrentState = state;
        if (m_CurrentState)
        {
            m_CurrentState->OnEnterState(*this); // Enter the new state
        }
    }

    void Player::Update()
    {
        if (m_CurrentState)
        {
            m_CurrentState->Update(*this); // Update based on the current state
        }
    }

    void Player::Move(float deltaX, float deltaY)
    {
        m_deltaY = deltaY;
        m_deltaX = deltaX;

        glm::vec3 currentPosition = m_GameObject->GetWorldPosition();
        currentPosition.x += deltaX;
        currentPosition.y += deltaY;
        m_GameObject->SetLocalPosition(currentPosition);

        if (m_CurrentState)
        {
            SetState(m_walkingState.get());
        }
    }

    void Player::Attack()
    {
        if (m_CurrentState)
        {
            SetState(m_attackignState.get());
        }


        const int newScore = m_pointComponent->GetScore() + 100;
        m_pointComponent->SetScore(newScore);
    }

    void Player::Die()
    {
        if (m_CurrentState)
        {
            SetState(m_dyingState.get());
        }
       
        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(1)); // sound ID
        message.arguments.emplace_back(50.f); // volume

        dae::EventQueue::Broadcast(message);

        const int newHealth = m_healthComponent->GetHealth() - 100;
        m_healthComponent->SetHealth(newHealth);
    }

    void Player::Idle()
    {
        if (m_CurrentState)
        {
            SetState(m_idleState.get());
        }
    }

    void Player::respawn()
    {
        m_GameObject->SetLocalPosition(m_startPosition);
        m_healthComponent->SetLives(3);
        Idle();
    }
}
