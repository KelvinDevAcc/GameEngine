#pragma once

namespace dae
{
    class GameObject; // Forward declaration

    class Component
    {
    public:
        Component() : m_pGameObject(nullptr) {}
        virtual ~Component() = default;

        virtual void Initialize() {}
        virtual void Update(float deltaTime) = 0;
        virtual void Render() const {} 
        virtual const char* GetComponentType() const = 0;
        virtual void SetPosition(float x, float y) { (void)x; (void)y; }

        void SetGameObject(GameObject* gameObject) { m_pGameObject = gameObject; }
        GameObject* GetGameObject() const { return m_pGameObject; }

    protected:
        GameObject* m_pGameObject;
    };
}