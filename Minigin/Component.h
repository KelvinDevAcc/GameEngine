#pragma once

#include <typeinfo>

namespace dae
{
    class GameObject; // Forward declaration

    class Component
    {
    public:
        Component() : m_pGameObject(nullptr) {}
        virtual ~Component() = default;

        virtual void Initialize() {}
        virtual void Update() = 0; // Pure virtual function for updating component logic
        virtual void Render() const {} // Render component if needed
        virtual const std::type_info& GetComponentType() const = 0; // Pure virtual function for component type identification


        GameObject* GetGameObject() const { return m_pGameObject; }

    private:
        GameObject* m_pGameObject;
    };
}