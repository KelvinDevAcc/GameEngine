#pragma once
#include <memory>
#include "Component.h"
#include "Font.h"
#include "Observer.h"
#include "PointComponent.h"
#include "TextComponent.h"


namespace dae
{
    class PointsDisplayComponent : public Component, public Observer
    {
    public:
        PointsDisplayComponent(std::unique_ptr<Font> font, GameObject& gameObject);
        ~PointsDisplayComponent() override = default;

        void Render() const override;
        void Update() override;

        void AttachToPointComponent(PointComponent* pointComponent);

        const char* GetComponentType() const override { return "PointsDisplay"; }

    private:
        PointComponent* m_pointComponent;
        std::unique_ptr<TextComponent> m_textComponent;
    };
}
