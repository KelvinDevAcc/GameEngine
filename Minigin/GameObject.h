#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"

namespace dae
{
    class GameObject final
    {
    public:
        GameObject();
        ~GameObject() = default;

        void Update(float deltaTime) const;
        void Render() const;

        // Function to set rotation
        void SetRotation(float rotation) { m_worldPosition.SetRotation(rotation); }

        void SetDimensions(float width, float height);
        void AddComponent(const std::shared_ptr<Component>& component);
        void RemoveComponent(const std::shared_ptr<Component>& component);
        void SetParent(GameObject* parent, bool keepWorldPosition = false);

        void SetLocalPosition(const glm::vec3& pos);
        const glm::vec3& GetWorldPosition();
        glm::vec3 GetLocalPosition() const;

        float GetRotation() const;

        template <typename T>
        std::shared_ptr<T> GetComponent()
        {
            for (const auto& component : m_components)
            {
                if (auto derived = std::dynamic_pointer_cast<T>(component))
                    return derived;
            }
            return nullptr;
        }

        template <typename T>
        bool HasComponent()
        {
            return GetComponent<T>() != nullptr;
        }

        const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_components; }

        bool IsChild(GameObject* potentialChild) const;

    private:
        std::shared_ptr<Texture2D> m_texture;
        std::vector<std::shared_ptr<Component>> m_components;
        GameObject* m_parent = nullptr;
        std::vector<GameObject*> m_children;
        float m_width;
        float m_height;
        float m_originalTexWidth;
        float m_originalTexHeight;

        Transform m_localPosition;
        Transform m_worldPosition;
        bool m_positionIsDirty;

        void UpdateWorldPosition();
        void RemoveChild(GameObject* child);
        void AddChild(GameObject* child);
        void SetPositionDirty();
    };
}