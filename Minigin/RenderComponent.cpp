#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

namespace dae
{
    RenderComponent::RenderComponent()
	    : m_renderMode(RenderMode::Static), m_width(0), m_height(0), m_animationSpeed(0), m_currentFrame(0)
    {
    }

    void RenderComponent::Update() {
        if (m_renderMode == RenderMode::Animated) {
            m_currentFrame += m_animationSpeed * deltaTime;
            if (m_currentFrame >= m_animationFrames.size()) {
                m_currentFrame -= static_cast<float>(m_animationFrames.size());
            }
        }
    }


    void RenderComponent::Render() const
    {
        if (m_texture)
        {
            if (m_renderMode == RenderMode::Static && m_texture) {
                if (const auto gameObject = GetGameObject()) {
                    const auto& pos = gameObject->GetWorldPosition();
                    const float posX = pos.x - m_width / 2.0f;
                    const float posY = pos.y - m_height / 2.0f;
                    Renderer::GetInstance().RenderTexture(*m_texture, posX, posY, m_width, m_height);
                }
            }
            else if (m_renderMode == RenderMode::Animated && !m_animationFrames.empty()) {
                if (const auto gameObject = GetGameObject()) {
                    const auto& pos = gameObject->GetWorldPosition();
                    const float posX = pos.x - m_width / 2.0f;
                    const float posY = pos.y - m_height / 2.0f;
                    Renderer::GetInstance().RenderTexture(*m_animationFrames[static_cast<size_t>(m_currentFrame)], posX, posY, m_width, m_height);
                }
            }
        }
    }

    void RenderComponent::SetTexture(std::unique_ptr<Texture2D> texture)
    {
        m_texture = std::move(texture);
        if (m_texture)
        {
            // Retrieve the width and height of the texture
            const auto size = m_texture->GetSize();
            m_width = static_cast<float>(size.x);
            m_height = static_cast<float>(size.y);
        }
        m_renderMode = RenderMode::Static;
    }

    void RenderComponent::SetDimensions(float width, float height)
    {
        m_width = width;
        m_height = height;
    }

    void RenderComponent::SetAnimationFrames(std::vector<std::unique_ptr<Texture2D>> frames) {
        m_animationFrames.clear();
        m_animationFrames.reserve(frames.size());
        for (auto& frame : frames) {
            m_animationFrames.push_back(std::move(frame));
        }
        m_renderMode = RenderMode::Animated;
        m_currentFrame = 0;
    }

    void RenderComponent::SetAnimationSpeed(float framesPerSecond) {
        m_animationSpeed = framesPerSecond;
    }
}