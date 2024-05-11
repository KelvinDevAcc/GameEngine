#pragma once
#include <SDL_render.h>
#include <string>
#include "GameObject.h"
#include "Texture2D.h"

namespace dae
{
    struct AnimationData
    {
        std::string spritesheetFile;
        int frameWidth;
        int frameHeight;
        int frameCount;
        int startFrame; // New member: Start frame of the animation
        int endFrame;   // New member: End frame of the animation
        float animationSpeed;
    };

    class AnimationComponent : public Component
    {
    public:
        AnimationComponent(const AnimationData& animationData, GameObject* gameObject, bool playautomatic);
        ~AnimationComponent() override = default;

        AnimationComponent(const AnimationComponent& other) = delete; // Copy constructor
        AnimationComponent(AnimationComponent&& other) noexcept = delete; // Move constructor
        AnimationComponent& operator=(const AnimationComponent& other) = delete; // Copy assignment operator
        AnimationComponent& operator=(AnimationComponent&& other) noexcept = delete; // Move assignment operator


        void Update() override;
        void Render() const override;
        void Play();
        void Stop();
        void SetAnimation(const AnimationData& animationData);

        void SetRenderScale(float scaleX, float scaleY);
        void SetAnimationRange(int startFrame, int endFrame);

        static SDL_RendererFlip FlipSprite(bool flipHorizontally, bool flipVertically);
        bool IsPlaying() const;
        int GetCurrentFrame() const { return m_currentFrame; }
        const AnimationData& GetAnimationData() const { return m_animationData; }


        std::type_info const& GetComponentType() const override { return typeid(AnimationComponent); }

    private:
        AnimationData m_animationData;
        bool m_isPlaying;
        float m_frameTime;
        int m_currentFrame;
        float m_elapsedTime;
        bool m_needsUpdate;
        float m_renderScaleX;
        float m_renderScaleY;
        bool m_playautomatic;
        bool m_flipSpriteHorizontally;
        std::unique_ptr<Texture2D> m_texture;
        GameObject* m_gameObject;
    };
}