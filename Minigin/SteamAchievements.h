#pragma once

#include "Component.h"
#include "Observer.h"

namespace  dae
{

    class SteamAchievements : public Component, public Observer
    {
    public:
        SteamAchievements() = default;
        ~SteamAchievements() override = default;
        void Update(float deltaTime) override;
        void UpdateObsever(GameEvent event) override;
        const char* GetComponentType() const override { return "SteamAchievements"; }
    };
}
