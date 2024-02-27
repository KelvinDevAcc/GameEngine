#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "GameObject.h" // Include GameObject header to access its definition

namespace dae
{
    class RenderComponent : public Component
    {
    public:
        RenderComponent(std::shared_ptr<Texture2D> texture, GameObject& gameObject);

        virtual void Update(float deltaTime) override;
        virtual void Render() const override;

    private:
        std::shared_ptr<Texture2D> m_texture;
        GameObject& m_gameObject; // Reference to the GameObject
    };
}