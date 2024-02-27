#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

namespace dae
{
    RenderComponent::RenderComponent()
        : m_width(0), m_height(0)
    {}

    void RenderComponent::Update(float /*deltaTime*/)
    {
    }

    void RenderComponent::Render() const
    {
        if (m_texture)
        {
	        if (const auto gameObject = GetGameObject())
            {
                const auto& pos = gameObject->GetPosition();
                const float posX = pos.x - m_width / 2.0f;
                const float posY = pos.y - m_height;

                Renderer::GetInstance().RenderTexture(*m_texture, posX, posY, m_width, m_height);
            }
        }
    }

    void RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
    {
        m_texture = texture;
        if (m_texture)
        {
            // Retrieve the width and height of the texture
            const auto size = m_texture->GetSize();
            m_width = static_cast<float>(size.x);
            m_height = static_cast<float>(size.y);
        }
    }

    void RenderComponent::SetDimensions(float width, float height)
    {
        m_width = width;
        m_height = height;
    }
}