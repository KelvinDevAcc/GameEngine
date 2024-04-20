#pragma once

#include <list>

#include "Component.h"
#include "Subject.h"

namespace dae
{
    class HealthComponent final : public Component, public Subject // Inherit from Subject interface
    {
    public:
        HealthComponent(int initialHealth, int initialLives);
        ~HealthComponent() override = default;

        int GetHealth() const { return m_Health; }
        void SetHealth(int health);

        int GetLives() const { return m_Lives; }
        void SetLives(int lives);

        void Update() override;
        std::type_info const& GetComponentType() const override { return typeid(HealthComponent); }

        // Implementations for Subject interface
        void Attach(Observer* observer) override { m_observers.push_back(observer); }
        void Detach(Observer* observer) override { m_observers.remove(observer); }
        void Notify() override
        {
            for (auto* observer : m_observers)
            {
                observer->Update();
            }
        }

    private:
        int m_Health = 100;
        int m_Lives = 3;
        std::list<Observer*> m_observers;
    };
}