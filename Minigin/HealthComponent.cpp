#include "HealthComponent.h"


#include "GameEvent.h" 
#include "SteamAchievements.h"

namespace dae
{
    HealthComponent::HealthComponent()
        : m_Lives()
    {
    }

    void HealthComponent::Update(float /*deltaTime*/)
    {
    }

    void HealthComponent::SetLives(int lives)
    {
        m_Lives = lives;
        Notify(GameEvent::LivesUpdated);
        if (m_Lives <= 0)
        {
            Notify(GameEvent::playerDied);
        }
    }

    const char* HealthComponent::GetComponentType() const
    {
        return "HealthComponent";
    }

    void HealthComponent::Notify(GameEvent event) {
        for (auto* observer : m_observers[event]) {
            observer->UpdateObsever(event);
        }
    }
}
