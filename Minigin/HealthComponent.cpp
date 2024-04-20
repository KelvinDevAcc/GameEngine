#include "HealthComponent.h"

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