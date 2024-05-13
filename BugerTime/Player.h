#pragma once

#include "AnimationComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PlayerState.h" 
#include "PointComponent.h"

namespace game
{
    class Player : public dae::Component
    {

        friend class PlayerWalkingState;
        friend class PlayerAttackingState;
        friend class PlayerIdleState;
        friend class PlayerDyingState;

    public:
        Player(dae::GameObject* parentPtr);

        ~Player() override = default;

        Player(const Player&) = delete;
        Player(Player&&) noexcept = delete;
        Player& operator=(const Player&) = delete;
        Player& operator=(Player&&) noexcept = delete;

        void SetState(PlayerState* state);

        void Update() override;

        void Move(float deltaX, float deltaY);
        void Attack();
        void Die();
        void Idle();

        void respawn();

        std::type_info const& GetComponentType() const override { return typeid(Player); }


        std::unique_ptr<PlayerWalkingState> m_walkingState{ std::make_unique<PlayerWalkingState>() };
        std::unique_ptr<PlayerAttackingState> m_attackignState{ std::make_unique<PlayerAttackingState>() };
        std::unique_ptr<PlayerIdleState> m_idleState{ std::make_unique<PlayerIdleState>() };
        std::unique_ptr<PlayerDyingState> m_dyingState{ std::make_unique<PlayerDyingState>() };

        PlayerState* m_CurrentState; 

        
        float m_deltaY{ 0 };
        float m_deltaX{ 0 };

    private:
       
        dae::GameObject* m_GameObject;

        dae::HealthComponent* m_healthComponent{};
        dae::PointComponent* m_pointComponent{};

        dae::AnimationComponent* m_animationComponent{};

        glm::vec3 m_startPosition{};
        

    };
} // namespace 

