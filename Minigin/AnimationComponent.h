#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"


namespace dae
{
    class AnimationComponent : public Component
    {
    public:
        AnimationComponent(GameObject* gameObject, SpriteRenderer* spriteRenderer, const std::string& defaultAnimation);

        void Update() override;
        void Play(const std::string& name, bool looping = false, float startFrameTime = 0.0f);
        void Stop();
        void SetRenderScale(float scaleX, float scaleY);
        void FlipSprite(bool flipHorizontally, bool flipVertically) const;

        std::type_info const& GetComponentType() const override { return typeid(AnimationComponent); }

    private:
        GameObject* m_gameObject;
        SpriteRenderer* m_spriteRenderer;
        const SpriteAnimation* m_activeAnimation;
        std::string m_activeAnimationName;
        bool m_isPlaying;
        bool m_isLooping;
        float m_frameTime;
        float m_renderScaleX;
        float m_renderScaleY;
    };
}
