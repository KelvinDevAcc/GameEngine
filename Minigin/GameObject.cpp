#include "GameObject.h"

#include <iostream>
#include <stdexcept>
#include <utility>
#include <windows.h>

#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
    GameObject::GameObject()
        : m_transform(), m_components(), m_width(), m_height(), m_originalTexWidth(),
          m_originalTexHeight(), m_localPosition(), m_worldPosition()
    {
    }

    void GameObject::Update(float deltaTime) const
    {
        for (auto& component : m_components)
        {
            component->Update(deltaTime);
        }
    }

    void GameObject::Render() const
    {
        for (auto& component : m_components)
        {
            component->Render();
        }

    }

    void GameObject::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
        const glm::ivec2 size = m_texture->GetSize();
        m_width = static_cast<float>(size.x);
        m_height = static_cast<float>(size.y);

        // Store original dimensions
        m_originalTexWidth = m_width;
        m_originalTexHeight = m_height;
    }

   /* void GameObject::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);

        m_localPosition.x = x;
        m_localPosition.y = y;
        m_positionIsDirty = true;

        for (const auto& component : m_components)
        {
            component->SetPosition(x, y);
        }
    }*/

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

    void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
    {
        if (IsChild(parent) || parent == this || m_parent == parent)
            return;
        if (parent == nullptr)
            SetLocalPosition(GetWorldPosition());
        else
        {
            if (keepWorldPosition)
                SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
            SetPositionDirty();
        }
        if (m_parent) m_parent->RemoveChild(this);
        m_parent = parent;
        if (m_parent) m_parent->AddChild(this);

    }


    void GameObject::SetLocalPosition(const glm::vec3& pos)
    {
        m_localPosition = pos;
        SetPositionDirty();
        for (const auto& component : m_components)
        {
            component->SetPosition(pos.x, pos.y);
        }
    }

    const glm::vec3& GameObject::GetWorldPosition()
    {
        if (m_positionIsDirty)
            UpdateWorldPosition();
        return m_worldPosition;
    }

    glm::vec3 GameObject::GetLocalPosition() const
    {
        return m_localPosition;
    }

    void GameObject::UpdateWorldPosition() 
    {
        if (m_positionIsDirty)
        {
            if (m_parent == nullptr)
                m_worldPosition = m_localPosition;
            else
                m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;

        }
        m_positionIsDirty = false;
    }

    void GameObject::RemoveChild(GameObject* child) {
        std::erase(m_children, child);
    }


    void GameObject::AddChild(GameObject* child)
    {
	    m_children.emplace_back(child);
    }

    bool GameObject::IsChild(GameObject* potentialChild) const
    {
        for (const auto child : m_children)
        {
            if (child == potentialChild || child->IsChild(potentialChild))
            {
                return true;
            }
        }
        return false;
    }

    void GameObject::SetPositionDirty() {
        m_positionIsDirty = true;
    }

    float GameObject::GetRotation() const
    {
        return m_transform.GetRotation();
    }
}