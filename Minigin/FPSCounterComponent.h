#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae
{
    class FPSCounterComponent final : public Component
    {
    public:
        FPSCounterComponent(TextComponent* textComponent);
        ~FPSCounterComponent() override = default;

        void Update() override;
        float GetFPS() const; // Declaration of GetFPS function

        std::type_info const& GetComponentType() const override { return typeid(FPSCounterComponent); }

    private:
        int m_frameCount = 0;
        float m_elapsedTime = 0.0f;
        float m_fps = 0.0f;
        float m_deltaTime = 0.0f; // Store delta time here

        TextComponent* m_TextComponent;
    };
}
