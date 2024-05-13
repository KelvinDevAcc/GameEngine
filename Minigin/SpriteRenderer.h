#pragma once
#include <glm/vec2.hpp>

#include "Sprite.h"

#include "Component.h"


namespace dae
{

    class SpriteRenderer final : public Component
    {
    public:
        SpriteRenderer(GameObject* gameObject, const Sprite* sprite, glm::ivec2 drawCell = {});

        ~SpriteRenderer() override = default;

        SpriteRenderer(const SpriteRenderer& other) = delete;
        SpriteRenderer(SpriteRenderer&& other) noexcept = delete;
        SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
        SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

        void SetDrawCell(glm::ivec2 drawCell);
        void SetSprite(const Sprite* spritePtr);

        void Update() override;
    	const Sprite* GetSprite() const;

        void SetDimensions(float width, float height);
        void Setflip(bool flipx, bool flipy);

        std::type_info const& GetComponentType() const override { return typeid(SpriteRenderer); }

    private:
        void Render() const override;

        GameObject* m_gameObject;

        float m_width;
        float m_height;

        bool m_flipX;
        bool m_flipY;

        glm::ivec2 m_drawCell;
        const Sprite* m_spritePtr;
    };
}
