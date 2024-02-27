#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
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
            Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
        }

        for (const auto& component : m_components)
        {
            component->Render();
        }
    }

    void GameObject::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }

    void GameObject::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);

        for (const auto& component : m_components)
        {
            component->SetPosition(x, y);
        }

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