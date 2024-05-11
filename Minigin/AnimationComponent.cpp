#include "AnimationComponent.h"
#include "Renderer.h"

#include "GameTime.h"
#include "ResourceManager.h"

namespace dae
{
    AnimationComponent::AnimationComponent(const AnimationData& animationData, GameObject* gameObject , bool playautomatic)
        : m_animationData(animationData),
        m_isPlaying(false),
        m_frameTime(1.0f / animationData.animationSpeed),
        m_currentFrame(0),
        m_elapsedTime(0.0f),
        m_needsUpdate(true),
        m_renderScaleX(1.0f),
        m_renderScaleY(1.0f),
        m_playautomatic(playautomatic), // Initialize to 0 until texture is loaded
        m_texture(nullptr),
		m_gameObject(gameObject)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(animationData.spritesheetFile);
    }

    void AnimationComponent::Update()
    {
        if (m_isPlaying)
        {
            m_elapsedTime += GameTime::GetDeltaTime();
            const int numFrames = m_animationData.endFrame - m_animationData.startFrame + 1; // Calculate the total number of frames in the range
            const float totalAnimationTime = numFrames * m_frameTime;

            // Calculate the current frame, ensuring it loops back to the start if it reaches the end
            m_currentFrame = static_cast<int>((fmod(m_elapsedTime, totalAnimationTime) / totalAnimationTime) * numFrames);
        }
    }

    void AnimationComponent::Render() const
    {
        if (m_texture != nullptr)
        {
            // Calculate the position to render the texture
            const auto& pos = m_gameObject->GetWorldPosition();
            const float textureWidth = static_cast<float>(m_animationData.frameWidth) * m_renderScaleX; // Use loaded width
            const float textureHeight = static_cast<float>(m_animationData.frameHeight) * m_renderScaleY; // Use loaded height
            const float posX = pos.x - textureWidth / 2.0f;
            const float posY = pos.y - textureHeight / 2.0f;

            // Calculate the source rectangle for the current frame
            const int frameWidth = m_animationData.frameWidth;
            const int frameHeight = m_animationData.frameHeight;
            const int frameX = m_currentFrame * frameWidth;
            SDL_Rect srcRect{ frameX, 0, frameWidth, frameHeight };

            // Determine sprite flipping based on a boolean flag using FlipSprite function
            const auto flip = FlipSprite(m_flipSpriteHorizontally, false);

            // Render the current frame with render scale and flipping
            Renderer::GetInstance().RenderTexture(*m_texture, posX, posY, textureWidth, textureHeight, 0.0f, &srcRect, flip);
        }
    }

    void AnimationComponent::Play()
    {
        m_isPlaying = true;
        m_elapsedTime = 0.0f;
        m_currentFrame = m_animationData.startFrame;
    }

    void AnimationComponent::Stop()
    {
        m_isPlaying = false;
        m_elapsedTime = 0.0f;
        m_currentFrame = 0;
    }

    void AnimationComponent::SetAnimation(const AnimationData& animationData)
    {
        m_animationData = animationData;
        m_frameTime = 1.0f / animationData.animationSpeed;
        m_currentFrame = animationData.startFrame; // Set current frame to start frame
        m_elapsedTime = 0.0f;
        m_needsUpdate = true;
    }

    void AnimationComponent::SetRenderScale(float scaleX, float scaleY)
    {
        m_renderScaleX = scaleX;
        m_renderScaleY = scaleY;
    }

    void AnimationComponent::SetAnimationRange(int startFrame, int endFrame)
    {
        m_animationData.startFrame = startFrame;
        m_animationData.endFrame = endFrame;
    }

    SDL_RendererFlip AnimationComponent::FlipSprite(bool flipHorizontally, bool flipVertically)
    {
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        if (flipHorizontally) {
            flip = SDL_FLIP_HORIZONTAL;
        }

        if (flipVertically) {
            flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
        }

        return flip;
    }

    bool AnimationComponent::IsPlaying() const {
        return m_isPlaying;
    }

   
}
