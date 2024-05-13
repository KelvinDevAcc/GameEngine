#include "PlayerState.h"

#include <iostream>

#include "Player.h" // Include the Player header file if necessary

namespace game
{
    //walking state
    void PlayerWalkingState::OnEnterState(Player& /*player*/)
    {
        std::cout << "in PlayerWalkingState";
    }

    void PlayerWalkingState::Update(Player& player)
    {

        if (player.m_deltaX > 0) {
            player.m_animationComponent->Play("Walk_Right", true, 0);
            player.m_animationComponent->FlipSprite(true, false);
        }
        else if (player.m_deltaX < 0) {
            player.m_animationComponent->Play("Walk_Left", true, 0);
            player.m_animationComponent->FlipSprite(false, false);

        }
        else if (player.m_deltaY > 0) {
            player.m_animationComponent->Play("Walk_Down", true, 0);
        }
        else if (player.m_deltaY < 0) {
            player.m_animationComponent->Play("Walk_Up", true, 0);
        }
    }

    void PlayerWalkingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }
   

    //atacking state
    void PlayerAttackingState::OnEnterState(Player& player)
    {
        std::cout << "in PlayerAttackingState";
        player.m_animationComponent->Play("Attacking", false);

    }

    void PlayerAttackingState::Update(Player& /*player*/)
    {
    }

    void PlayerAttackingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }


    //dyingstate
    void PlayerDyingState::OnEnterState(Player& player)
    {
        std::cout << "in PlayerDyingState";
        player.m_animationComponent->Play("Dying", false);
    }

    void PlayerDyingState::Update(Player& player)
    {
	    if (player.m_healthComponent->GetLives() < 0)
	    {
            player.respawn();
	    }
    }

    void PlayerDyingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }


    //idlestate
    void PlayerIdleState::OnEnterState(Player& player)
    {
        std::cout << "in idle";
        player.m_animationComponent->Play("Idle", true);
    }

    void PlayerIdleState::Update(Player& /*player*/)
    {
    }

    void PlayerIdleState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }
}