#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include "Font.h"
#include "Observer.h"
#include "Renderer.h"
#include "PointComponent.h"
#include "Transform.h"


namespace dae
{
    class PointsDisplayComponent : public Component, public Observer
    {
    public:
        PointsDisplayComponent(std::unique_ptr<Font> font);
        ~PointsDisplayComponent() override = default;

        void Render() const override;
        void UpdateObsever(GameEvent event) override;
        void SetPosition(float x, float y) override;
        void AttachToPointComponent(PointComponent* pointComponent);

        const char* GetComponentType() const override { return "PointsDisplay"; }

    private:
        PointComponent* m_pointComponent;
        std::unique_ptr<Font> m_font;
        std::unique_ptr<Texture2D> m_textTexture;
        Transform m_transform{};

        void RenderText(const std::string& text);
    };
}
