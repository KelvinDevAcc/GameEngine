#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"


namespace dae
{
    class Texture2D; // Forward declaration

    class GameObject final
    {
    public:
        GameObject();
        ~GameObject() = default;

        void Update(float deltaTime) const;
        void Render() const;

        void SetTexture(const std::string& filename);
        void SetPosition(float x, float y);
        void SetDimensions(float width, float height);

        void AddComponent(const std::shared_ptr<Component>& component);
        void RemoveComponent(const std::shared_ptr<Component>& component);

        template <typename T>
        std::shared_ptr<T> GetComponent()
        {
            for (const auto& component : m_components)
            {
                auto derived = std::dynamic_pointer_cast<T>(component);
                if (derived)
                    return derived;
            }
            return nullptr;
        }

        template <typename T>
        bool HasComponent()
        {
            return GetComponent<T>() != nullptr;
        }

        glm::vec2 GetPosition() const;
       
       
    private:
        Transform m_transform;
        std::shared_ptr<Texture2D> m_texture;
        std::vector<std::shared_ptr<Component>> m_components;
        float m_width;
        float m_height;

        float m_originalTexWidth;
        float m_originalTexHeight;
    };
}
