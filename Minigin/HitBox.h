#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"

class HitBox : public dae::Component {
public:
    HitBox(const glm::vec2& size)
	    : m_position(0,0), m_size(size)
    {
    }

    SDL_Rect GetRect() const {
	    const glm::vec2 position = m_position;
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(m_size.x),
            static_cast<int>(m_size.y)
        };
    }

    bool IsColliding(const HitBox& other) const {
	    const SDL_Rect rectA = GetRect();
        const SDL_Rect rectB = other.GetRect();
        return SDL_HasIntersection(&rectA, &rectB) == SDL_TRUE;
    }

    void SetPosition(const glm::vec2& position) {
        m_position = position;
    }

    void Update() override {

        if (const auto parent = GetGameObject()) {
            m_position = parent->GetWorldPosition();
        }
    }

    void Render() const override
    {
	    const SDL_Rect rect = GetRect(); 
        dae::Renderer::GetInstance().RenderRect(rect, { 255, 0, 0, 255 }, false);
    }

    const std::type_info& GetComponentType() const override {
        return typeid(HitBox);
    }

private:
    glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
    glm::vec2 m_size;
};
