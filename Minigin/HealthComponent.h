#pragma once

#include <list>
#include <unordered_map>

#include "Component.h"
#include "Subject.h"
#include "GameEvent.h"

namespace dae
{
    class HealthComponent final : public Component, public Subject 
    {
    public:
        HealthComponent();
        ~HealthComponent() override = default;

        int GetLives() const { return m_Lives; }
        void SetLives(int lives);

        void Update(float deltaTime);
        const char* GetComponentType() const override;

        // Implementations for Subject interface
        void Attach(Observer* observer, GameEvent event) override { m_observers[event].push_back(observer); }
        void Detach(Observer* observer, GameEvent event) override { m_observers[event].remove(observer); }
        void Notify(GameEvent event) override;

    private:
        int m_Lives = 3;
        std::unordered_map<GameEvent, std::list<Observer*>> m_observers;
    };
}