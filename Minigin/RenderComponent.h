#pragma once

#include <memory>

#include "Component.h"
#include "Texture2D.h"

namespace dae
{
    class RenderComponent : public Component
    {
    public:
        RenderComponent();
        ~RenderComponent() override = default;

        void Update(float deltaTime) override;
        void Render() const override;
        void SetTexture(const std::shared_ptr<Texture2D>& texture);
        void SetDimensions(float width, float height);

        const char* GetComponentType() const override { return "Render"; }

    private:
        std::shared_ptr<Texture2D> m_texture;
        float m_width;
        float m_height;
    };
}