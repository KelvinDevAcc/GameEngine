#pragma once

#include <memory>
#include <string>
#include "Component.h"
#include "Font.h"
#include "Renderer.h"
#include "HealthComponent.h"
#include "Observer.h"
#include "Transform.h"

namespace dae
{
    class LivesDisplayComponent : public Component, public Observer
    {
    public:
        LivesDisplayComponent(std::unique_ptr<Font> font);
        ~LivesDisplayComponent() override = default;
        void Render() const override;
        void UpdateObsever(GameEvent event) override;
        void SetPosition(float x, float y) override;
        void Update(float deltaTime) override;
        void AttachToHealthComponent(HealthComponent* healthComponent);

        const char* GetComponentType() const override { return "LivesDisplay"; }

    private:
        HealthComponent* m_healthComponent;
        std::unique_ptr<Font> m_font;
        std::unique_ptr<Texture2D> m_textTexture;
        Transform m_transform{};

        void RenderText(const std::string& text);
    };
}
