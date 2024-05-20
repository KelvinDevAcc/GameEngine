#include "Player.h"

#include "GameTime.h"
#include "SceneData.h"
#include "SceneHelpers.h"

namespace game
{
    Player::Player(dae::GameObject* gameObject)
        : m_CurrentState(nullptr), m_GameObject(gameObject),
        m_timeSinceLastAction(0.0f), m_inactivityThreshold(1.0f),
        m_gameMap(nullptr)
    {

        m_animationComponent = m_GameObject->GetComponent<dae::AnimationComponent>();
        m_healthComponent = m_GameObject->GetComponent<dae::HealthComponent>();
        m_pointComponent = m_GameObject->GetComponent<dae::PointComponent>();

        m_startPosition = m_GameObject->GetWorldPosition();

        SetState(m_idleState.get());
        dae::SceneData::GetInstance().AddGameObject(m_GameObject, dae::GameObjectType::Player);
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

            dae::SceneData::GetInstance().Update();
        }
    }

    void Player::Move(float deltaX, float deltaY)
    {
        //m_deltaY = deltaY;
        //m_deltaX = deltaX;

        //glm::vec3 currentPosition = m_GameObject->GetWorldPosition();
        //currentPosition.x += deltaX;
        //currentPosition.y += deltaY;
        //m_GameObject->SetLocalPosition(currentPosition);

        //if (m_CurrentState)
        //{
        //    SetState(m_walkingState.get());
        //}


        m_deltaY = deltaY;
        m_deltaX = deltaX;

        CheckAndMove(deltaX, deltaY);
    }

    void Player::Attack() {
        SetState(m_attackignState.get());
    }

    void Player::Die() {
        SetState(m_dyingState.get());
    }

    void Player::Idle() {
        SetState(m_idleState.get());
    }

    void Player::Respawn()
    {
        m_GameObject->SetLocalPosition(m_startPosition);
        m_healthComponent->SetLives(3);
        m_pointComponent->SetScore(0);
        Idle();
    }

    void Player::SetMap(const LoadMap& map) {
        m_gameMap = &map;
    }

    void Player::CheckAndMove(float deltaX, float deltaY)
    {
        const auto& sceneData = dae::SceneData::GetInstance();

        bool canMoveX = false;
        bool canMoveY = false;

        bool isOnLadder = sceneData.IsOnLadder(*m_GameObject);
        bool isOnSolidLadder = sceneData.IsOnSolidLadder(*m_GameObject);
        bool isOnFloor = sceneData.IsOnFloor(*m_GameObject);

        // Allow horizontal movement if the player is on a regular ladder or not on any ladder
        if (isOnFloor) {
            if (sceneData.CanEntityMove(deltaX, 0, *m_GameObject)) {
                canMoveX = true;
            }
        }

        // Allow vertical movement if the player is on a ladder or solid ladder
        if (isOnSolidLadder) {
            if (sceneData.CanEntityMove(0, deltaY, *m_GameObject)) {
                canMoveY = true;
            }
        }

        if (isOnLadder) {
            if (sceneData.CanEntityMove(deltaX, deltaY, *m_GameObject)) {
                canMoveY = true;
            }
        }

        if (canMoveX || canMoveY) {
            glm::vec3 currentPosition = m_GameObject->GetWorldPosition();
            if (canMoveX) {
                currentPosition.x += deltaX;
            }
            if (canMoveY) {
                currentPosition.y += deltaY;

                // If moving vertically on a ladder, clip to the center of the ladder
                if (isOnLadder) {
                    // Assuming you have a function to get the center X position of the ladder
                    float ladderCenterX = sceneData.GetLadderCenterX(*m_GameObject);
                    currentPosition.x = ladderCenterX;
                }
            }
            m_GameObject->SetLocalPosition(currentPosition);

            if (m_CurrentState) {
                SetState(m_walkingState.get());
            }
        }
        else {
            Idle();
        }
    }

}
