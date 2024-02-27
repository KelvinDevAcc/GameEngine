#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
	GameObject::GameObject()
		: m_transform(), m_texture(), m_components(), m_width(), m_height(),m_originalTexWidth(),m_originalTexHeight()
	{
	}

    void GameObject::Update(float deltaTime) const
    {
        for (const auto& component : m_components)
        {
            component->Update(deltaTime);
        }
    }

    void GameObject::Render() const
    {
        if (m_texture)
        {
            const auto& pos = m_transform.GetPosition();
            float posX = pos.x - m_width / 2.0f;
            float posY = pos.y - m_height;


            Renderer::GetInstance().RenderTexture(*m_texture, posX, posY, m_width, m_height); // Pass adjusted position, width, and height
        }

        for (const auto& component : m_components)
        {
            component->Render();
        }
    }

    void GameObject::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
        glm::ivec2 size = m_texture->GetSize();
        m_width = static_cast<float>(size.x);
        m_height = static_cast<float>(size.y);

        // Store original dimensions
        m_originalTexWidth = m_width;
        m_originalTexHeight = m_height;
    }
 


    void GameObject::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);

        for (const auto& component : m_components)
        {
            component->SetPosition(x, y);
        }
    }

    void GameObject::SetDimensions(float width, float height)
    {
        m_width = width;
        m_height = height;
    }

    void GameObject::AddComponent(const std::shared_ptr<Component>& component)
    {
        m_components.push_back(component);
        component->SetGameObject(this);
    }

    void GameObject::RemoveComponent(const std::shared_ptr<Component>& component)
    {
        const auto it = std::ranges::find(m_components, component);
        if (it != m_components.end())
        {
            m_components.erase(it);
        }
    }

    glm::vec2 GameObject::GetPosition() const
    {
        return m_transform.GetPosition();
    }
}