#pragma once

#include <memory>
#include <vector>

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

        void SetTexture(const std::unique_ptr<Texture2D> texture);
        void SetDimensions(float width, float height);

        void SetAnimationFrames(const std::vector<std::unique_ptr<Texture2D>> frames);
        void SetAnimationSpeed(float framesPerSecond);

        const char* GetComponentType() const override { return "Render"; }

    private:
        enum class RenderMode {
            Static,
            Animated
        };

        RenderMode m_renderMode;

        // For static images
        std::unique_ptr<Texture2D> m_texture;
        float m_width;
        float m_height;

        // For animations
        std::vector<std::unique_ptr<Texture2D>> m_animationFrames;
        float m_animationSpeed;
        float m_currentFrame;
    };
}