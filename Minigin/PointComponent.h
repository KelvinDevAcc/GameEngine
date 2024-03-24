#pragma once

#include <list>
#include <unordered_map>

#include "Component.h"
#include "Subject.h"
#include "GameEvent.h" 

namespace dae
{
    class PointComponent final : public Component, public Subject // Inherit from Subject interface
    {
    public:
        PointComponent();
        ~PointComponent() override = default;

        int GetScore() const { return m_Score; }
        void SetScore(int score);

        void Update(float deltaTime) override;
        const char* GetComponentType() const override;

        void Attach(Observer* observer, GameEvent event) override { m_observers[event].push_back(observer); }
        void Detach(Observer* observer, GameEvent event) override { m_observers[event].remove(observer); }
        void Notify(GameEvent event) override
        {
            for (auto* observer : m_observers[event])
            {
                if (observer)
                {
                    observer->UpdateObsever(event);
                }
            }
        }

    private:
        int m_Score;
        std::unordered_map<GameEvent, std::list<Observer*>> m_observers;
    };
}