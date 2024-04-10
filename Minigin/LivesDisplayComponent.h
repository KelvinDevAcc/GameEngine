#pragma once

#include <memory>
#include "Component.h"
#include "Font.h"
#include "HealthComponent.h"
#include "Observer.h"
#include "TextComponent.h"


namespace dae
{
    class LivesDisplayComponent : public Component, public Observer
    {
    public:
        LivesDisplayComponent(std::unique_ptr<Font> font, GameObject& gameObject);
        ~LivesDisplayComponent() override = default;

        void Render() const override;
        void Update() override;

        void AttachToHealthComponent(HealthComponent* healthComponent);

        const char* GetComponentType() const override { return "LivesDisplay"; }

    private:
        std::unique_ptr<TextComponent> m_textComponent;
        HealthComponent* m_healthComponent;
    };
}
