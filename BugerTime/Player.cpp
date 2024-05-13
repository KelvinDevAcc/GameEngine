#include "Player.h"

#include "GameTime.h"

namespace game
{
    Player::Player(dae::GameObject* gameObject) : m_CurrentState(nullptr), m_GameObject(gameObject),
                                                  m_timeSinceLastAction(0.0f),
                                                  m_inactivityThreshold(1.0f)
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
            m_CurrentState->OnExitState(*this);
        }
        m_CurrentState = state;
        if (m_CurrentState)
        {
            m_CurrentState->OnEnterState(*this);
            m_timeSinceLastAction = 0.0f;
        }
    }

    void Player::Update()
    {
        if (m_CurrentState)
        {
            m_CurrentState->Update(*this);

            m_timeSinceLastAction += dae::GameTime::GetDeltaTime();

            if (m_timeSinceLastAction >= m_inactivityThreshold)
            {
                Idle();
            }
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
    }

    void Player::Die()
    {
        if (m_CurrentState)
        {
            SetState(m_dyingState.get());
        }
    }

    void Player::Idle()
    {
        if (m_CurrentState)
        {
            SetState(m_idleState.get());
        }
    }

    void Player::Respawn()
    {
        m_GameObject->SetLocalPosition(m_startPosition);
        m_healthComponent->SetLives(3);
        m_pointComponent->SetScore(0);
        Idle();
    }
}
