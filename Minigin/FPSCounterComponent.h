#pragma once
#include "Component.h"

namespace dae
{
    class FPSCounterComponent final : public Component
    {
    public:
        FPSCounterComponent() = default;
        ~FPSCounterComponent() override = default;

        void Update() override;
        float GetFPS() const; // Declaration of GetFPS function

        const char* GetComponentType() const override { return "FPSCounter"; } // Implementation of GetComponentType()

    private:
        int m_frameCount = 0;
        float m_elapsedTime = 0.0f;
        float m_fps = 0.0f;
        float m_deltaTime = 0.0f; // Store delta time here
    };
}