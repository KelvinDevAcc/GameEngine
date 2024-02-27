#include "RenderComponent.h"
#include "Renderer.h"

namespace dae
{
    RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture, GameObject& gameObject)
        : m_texture(texture), m_gameObject(gameObject)
    {
        // Optionally, load the texture here if needed
    }

    void RenderComponent::Update(float deltaTime)
    {
        // Optionally, update logic specific to rendering here
    }

    void RenderComponent::Render() const
    {
        // Access the Transform component through the GameObject
        const auto& transform = m_gameObject.GetTransform();
        float x = transform.GetPosition().x;
        float y = transform.GetPosition().y;

        // Render the texture using the Renderer class
        if (m_texture)
            Renderer::GetInstance().RenderTexture(*m_texture, x, y);
    }
}