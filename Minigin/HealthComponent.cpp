#include "HealthComponent.h"

#include "EnventQueue.h"
#include "sound_system.h"

namespace dae
{
    HealthComponent::HealthComponent(int initialHealth, int initialLives)
        : m_Health(initialHealth), m_Lives(initialLives)
    {
    }

    void HealthComponent::Update()
    {
        if (m_Health <= 0)
        {
            m_Lives--;
            m_Health = 100; // Reset health
            //if (m_DeathCallback) // Invoke death callback if set
            //    m_DeathCallback();
            if (m_Lives == 0)
            {
                dae::Message message;

                message.type = dae::PlaySoundMessageType::deathSound;

                message.arguments.emplace_back(static_cast<sound_id>(1)); // sound ID
                message.arguments.emplace_back(50.f); // volume

                dae::EventQueue::Broadcast(message);
            }
        }

      
    }

    void HealthComponent::SetHealth(int health)
    {
        m_Health = health;
        Notify(); // Notify observers after updating health
    }

    void HealthComponent::SetLives(int lives)
    {
        m_Lives = lives;
        Notify(); // Notify observers after updating lives
    }
}
