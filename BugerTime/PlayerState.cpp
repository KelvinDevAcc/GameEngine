#include "PlayerState.h"
#include "EnventQueue.h"
#include "Player.h"
#include "sound_system.h"

namespace game
{
    //walking state
    void MovingState::Update(Player& player)
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

    void MovingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }
   

    //atacking state
    void AttackingState::OnEnterState(Player& player)
    {
        player.m_animationComponent->Play("Attacking", false);

		const int newScore = player.m_pointComponent->GetScore() + 100;
        player.m_pointComponent->SetScore(newScore);
        /*dae::Message scoreMessage;
        scoreMessage.type = dae::PointsMessageType::addScore;
        scoreMessage.arguments.emplace_back(100);
        dae::EventQueue::Broadcast(scoreMessage);*/
    }

    void AttackingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }


    //dyingstate
    void DyingState::OnEnterState(Player& player)
    {
        player.m_animationComponent->Play("Dying", false);

        dae::Message message;

        message.type = dae::PlaySoundMessageType::deathSound;

        message.arguments.emplace_back(static_cast<sound_id>(1));

        dae::EventQueue::Broadcast(message);

        const int newHealth = player.m_healthComponent->GetHealth() - 100;
        player.m_healthComponent->SetHealth(newHealth);
    }

    void DyingState::Update(Player& player)
    {
	    if (player.m_healthComponent->GetLives() < 0)
	    {
            player.Respawn();
	    }
    }

    void DyingState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }


    //idlestate
    void IdleState::OnEnterState(Player& player)
    {
        player.m_animationComponent->Play("Idle", true);
    }

    void IdleState::OnExitState(Player& player)
    {
        player.m_animationComponent->Stop();
    }
}
